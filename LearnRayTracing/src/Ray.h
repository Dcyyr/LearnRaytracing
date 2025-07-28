#pragma once
//#include<glm/glm.hpp>
#include "vec3.h"
class Ray
{
public:
	Ray() {}
	Ray(const  RT::vec3& origin, const RT::vec3& direction)
		:m_Origin(origin), m_Dir(direction) {
	}

	const RT::vec3& Origin() const{ return m_Origin; }
	const RT::vec3& Direction() const{ return m_Dir; }

	RT::vec3 at(float t)const
	{
		return m_Origin + t * m_Dir;
	}

private:
	RT::vec3 m_Origin;
	RT::vec3 m_Dir;

};