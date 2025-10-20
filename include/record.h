#ifndef RECORD_H
#define RECORD_H

#include"vec3.h"
#include"ray.h"

class hit_record{
public:
    bool isHit = false;
    point3 p;
    vec3 normal;


};




#endif
