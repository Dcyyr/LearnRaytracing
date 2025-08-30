#pragma once
#include "interval.h"
//#include <glm/glm.hpp>
#include "rtweekend.h"

void WirteColor(std::ostream& out, const RT::vec3& pixelColor)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();


	static const Interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}