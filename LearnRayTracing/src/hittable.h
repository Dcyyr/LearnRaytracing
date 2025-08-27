#pragma once

#include"rtweekend.h"

class HitRecord
{
public:
	RT::vec3 p;//命中点
	RT::vec3 normal;//法线
	double t;
	bool front_face;//射线是否击中物体的正面

	void SetFaceNormal(const Ray& r, const RT::vec3& outway_normal)
	{
		// 设置碰撞记录的法线向量。
		// 注意：参数 `outward_normal` 假设具有单位长度
		front_face = RT::dot(r.Direction(), outway_normal) < 0;
		normal = front_face ? outway_normal : -outway_normal;
	}
};

class Hittable
{
public:
	virtual ~Hittable() = default;

	virtual bool hit(const Ray& r,interval ray_t, HitRecord& rec) const = 0;

};

