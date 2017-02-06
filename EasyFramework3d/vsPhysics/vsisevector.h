/*
  Name: vsIseVector.h
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 19:38
  Description: blabla
*/

#ifndef VSISEVECTOR_H
#define VSISEVECTOR_H

#include "vsIse.h"

/*
 * No description
 */
class vsIseVector
{
	public:
		vsIseVector();
		vsIseVector(vsIse x, vsIse y, vsIse z);
		vsIseVector(double x, double y, double z);
		vsIseVector(const vsDoubleVector &vector);
		vsIseVector(const vsIseVector &vector);
		~vsIseVector();
		
		void setX(vsIse x) { this->x = x; }
		vsIse getX() const { return x; }

		void setY(vsIse x) { this->y = y; }
		vsIse getY() const { return y; }

		void setZ(vsIse x) { this->z = z; }
		vsIse getZ() const { return z; }

		
		vsIseVector &operator+=(const vsIseVector &vector);
		vsIseVector operator+(const vsIseVector &vector);
		
		vsIseVector &operator+=(const vsDoubleVector &vector);
		vsIseVector operator+(const vsDoubleVector &vector);
		
		vsIseVector &operator-=(const vsIseVector &vector);
		vsIseVector operator-(const vsIseVector &vector);
		
		vsIseVector &operator-=(const vsDoubleVector &vector);
		vsIseVector operator-(const vsDoubleVector &vector);

		vsIseVector &operator*=(const double &scalar);
		vsIseVector operator*(const double &scalar);
		
		vsIseVector operator=(vsIseVector vector);
		vsIseVector operator=(vsDoubleVector vector);
		
		// ignore all higher digits of the components and give only their doubles
		vsDoubleVector toDoubleVector() const;
		
		// Skalarprodukt und Kreuzprodukt (auf englisch?)
		// vsIseVector dot(vsIseVector
	protected:
		// Coordinates
		vsIse x;
		vsIse y;
		vsIse z;
};

#endif // VSISEVECTOR_H
