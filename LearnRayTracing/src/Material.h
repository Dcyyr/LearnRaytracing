#pragma once

#include "hittable.h"

class Material
{
public:
	virtual ~Material() = default;

	/** 	const Ray& rayIn ���䵽����Ĺ��ߡ�
			const HitRecord& rec ��������������ཻʱ��������Ϣ���罻�㡢���ߵȣ���
			RT::vec3& attenuation ���߾������ʺ���ɫ��˥������������ʧ����ɫ�仯����ͨ������ģ����ʵ����ջ������ԡ�
			Ray& scatter ɢ�����¹��ߣ����ӱ��浯���ȥ�Ĺ��ߣ���
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

	Metal(const RT::vec3& albedo)
		:m_Albedo(albedo)
	{

	}

	bool Scatter(const Ray& rayIn, const HitRecord& rec, RT::vec3& attenuation, Ray& scattered) const override
	{
		auto Reflected = RT::Reflect(rayIn.Direction(), rec.normal);
		scattered = Ray(rec.p, Reflected);
		attenuation = m_Albedo;
		return true;

	}

private:
	RT::vec3 m_Albedo;
};
