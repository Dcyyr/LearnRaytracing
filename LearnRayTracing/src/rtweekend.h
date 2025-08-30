#pragma once


#include<cmath>
#include<iostream>
#include<limits>
#include<memory>
#include<cstdlib>
#include<random>
//constants
const double Infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;


//随机实数
inline double RandomDouble()// 返回一个在[0,1)区间内的随机实数。
{
	return std::rand() / (RAND_MAX + 1.0);
}

//inline double RandomDouble()
//{
//	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//	static std::mt19937 generator;
//	return distribution(generator);
//}

/*如果 x 是 [0, 1) 区间的随机数，想要得到 [a, b) 区间的随机数 y
	公式：y = a + (b - a) * x

*/
inline double RandomDouble(double min, double max)//返回一个在[min,max)区间内的随机实数。
{
	return min + (max - min) * RandomDouble();
}

inline double DegreesToRadians(double degrees)//角度转弧度
{
	return degrees * PI / 180.0;
}


#include"Ray.h"
#include"color.h"
#include"vec3.h"
#include"interval.h"