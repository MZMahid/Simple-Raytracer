#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"

class sphere : public hittable {

public:
    vec3 center;
    double radius;
    color surf_col;
    sphere(const vec3& c, const double& r,const color& col) : center{c}, radius{r}, surf_col{col} {}

    void hit(const ray& ray, hit_record& rec) const override{
        vec3 d = ray.get_direction();
        double a = dot(d, d);
        vec3 dis_OtoC = center - ray.get_origin();
        double b = -2 * dot(d, dis_OtoC);
        double c = dot(dis_OtoC, dis_OtoC) - std::pow(radius, 2);
        bool isHit = false;

        if( (b * b - 4*a*c) > 0 ){
            isHit = true;
            rec.isHit = true;
        }
        else return;

        double lineDis{};
        if(isHit){
            lineDis = (-b - sqrt(b*b - 4*a*c)) / (2*a);
            if(lineDis < 0){
                lineDis = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
            }
        }
        rec.t = lineDis;
        rec.p = ray.at(rec.t);
        rec.normal = unit_vector(rec.p - center);
        if (dot(rec.normal, ray.get_direction()) >= 0){
            rec.normal = -rec.normal;   
        }
        rec.hit_surf_col = surf_col;
    }
};

#endif