#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>

#include "vec3.hpp"

class Camera
{
public:
    Camera(const vec3 &position, double focal_length):
        position { position }, focal_length { focal_length } {}
    ~Camera() {}

    void init(int W, int H)
    {
        viewport_height = 2.0;
        viewport_width = viewport_height * (static_cast<double>(W) / H);
        viewport_u = vec3 { viewport_width, 0.0, 0.0 };
        viewport_v = vec3 { 0.0, -viewport_height, 0.0 };
        pixel_u = viewport_u / W;
        pixel_v = viewport_v / H;

        viewport_upper_left = position - vec3 { 0.0, 0.0, focal_length } - viewport_u/2 - viewport_v/2;
        pixel_loc = viewport_upper_left + (pixel_u + pixel_v) * 0.5;
    }

    double focal_length;
    double viewport_width;
    double viewport_height;

    vec3 viewport_u;
    vec3 viewport_v;
    vec3 pixel_u;
    vec3 pixel_v;
    vec3 pixel_loc;
    vec3 viewport_upper_left;
    vec3 position;
};

#endif