#ifndef HITTABLE_H
#define HITTABLE_H

#include"ray.h"
#include"record.h"

class hittable {
private:

public:
    virtual void hit(const ray& r,const hit_record& record){}

};

#endif