#pragma once

#include "hittable.h"
#include "rtweekend.h"


class Sphere : public Hittable
{
public:
	Sphere(const RT::vec3& center,double radius)
	:m_Center(center),m_Radius(std::fmax(0,radius)){}

	bool hit(const Ray& r,interval ray_t, HitRecord& rec) const override
	{
		RT::vec3 oc = m_Center - r.Origin(); //(C-Q)
		auto a = r.Direction().length_squared();
		auto h = RT::dot(r.Direction(), oc);
		auto c = oc.length_squared() - m_Radius * m_Radius;

		auto discriminant = h * h - a * c;
		if(discriminant <0)
			return false;

		auto sqrtd = std::sqrt(discriminant);

		auto root = (h - sqrtd) / a;
		if (root <= ray_t.m_Min || ray_t.m_Max <= root) {
			root = (h + sqrtd) / a;
			if (root <= ray_t.m_Min || ray_t.m_Max <= root)
				return false;
		}

		rec.t = root;//交点
		rec.p = r.at(rec.t);//交点位置
		RT::vec3 outward_normal = (rec.p - m_Center) / m_Radius;//法线
		rec.SetFaceNormal(r, outward_normal);

		return true;
	}


private:
	RT::vec3 m_Center;
	double m_Radius;
};