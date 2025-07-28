#pragma once

//#include <glm/glm.hpp>
#include "vec3.h"
#include <iostream>

void WirteColor(std::ostream& out, const RT::vec3& pixelColor)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	int rbyte = int(255.999 * r);
	int gbyte = int(255.999 * g);
	int bbyte = int(255.999 * b);

	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

}