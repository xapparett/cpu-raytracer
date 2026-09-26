#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

class vec3
{
public:
    vec3() = default;
    vec3(double x, double y, double z):
        x { x }, y { y }, z { z } {}
    vec3(double a):
        x { a }, y { a }, z { a } {}
    ~vec3() {}

    vec3 operator-() const
    {
        return vec3 { -x, -y, -z };
    }

    vec3& operator+=(const vec3 &v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    vec3& operator-=(const vec3 &v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    vec3& operator*=(double t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    vec3& operator/=(double t)
    {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }

    double length() const
    {
        return std::sqrt(lensqr());
    }

    double lensqr() const
    {
        return x*x + y*y + z*z;
    }

    double x, y, z;
};

inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3 { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3 { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3 { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
}

inline vec3 operator*(const vec3 &v1, double v)
{
    return vec3 { v1.x * v, v1.y * v, v1.z * v };
}

inline vec3 operator/(const vec3 &v1, double v)
{
    return vec3 { v1.x / v, v1.y / v, v1.z / v };
}

inline double dot(const vec3 &v1, const vec3 &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
    return vec3 {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}

inline vec3 unit(const vec3 &v)
{
    return v / v.length();
}

inline vec3 reflect(const vec3 &v, const vec3 &n)
{
    double a { 2 * dot(v, n) };
    return v - ( vec3 { a, a, a } * n );
}

inline vec3 lerpv(const vec3 &v1, const vec3& v2, double t)
{
    return {
        std::lerp(v1.x, v2.x, t),
        std::lerp(v1.y, v2.y, t),
        std::lerp(v1.z, v2.z, t)
    };
}

#endif