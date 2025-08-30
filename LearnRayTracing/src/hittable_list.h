#pragma once

#include "hittable.h"

#include "rtweekend.h"
#include<vector>

class HittableList : public Hittable
{
public:
	std::vector<std::shared_ptr<Hittable>> objects;


	HittableList() {}
	HittableList(std::shared_ptr<Hittable> object) { Add(object); }

	void Clear() { objects.clear(); }

	void Add(std::shared_ptr<Hittable> object)
	{
		objects.push_back(object);
	}

	bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override
	{
		HitRecord temprec;
		bool hit_anything = false;
		auto closest_so_far = ray_t.m_Max;

		for (const auto& object : objects)
		{
			if(object->hit(r, Interval(ray_t.m_Min, closest_so_far), temprec))
			{
				hit_anything = true;
				closest_so_far = temprec.t;
				rec = temprec;
			}
		}

		return hit_anything;
	}
};