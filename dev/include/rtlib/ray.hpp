#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"
#include "material.h"

class Ray
{
public:
    Ray() = default;
    Ray(const vec3 &origin, const vec3 &direction):
        origin { origin }, direction { direction } {}
    ~Ray() {}

    vec3 at(double t) const
    {
        return origin + direction * t;
    }

    vec3 origin;
    vec3 direction;
};

struct Hit
{
    double t;
    bool is_front;
    vec3 position;
    vec3 normal;
    Material material;

    void set_is_front(const Ray &ray, const vec3 &outward_normal)
    {
        is_front = dot(ray.direction, outward_normal) < 0;
        normal = is_front ? outward_normal : -outward_normal;
    }
};

#endif