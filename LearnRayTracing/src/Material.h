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

class Dielectric : public Material
{
public:
	Dielectric(double refractionindex)
		:m_RefractionIndex(refractionindex)
	{

	}


	bool Scatter(const Ray& rayIn, const HitRecord& rec, RT::vec3& attenuation, Ray& scattered)const override
	{
		attenuation = RT::vec3(1.0, 1.0, 1.0);

		//根据光线是进入还是离开介质，选择合适的折射率
		double ri = rec.front_face ? (1.0 / m_RefractionIndex) : m_RefractionIndex;


		RT::vec3 unitDirection = RT::UnitVector(rayIn.Direction());

		//当光线以足够斜的角度进入折射率较低的介质时，它可能会以大于 90°的角度发生折射,等式两边的相等关系被破坏，且不存在解。如果不存在解，玻璃无法折射，因此必须反射光线：


		double cos_thete = std::fmin(dot(-unitDirection, rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_thete * cos_thete);

		bool cannotRefract = ri * sin_theta > 1.0;
		RT::vec3 direction;

		//如果不能折射（全反射），则反射光线；否则，根据斯涅尔定律计算折射光线
		if (cannotRefract || Reflectance(cos_thete,ri) > RandomDouble())
			direction = RT::Reflect(unitDirection, rec.normal);
		else
			direction = RT::Refract(unitDirection, rec.normal, ri);


		scattered = Ray(rec.p, direction);
		return true;

	}



private:
	//真空或空气中的折射率，或材料折射率与所处介质折射率之比
	double m_RefractionIndex;

	static double Reflectance(double cos, double refractionIndex)
	{
		//使用 Schlick 近似计算反射率
		auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cos), 5);
	}
};