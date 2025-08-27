#pragma once


#include<cmath>
#include<iostream>
#include<limits>
#include<memory>

//constants
const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;


inline double DegreesToRadians(double degrees)//½Ç¶È×ª»¡¶È
{
	return degrees * PI / 180.0;
}


#include"Ray.h"
#include"color.h"
#include"vec3.h"
#include"interval.h"