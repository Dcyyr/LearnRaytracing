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

		//���ݹ����ǽ��뻹���뿪���ʣ�ѡ����ʵ�������
		double ri = rec.front_face ? (1.0 / m_RefractionIndex) : m_RefractionIndex;


		RT::vec3 unitDirection = RT::UnitVector(rayIn.Direction());

		//���������㹻б�ĽǶȽ��������ʽϵ͵Ľ���ʱ�������ܻ��Դ��� 90��ĽǶȷ�������,��ʽ���ߵ���ȹ�ϵ���ƻ����Ҳ����ڽ⡣��������ڽ⣬�����޷����䣬��˱��뷴����ߣ�


		double cos_thete = std::fmin(dot(-unitDirection, rec.normal), 1.0);
		double sin_theta = std::sqrt(1.0 - cos_thete * cos_thete);

		bool cannotRefract = ri * sin_theta > 1.0;
		RT::vec3 direction;

		//����������䣨ȫ���䣩��������ߣ����򣬸���˹�������ɼ����������
		if (cannotRefract || Reflectance(cos_thete,ri) > RandomDouble())
			direction = RT::Reflect(unitDirection, rec.normal);
		else
			direction = RT::Refract(unitDirection, rec.normal, ri);


		scattered = Ray(rec.p, direction);
		return true;

	}



private:
	//��ջ�����е������ʣ����������������������������֮��
	double m_RefractionIndex;

	static double Reflectance(double cos, double refractionIndex)
	{
		//ʹ�� Schlick ���Ƽ��㷴����
		auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
		r0 = r0 * r0;
		return r0 + (1 - r0) * std::pow((1 - cos), 5);
	}
};