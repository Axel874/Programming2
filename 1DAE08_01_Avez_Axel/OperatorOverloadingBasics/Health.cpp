#include "pch.h"
#include "Health.h"

Health::Health(int value)
	: m_Value{ value }
{
}
int Health::GetValue() const
{
	return m_Value;
}

Health& Health::operator+=(int rhs) { this->m_Value += rhs; return *this; }
Health& Health::operator-=(int rhs) { this->m_Value -= rhs; return *this; }
Health& Health::operator+=(const Health& rhs) { *this += rhs.m_Value; return *this; }
Health& Health::operator-=(const Health& rhs) { *this -= rhs.m_Value; return *this; }
Health Health::operator-() const { return Health(-this->m_Value); }

Health& operator+(Health lhs, const int rhs) { return lhs += rhs; }
Health& operator+(int rhs, const Health& lhs) { return lhs + rhs; }
Health& operator+(Health rhs, const Health& lhs) { return rhs += lhs; }
Health& operator-(Health lhs, const int rhs) { return lhs -= rhs; }
Health& operator-(int rhs, const Health& lhs) { return -lhs + rhs; }
Health& operator-(Health rhs, const Health& lhs) { return rhs -= lhs; }


