#ifndef HITTABLE_H
#define HITTABLE_H

#include"ray.h"
#include"record.h"

class hittable {
private:

public:
    virtual ~hittable() = default;
    virtual void hit(const ray& r, hit_record& record) const = 0;

};

#endif