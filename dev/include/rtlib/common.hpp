#ifndef COMMON_H
#define COMMON_H

#include <algorithm>
#include <cmath>
#include <memory>
#include <limits>

#include "ray.hpp"
#include "vec3.hpp"
#include "interval.hpp"

namespace CommonUtils
{
    constexpr double inf { std::numeric_limits<double>::infinity() };
    constexpr double pi { 3.14159265358979 };
    constexpr double epsilon { 1e-4f };
}

#endif