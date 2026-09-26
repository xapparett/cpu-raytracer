#ifndef GRAPHICS_UTILS_HPP
#define GRAPHICS_UTILS_HPP

#include "common.hpp"

namespace GraphicsUtils
{
    const vec3 SKY_COLOR_HORIZON { 1.0 };
    const vec3 SKY_COLOR_ZENITH { 0.55, 0.55, 1.0 };
    const vec3 GROUND_COLOR { 0.4 };

    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/smoothstep.xhtml
    inline double smoothstep(double edge0, double edge1, double x)
    {
        double t { std::clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0) };
        return t * t * (3.0 - 2.0 * t);
    }
}

#endif