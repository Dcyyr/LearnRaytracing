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

        //����������ʵ�ʳ��ȣ�ģ��,�õ�ʵ�ʵ���������
        double length() const {
            return std::sqrt(length_squared());
        }

        ////���������ĳ��ȵ�ƽ��,�ʺ�ֻ�ȽϾ����Сʱ��
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

    inline vec3 UnitVector(const vec3& v) {//�����ǰ�����������ɳ���Ϊ 1 �ĵ�λ������������ֻ���ķ��򡢲����Ĵ�С�ĳ�����

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
        if (dot(onUnitSphere, normal) > 0.0)//�뷨��λ��ͬһ����
            return onUnitSphere;
        else
            return -onUnitSphere;
    }

    inline vec3 Reflect(const vec3& v, const vec3& n)//������������ v ���ڷ��� n �ķ�������
    {
        return v - 2 * dot(v, n) * n;//dot(v, n) * n �õ� v �ڷ��߷����ϵ�ͶӰ��v - 2 * (ͶӰ)���ǰ� v ���ڷ��ߡ����ۡ�����һ�࣬�õ����䷽��
   
    }
}