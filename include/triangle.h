#ifndef TRIANGLE_H
#define TRIANGLE_H
#include"hittable.h"

class triangle : public hittable{
public:
    triangle(const point3& a, const point3& b, const point3& c) : a{a}, b{b}, c{c} {}

    bool hit(const ray& ray, const interval& limit, hit_record& rec) const override{
        vec3 AB = b - a;
        vec3 AC = c - a;
        vec3 norm = unit_vector(cross(AB, AC));
        point3 pos = a;

        double DdotN = dot(ray.get_direction(), norm);
        
        if(fabs(DdotN) < 1e-6) return false;

        vec3 dis = pos - ray.get_origin();
        double nominator = dot(dis, norm);
        double t = nominator / DdotN;

        if (!limit.surrounds(t))
            return false;
        
        point3 p = ray.at(t);

        vec3 C0 = cross(b - a, p - a);
        vec3 C1 = cross(c - b, p - b);
        vec3 C2 = cross(a - c, p - c);

        if (dot(C0, norm) >= 0 && dot(C1, norm) >= 0 && dot(C2, norm) >= 0) {
            rec.t = t;
            rec.p = p;
            if (dot(ray.get_direction(), rec.normal) > 0)
                rec.normal = -rec.normal;
            rec.normal = norm;
            rec.hit_surf_col = color(1, 0, 0);
            return true;
        }
        return false;
    }
private:
    point3 a, b, c;

};

#endif