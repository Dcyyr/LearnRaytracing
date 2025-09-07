#pragma once

#include"rtweekend.h"

class Material;

class HitRecord
{
public:
	RT::vec3 p;//���е�
	RT::vec3 normal;//����
	double t;
	bool front_face;//�����Ƿ�������������
	std::shared_ptr<Material> m_Mat;


	void SetFaceNormal(const Ray& r, const RT::vec3& outway_normal)
	{
		// ������ײ��¼�ķ���������
		// ע�⣺���� `outward_normal` ������е�λ����
		front_face = RT::dot(r.Direction(), outway_normal) < 0;
		normal = front_face ? outway_normal : -outway_normal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r,Interval ray_t, HitRecord& rec) const = 0;

};

