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


//���ʵ��
inline double RandomDouble()// ����һ����[0,1)�����ڵ����ʵ����
{
	return std::rand() / (RAND_MAX + 1.0);
}

//inline double RandomDouble()
//{
//	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//	static std::mt19937 generator;
//	return distribution(generator);
//}

/*��� x �� [0, 1) ��������������Ҫ�õ� [a, b) ���������� y
	��ʽ��y = a + (b - a) * x

*/
inline double RandomDouble(double min, double max)//����һ����[min,max)�����ڵ����ʵ����
{
	return min + (max - min) * RandomDouble();
}

inline double DegreesToRadians(double degrees)//�Ƕ�ת����
{
	return degrees * PI / 180.0;
}


#include"Ray.h"
#include"color.h"
#include"vec3.h"
#include"interval.h"