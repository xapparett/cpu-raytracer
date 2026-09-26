#ifndef RT_H
#define RT_H

#include <cstdint>
#include <algorithm>

#include <iomanip>
#include <ctime>

#include <format>
#include <string>
#include <sstream>

#include "stb_image_write.h"

#include "rtlib/hittable.h"
#include "rtlib/material.h"

#include "rtlib/common.hpp"
#include "rtlib/graphicsu.hpp"

#include "rtlib/sphere.hpp"
#include "rtlib/camera.hpp"
#include "rtlib/world.hpp"

class RT
{
private:
    uint8_t* m_Image;

    int m_Width;
    int m_Height;
public:
    RT(int W, int H);
    ~RT();

    vec3 color(const Ray &ray, const vec3 &cameraPos, const vec3 &lightPos, int depth = 0);

    void init();
    void render();

    World world;
};

#endif