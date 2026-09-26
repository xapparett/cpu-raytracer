#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <cmath>

#include "common.hpp"
#include "hittable.h"
#include "material.h"

class Sphere: public Hittable
{
public:
    Sphere(double radius, const vec3 &origin, const Material &material):
        radius { radius }, origin { origin }, material { material } {}
    ~Sphere() {}

    bool hit(const Ray &ray, Interval ray_t, Hit& hit) const override
    {
        vec3 to { origin - ray.origin };
        double quadratic { ray.direction.lensqr() };
        double linear { dot(ray.direction, to) };
        double constterm { to.lensqr() - radius*radius };

        double discriminant { linear*linear - quadratic * constterm };
        if (discriminant < 0)
            return false;

        double sqrtd { std::sqrt(discriminant) };

        double root { (linear - sqrtd) / quadratic };
        if (!ray_t.surrounds(root))
        {
            root = (linear + sqrtd) / quadratic;
            if (!ray_t.surrounds(root))
                return false;
        }

        hit.t = root;
        hit.position = ray.at(hit.t);
        hit.material = material;

        vec3 outward_normal = (hit.position - origin) / radius;
        hit.set_is_front(ray, outward_normal);

        return true;
    }

    double radius;
    vec3 origin;
    Material material;
};

#endif