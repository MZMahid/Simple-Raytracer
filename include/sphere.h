#ifndef SPHERE_H
#define SPHERE_H

#include"hittable.h"

class sphere : public hittable {

public:
    vec3 center;
    double radius;
    sphere(const vec3& c, const double& r) : center{c}, radius{r} {}

    void hit(const ray& ray, hit_record& rec) const override{
        vec3 d = ray.get_direction();
        double a = dot(d, d);
        vec3 dis = center - ray.get_origin();
        double b = -2 * dot(d, dis);
        double c = dot(dis, dis) - std::pow(radius, 2);

        if( (b * b - 4*a*c) > 0 ){
            rec.isHit = true;
        }
    }
};

#endif