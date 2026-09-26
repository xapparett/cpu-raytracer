#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "rt.h"

int main()
{
    RT raytracer { 1280, 720 };
    raytracer.init();
    raytracer.render();

    return 0;
}