#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.hpp"

struct Material
{
public:
    Material() = default;
    Material(double specStrength, double shininess, bool is_reflective, const vec3 &color):
        specularStrength { specStrength }, shininess { shininess }, is_reflective { is_reflective }, color { color } {}
    ~Material() {}

    double specularStrength;
    double shininess;
    bool is_reflective;

    vec3 color;
};

#endif