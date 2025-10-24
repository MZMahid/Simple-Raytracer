#ifndef HITTABLE_H
#define HITTABLE_H

#include"ray.h"
#include"record.h"
#include"interval.h"

class hittable {
private:

public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, const interval& limit, hit_record& record)
                                                                     const = 0;

};

#endif