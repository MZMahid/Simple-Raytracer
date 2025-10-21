#ifndef RAY_H
#define RAY_H

#include"vec3.h"

class ray{
private:
    vec3 dir;
    point3 orig;
public:
    ray(const point3& o,const vec3& d): orig{o}, dir{d}{}

    point3 get_origin() const{ return orig; }
    vec3 get_direction() const { return dir; }

    vec3 at(const double& t) const{
        return orig + (dir * t);
    }

};


#endif