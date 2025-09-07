#pragma once

#include "hittable.h"

class Material
{
public:
	virtual ~Material() = default;

	/** 	const Ray& rayIn 入射到表面的光线。
			const HitRecord& rec 光线与物体表面相交时的命中信息（如交点、法线等）。
			RT::vec3& attenuation 光线经过材质后颜色的衰减（即能量损失或颜色变化），通常用于模拟材质的吸收或反射特性。
			Ray& scatter 散射后的新光线（即从表面弹射出去的光线）。
	**/

	virtual bool Scatter(const Ray& rayIn, const HitRecord& rec, RT::vec3& attenuation, Ray& scattered) const
	{
		return false;
	}



private:

};


class Lambertian : public Material
{
public:
	Lambertian(const RT::vec3& albedo)
		:m_Albedo(albedo)
	{
	}

	bool Scatter(const Ray& rayIn, const HitRecord& rec, RT::vec3& attenuation, Ray& scattered) const override
	{
		auto scatterDirection = rec.normal + RT::RandomUnitVector();

		if(scatterDirection.NearZero())
			scatterDirection = rec.normal;

		scattered = Ray(rec.p, scatterDirection);
		attenuation = m_Albedo;

		return true;
	}
private:
	RT::vec3 m_Albedo;
};

class Metal :public Material
{
public:

	Metal(const RT::vec3& albedo,double fuzz)
		:m_Albedo(albedo),m_Fuzz(fuzz <1 ? fuzz:1)
	{

	}

	bool Scatter(const Ray& rayIn, const HitRecord& rec, RT::vec3& attenuation, Ray& scattered) const override
	{
		auto Reflected = RT::Reflect(rayIn.Direction(), rec.normal);
		Reflected = RT::UnitVector(Reflected) + (m_Fuzz * RT::RandomUnitVector());
		scattered = Ray(rec.p, Reflected);
		attenuation = m_Albedo;
		return(RT::dot(scattered.Direction(), rec.normal) > 0);

	}

private:
	RT::vec3 m_Albedo;
	double m_Fuzz;
};
