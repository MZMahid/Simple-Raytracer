#include <iostream>
#include"vec3.h"

int main(){

    int world_width = 400;
    double aspect_ratio = 16.0/ 9.0;
    int world_height = world_width / aspect_ratio;

    //main render loop
    std::cout << "P3\n" << world_width << " " << world_height << '\n' <<"255\n";
    for(int j = 0 ; j < world_height ; j++){
        for(int i = 0 ; i < world_width ; i++){
            double r_norm = double(i) / (world_width - 1);
            double g_norm = double(j) / (world_height  - 1);
            double b_norm = 0.0;

            std::cout << int(r_norm * 255.0) << " " << int(g_norm * 255.0) 
                      << " " << int(b_norm * 255.0) << '\n';
        }
    }
}