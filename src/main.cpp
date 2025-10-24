#include <iostream>
#include <vector>
#include <memory>
#include <random>
#include"global.h"
#include"interval.h"

    color get_ray_col(const ray &r, hit_record &rec, const std::vector<std::shared_ptr<hittable>> &world)
{
    const double infinity = std::numeric_limits<double>::infinity();
    interval limit(0, infinity);
    bool hit_anything = false;

    for(const auto& obj : world){
        if(obj->hit(r, limit, rec)){
            hit_anything = true;
            limit.max = rec.t;
        }
    }

    vec3 unit_direction = unit_vector(r.get_direction());
    if(hit_anything){
        color N = rec.normal;
        return color(N.x() + 1, N.y() + 1, N.z() + 1) * 0.5 * rec.hit_surf_col;
    }
    else{
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
}

int main(){
    int samples = 10;

    int world_width = 400;
    double aspect_ratio = 16.0/ 9.0;
    int world_height = world_width / aspect_ratio;

    double view_height = 2.0;
    double view_width = view_height * (double(world_width) / world_height);

    point3 cam_pos(0, 0, 0);

    double focal_lenght = 1.0;

    vec3 view_w_vec = vec3(view_width, 0, 0);
    vec3 view_h_vec = vec3(0, -view_height ,0);

    vec3 view_w_delta = view_w_vec / world_width;
    vec3 view_h_delta = view_h_vec / world_height;

    point3 corner = cam_pos 
                      - vec3(0, 0, focal_lenght)
                      - view_w_vec / 2
                      - view_h_vec / 2;
    point3 pix_00 = corner + (view_w_delta + view_h_delta) / 2;

    //main render loop

    std::vector<std::shared_ptr<hittable>> world;

    auto red = std::make_shared<sphere>(point3(1.4, 0, -2), 1, color(1, 0, 0));
    auto green = std::make_shared<sphere>(point3(0, 0, -3), 1, color(0, 1, 0));

    world.push_back(green);
    world.push_back(red);

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-0.5, 0.5);
    std::cout << "P3\n" << world_width << " " << world_height << '\n' <<"255\n";
    for(int j = 0 ; j < world_height ; j++){
        for(int i = 0 ; i < world_width ; i++){

            point3 pix_center = pix_00 + (i * view_w_delta) + (j *view_h_delta);
            //construct the ray
            color rgb(0, 0, 0);


            for (int k = 0; k < samples; ++k)
            {
                vec3 offset = vec3( distribution(generator) * view_w_delta.x(),
                                    distribution(generator) * view_h_delta.y(),
                                    0);
                ray ray(cam_pos, (pix_center - cam_pos) + offset);
                hit_record rec;
                rgb += get_ray_col(ray, rec, world);
            }

            rgb /= samples;
            std::cout << int(rgb.x() * 255.9) << " " << int(rgb.y() * 255.9) 
                      << " " << int(rgb.z() * 255.9) << '\n';
        }
    }
}

