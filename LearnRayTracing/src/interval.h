#pragma once
#include "rtweekend.h"

//Çø¼äÀà
class Interval {
public:
    double m_Min, m_Max;

    Interval() : m_Min(+Infinity), m_Max(-Infinity) {} // Default interval is empty

    Interval(double min, double max) : m_Min(min), m_Max(max) {}

    double size() const {
        return m_Max - m_Min;
    }

    bool contains(double x) const {
        return m_Min <= x && x <= m_Max;
    }

    bool surrounds(double x) const {
        return m_Min < x && x < m_Max;
    }

    double clamp(double x)const
    {
        if (x < m_Min)return m_Min;
        if (x > m_Max)return m_Max;
        return x;
    }

    static const Interval s_Empty, s_Universe;
};

const Interval Interval::s_Empty = Interval(+Infinity, -Infinity);
const Interval Interval::s_Universe = Interval(-Infinity, +Infinity);