#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include"global.h"
#include"interval.h"

//this function runs for every single ray and returns final color for that ray.
color get_ray_col(const ray &r, hit_record &rec, const std::vector<std::shared_ptr<hittable>> &world)
{
    const double infinity = std::numeric_limits<double>::infinity();
    interval limit(0.001, infinity); // 0.001 prevents self-intersection artifacts
    bool hit_anything = false;
    bool inShadow = false;

    for(const auto& obj : world){ // single ray check for any hit on all the objects in scene
        if(obj->hit(r, limit, rec)){
            hit_anything = true;
            limit.max = rec.t; // limit the max hit lenght to the latest hit to keep the depth correct
        }
    }

    point3 light_pos = point3(5, 5, 1); // point light
    vec3 light_dir = unit_vector(light_pos - rec.p); // direction hit point to light
    ray shadow_ray(rec.p, light_dir); // construct shadow ray
    hit_record shadow_rec;
    for (const auto &objj : world) // shadow ray check if there is any blockage between hitpoint and light source
    {
        if (objj->hit(shadow_ray, interval(0.01, infinity), shadow_rec))
        {
            inShadow = true;
            break;
            
        }
    }

    vec3 unit_direction = unit_vector(r.get_direction());
    color base = rec.hit_surf_col;

    if(hit_anything){ // something hit! now is it in shadow or not.

        color N = unit_vector(rec.normal);
        if(inShadow){
            return base * 0.2; // 20% ambient lighting in shadow
        }
        else{
            double diffuse = std::max(0.0, dot(N, light_dir));
            double lighting = 0.2 + 0.8 * diffuse; // ambient + diffuse
            return base * lighting ;
        }
    }


    else{ // default sky color if the ray hit nothing in the scene
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
}

int main(){
    int samples = 1;

    int world_width = 400;
    double aspect_ratio = 16.0/ 9.0;
    int world_height = world_width / aspect_ratio;

    double view_height = 2.0;
    // making sure the vieport has same ratio as the scene
    double view_width = view_height * (double(world_width) / world_height);

    point3 cam_pos(0, 0, 0);

    double focal_lenght = 1.0;

    vec3 view_w_vec = vec3(view_width, 0, 0);
    vec3 view_h_vec = vec3(0, -view_height ,0); // reverse the y cordinate to be up as positive

    //for every unit of x or y in scene how much lenght in viewport
    vec3 view_w_delta = view_w_vec / world_width;
    vec3 view_h_delta = view_h_vec / world_height;

    point3 corner = cam_pos 
                      - vec3(0, 0, focal_lenght)
                      - view_w_vec / 2
                      - view_h_vec / 2;
    point3 pix_00 = corner + (view_w_delta + view_h_delta) / 2;

    //main render loop

    std::vector<std::shared_ptr<hittable>> world;

    auto ball = std::make_shared<sphere>(point3(0, 0, -1), 0.5, color(0.5, 1, 0));
    // auto ground = std::make_shared<sphere>(point3(0, -100.5, -1), 100.0, color(0.9, 0.9, 0.8));
    auto sample_plane = std::make_shared<plane>(point3(0, -0.5, 0), vec3(0.2, 1, 0), color(1, 1, 0));
    auto sample_triangle = std::make_shared<triangle>(point3(0, 1, -1), point3(-2, -1, -1), point3(2, -1, -1));

    world.push_back(ball);
    // world.push_back(ground);
    world.push_back(sample_plane);
    world.push_back(sample_triangle);

    // random seed generator
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-0.5, 0.5);

    std::cout << "P3\n" << world_width << " " << world_height << '\n' <<"255\n";
    for(int j = 0 ; j < world_height ; j++){
        for(int i = 0 ; i < world_width ; i++){

            //move from one center to another center of pixel
            point3 pix_center = pix_00 + (i * view_w_delta) + (j *view_h_delta);
            color rgb(0, 0, 0);


            for (int k = 0; k < samples; ++k)
            {
                // offset the ray intersection in the viewport from the center but still keeping inside single pixel.
                vec3 offset = vec3( distribution(generator) * view_w_delta.x(),
                                    distribution(generator) * view_h_delta.y(),
                                    0);
                ray ray(cam_pos, (pix_center - cam_pos) + offset); // single primary ray
                hit_record rec; // each ray has its own hit record
                rgb += get_ray_col(ray, rec, world); 
            }

            rgb /= samples; // avarage result of all the ray with an offset for singel pixel, this is AA
            std::cout << int(rgb.x() * 255.9) << " " << int(rgb.y() * 255.9) 
                      << " " << int(rgb.z() * 255.9) << '\n';
        }
    }
}

