#pragma once
#include "rtweekend.h"

//Çø¼äÀà
class interval {
public:
    double m_Min, m_Max;

    interval() : m_Min(+Infinity), m_Max(-Infinity) {} // Default interval is empty

    interval(double min, double max) : m_Min(min), m_Max(max) {}

    double size() const {
        return m_Max - m_Min;
    }

    bool contains(double x) const {
        return m_Min <= x && x <= m_Max;
    }

    bool surrounds(double x) const {
        return m_Min < x && x < m_Max;
    }

    static const interval s_Empty, s_Universe;
};

const interval interval::s_Empty = interval(+Infinity, -Infinity);
const interval interval::s_Universe = interval(-Infinity, +Infinity);