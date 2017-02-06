/*
  Name: vsIseVector.cpp
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:07
  Description: 
*/

#include "vsisevector.h"
#include "vsdoublevector.h"

vsIseVector::vsIseVector()
:x(), y(), z()
{
}

vsIseVector::vsIseVector(vsIse x, vsIse y, vsIse z)
: this->x(x), this->y(y), this->y(y)
{
}

vsIseVector(double x, double y, double z)
: this->x(x), this->y(y), this->y(y)
{
}

vsIseVector::vsIseVector(const vsDoubleVector &vector)
: x(vector.x), y(vector.y), z(vector.z)
{
}

vsIseVector::vsIseVector(const vsIseVector &vector)
:x(vector.x), y(vector.y), z(vector.z)
{
}

vsIseVector::~vsIseVector()
{
	// insert your code here
}

vsIseVector &vsIseVector::operator+=(const vsIseVector &vector)
{
	x += vector.x; y += vector.y; z += vector.z;
	return *this;
}

vsIseVector vsIseVector::operator+(const vsIseVector &vector)
{
	vsIseVector temp(x, y, z);
	return temp += vector;
}

vsIseVector &vsIseVector::operator+=(const vsDoubleVector &vector)
{
	x += vector.getX(); y += vector.getY(); z += vector.getZ();
	return *this;
}

vsIseVector vsIseVector::operator+(const vsDoubleVector &vector)
{
	vsIseVector temp(x, y, z);
	return temp += vector;
}


vsIseVector &vsIseVector::operator-=(const vsIseVector &vector)
{
	x -= vector.x; y -= vector.y; z -= vector.z;
	return *this;
}

vsIseVector vsIseVector::operator-(const vsIseVector &vector)
{
	vsIseVector temp(x, y, z);
	return temp -= vector;
}

vsIseVector &vsIseVector::operator-=(const vsDoubleVector &vector)
{
	x -= vector.getX(); y -= vector.getY(); z -= vector.getZ();
	return *this;
}

vsIseVector vsIseVector::operator-(const vsDoubleVector &vector)
{
	vsIseVector temp(x, y, z);
	return temp -= vector;
}

vsIseVector &vsIseVector::operator*=(const double &scalar)
{
	x *= scalar; y *= scalar; z *= scalar;
	return *this;
}

vsIseVector &vsIseVector::operator*(const double &scalar)
{
	vsIseVector temp(x, y, z);
	return temp *= scalar;
}

vsIseVector &vsIseVector::operator=(const vsIseVector &vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	
	return *this;
}

vsIseVector &vsIseVector::operator=(const vsDoubleVector &vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	
	return *this;
}

// TODO : sqrt funktion überladen
//double vsIseVector::abs() const
//{
//	return sqrt(x*x + y*y + z*z);
//}

vsIse vsIseVector::abs_sqr() const
{
	return (x*x + y*y + z*z);
}

vsDoubleVector vsIseVector::toDoubleVector() const
{
	return vsDoubleVector(x.getZiffer(), y.getZiffer(), z.getZiffer());
}
