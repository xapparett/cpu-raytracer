#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>

#include "common.hpp"
#include "hittable.h"

class World: public Hittable
{
public:
    World() {};
    ~World() {};

    void clear()
    {
        objects.clear();
    };

    void add(std::shared_ptr<Hittable> hittable)
    {
        objects.push_back(hittable);
    }

    bool hit(const Ray &ray, Interval ray_t, Hit &hit) const override
    {
        Hit temp;
        bool has_hit { false };
        double closest { ray_t.max };

        for (const auto &obj : objects)
        {
            if (obj->hit(ray, Interval { ray_t.min, closest }, temp))
            {
                has_hit = true;
                closest = temp.t;
                hit = temp;
            }
        }

        return has_hit;
    }

    std::vector<std::shared_ptr<Hittable>> objects;
};

#endif