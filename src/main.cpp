#include <iostream>
#include <vector>
#include <memory>
#include"global.h"

color get_ray_col(const ray &r, hit_record &rec
                , const std::vector<std::shared_ptr<hittable>>& world)
{
    // color current_surf_col;
    for(const auto& obj : world){
        obj->hit(r, rec);

        //stupid complicated casting codes that doesn't work
        // std::shared_ptr<sphere> obj_dirived = std::dynamic_pointer_cast<sphere>(obj);
        // if(obj_dirived){
        //     current_surf_col = obj_dirived->surf_col;
        // }
    }

    vec3 unit_direction = unit_vector(r.get_direction());
    if(rec.isHit){
        color N = rec.normal;
        return color(N.x() + 1, N.y() + 1, N.z() + 1) * 0.5 * rec.hit_surf_col;
    }
    else{
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
}

int main(){

    int world_width = 400;
    double aspect_ratio = 16.0/ 9.0;
    int world_height = world_width / aspect_ratio;

    double view_height = 2.0;
    double view_width = view_height * (double(world_width) / world_height);

    point3 cam_pos(0, 0, 0);

    double focal_lenght = 1.0;

    vec3 view_w_vec = vec3(view_width, 0, 0);
    vec3 view_h_vec = vec3(0, -view_height ,0);

    vec3 view_w_unit = view_w_vec / world_width;
    vec3 view_h_unit = view_h_vec / world_height;

    point3 corner = cam_pos 
                      - vec3(0, 0, focal_lenght)
                      - view_w_vec / 2
                      - view_h_vec / 2;
    point3 pix_00 = corner + (view_w_unit + view_h_unit) / 2;

    //main render loop

    std::vector<std::shared_ptr<hittable>> world;

    auto ground = std::make_shared<sphere>(point3(2, 0, -3), 1.2, color(1, 0, 0));
    auto ball = std::make_shared<sphere>(point3(0, 0, -2), 1, color(0, 1, 0));

    world.push_back(ground);
    world.push_back(ball);
    std::cout << "P3\n" << world_width << " " << world_height << '\n' <<"255\n";
    for(int j = 0 ; j < world_height ; j++){
        for(int i = 0 ; i < world_width ; i++){

            point3 pix_center = pix_00 + (i * view_w_unit) + (j * view_h_unit);
            //construct the ray
            ray ray(cam_pos, (pix_center - cam_pos));
            hit_record rec;
            
            color rgb = get_ray_col(ray, rec, world);


            std::cout << int(rgb.x() * 255.0) << " " << int(rgb.y() * 255.0) 
                      << " " << int(rgb.z() * 255.0) << '\n';
        }
    }
}

