#ifndef HITTABLE_H
#define HITTABLE_H

#include "common.hpp"

class Hittable
{
public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray &ray, Interval ray_t, Hit& hit) const = 0;
};

#endif