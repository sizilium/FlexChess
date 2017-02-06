/*
  Name: doubleVector.cpp
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:42
  Description: 
*/

#include "doublevector.h"

vsDoubleVector::vsDoubleVector()
: x(0), y(0), z(0)
{
}

vsDoubleVector::~vsDoubleVector()
{
}

vsDoubleVector::vsDoubleVector(double x, double y, double z)
: this->x(x), this->y(y), this->y(y)
{
}

vsDoubleVector::vsDoubleVector(const vsDoubleVector &vector)
: x(vector.x), y(vector.y), z(vector.z)
{
}

vsDoubleVector &doubleVector::operator+=(const vsDoubleVector &vector)
{
	x += vector.x; y += vector.y; z += vector.z;
	return *this;
}

vsDoubleVector doubleVector::operator+(const vsDoubleVector &vector)
{
	doubleVector temp(x, y, z);
	return temp += vector;
}

vsDoubleVector &doubleVector::operator-=(const vsDoubleVector &vector)
{
	x -= vector.x; y -= vector.y; z -= vector.z;
	return *this;
}

vsDoubleVector doubleVector::operator-(const vsDoubleVector &vector)
{
	doubleVector temp(x, y, z);
	return temp -= vector;
}

vsDoubleVector &doubleVector::operator*=(const double &scalar)
{
	x *= scalar; y *= scalar; z *= scalar;
	return *this;
}

vsDoubleVector &doubleVector::operator*(const double &scalar)
{
	doubleVector temp(x, y, z);
	return temp *= scalar;
}

vsDoubleVector &doubleVector::operator=(const vsDoubleVector &vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	
	return *this;
}

double vsDoubleVector::abs() const
{
	return sqrt(x*x + y*y + z*z);
}

double vsDoubleVector::abs_sqr() const
{
	return (x*x + y*y + z*z);
}
