#pragma once

#include"rtweekend.h"


namespace RT
{
    class vec3 {
    public:
        double e[3];

        vec3() : e{ 0,0,0 } {}
        vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        vec3& operator+=(const vec3& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }

        vec3& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator/=(double t) {
            return *this *= 1 / t;
        }

        //返回向量的实际长度（模）,得到实际的向量长度
        double length() const {
            return std::sqrt(length_squared());
        }

        ////返回向量的长度的平方,适合只比较距离大小时用
        double length_squared() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        bool NearZero()const
        {
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s);
        }

        static vec3 Random() 
        {
            return vec3(RandomDouble(), RandomDouble(), RandomDouble());
        }

        static vec3 Random(double min, double max)
        {
            return vec3(RandomDouble(min,max), RandomDouble(min,max), RandomDouble(min,max));
        }
        
    };

    // point3 is just an alias for vec3, but useful for geometric clarity in the code.
    using point3 = vec3;


    // Vector Utility Functions

    inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
        return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
    }

    inline vec3 operator+(const vec3& u, const vec3& v) {
        return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
    }

    inline vec3 operator-(const vec3& u, const vec3& v) {
        return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
    }

    inline vec3 operator*(const vec3& u, const vec3& v) {
        return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
    }

    inline vec3 operator*(double t, const vec3& v) {
        return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    inline vec3 operator*(const vec3& v, double t) {
        return t * v;
    }

    inline vec3 operator/(const vec3& v, double t) {
        return (1 / t) * v;
    }

    inline double dot(const vec3& u, const vec3& v) {
        return u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
    }

    inline vec3 cross(const vec3& u, const vec3& v) {
        return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
            u.e[2] * v.e[0] - u.e[0] * v.e[2],
            u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    inline vec3 UnitVector(const vec3& v) {//作用是把任意向量变成长度为 1 的单位向量，常用于只关心方向、不关心大小的场景。

        return v / v.length();
    }

    inline vec3 RandomUnitVector()
    {
        while (true)
        {
            auto p = vec3::Random(-1, 1);
            auto lensq = p.length_squared();
            if (1e-160 < lensq && lensq <= 1)
                return p / std::sqrt(lensq);
        }
    }

    inline vec3 RandomOnHemisphere(const vec3& normal)
    {
        vec3 onUnitSphere = RandomUnitVector();
        if (dot(onUnitSphere, normal) > 0.0)//与法线位于同一半球
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    inline vec3 Reflect(const vec3& v, const vec3& n)//计算入射向量 v 关于法线 n 的反射向量
    {
        return v - 2 * dot(v, n) * n;//dot(v, n) * n 得到 v 在法线方向上的投影。v - 2 * (投影)就是把 v 关于法线“翻折”到另一侧，得到反射方向。
   
    }
}