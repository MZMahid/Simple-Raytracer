#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"
#include"interval.h"

class sphere : public hittable {

public:
    vec3 center;
    double radius;
    color surf_col;
    sphere(const vec3& c, const double& r,const color& col)
            : center{c}, radius{r}, surf_col{col} {}

    bool hit(const ray& ray, const interval& limit, hit_record& rec) const override{
        vec3 d = ray.get_direction();
        double a = dot(d, d);
        vec3 dis_OtoC = center - ray.get_origin();
        double b = -2 * dot(d, dis_OtoC);
        double c = dot(dis_OtoC, dis_OtoC) - std::pow(radius, 2);

        double discriminant = b * b - 4 * a * c;

        if(discriminant < 0) return false;

        double t{};
        t = (-b - sqrt(discriminant)) / (2*a);

        if(!limit.surrounds(t)){
            t = (-b + sqrt(discriminant)) / (2 * a);
            if(!limit.surrounds(t)){
                return false;
            }
        }

        rec.t = t;
        rec.p = ray.at(rec.t);
        rec.normal = unit_vector(rec.p - center);
        if (dot(rec.normal, ray.get_direction()) >= 0){
            rec.normal = -rec.normal;   
        }
        rec.hit_surf_col = surf_col;
        return true;
    }
};

#endif