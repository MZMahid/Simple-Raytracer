#ifndef PLANE_H
#define PLANE_H

#include"global.h"

class plane : public hittable{
public:

    plane(const point3& position, const vec3& normal, const color& surf_color) 
        : pos{position}, norm{unit_vector(normal)}, surf_col{surf_color}{}

    bool hit(const ray& ray, const interval& limit, hit_record& rec) const override{
        double DdotN = dot(ray.get_direction(), norm);
        if(fabs(DdotN) < 1e-6) return false;

        vec3 dis = pos - ray.get_origin();
        double nominator = dot(dis, norm);
        double t = nominator / DdotN;

        if (!limit.surrounds(t))
            return false;

        rec.p = ray.at(t);
        rec.t = t;
        rec.isHit = true;

        if (dot(ray.get_direction(), rec.normal) > 0)
            rec.normal = -rec.normal;
        rec.normal = norm;
        
        rec.hit_surf_col = surf_col;

        return true;

    }
private:
    point3 pos;
    vec3 norm;
    color surf_col;
};

#endif