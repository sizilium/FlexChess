/*
  Name: vsDoubleVector.h
  Copyright: VS
  Author: Maccesch
  Date: 05.05.05 23:41
  Description: 
*/

#ifndef VSDOUBLEVECTOR_H
#define VSDOUBLEVECTOR_H

class vsDoubleVector
{
	public:
		vsDoubleVector();
		~vsDoubleVector();
		vsDoubleVector(double x, double y, double z);
		vsDoubleVector(const vsDoubleVector &vector);
		
		void setX(double x) { this->x = x; }
		double getX() const { return x; }


		void setY(double x) { this->y = y; }
		double getY() const { return y; }

		void setZ(double x) { this->z = z; }
		double getZ() const { return z; }

		
		vsDoubleVector &operator+=(const vsDoubleVector &vector);
		vsDoubleVector operator+(const vsDoubleVector &vector);
		
		vsDoubleVector &operator-=(const vsDoubleVector &vector);
		vsDoubleVector operator-(const vsDoubleVector &vector);

		vsDoubleVector &operator*=(const double &scalar);
		vsDoubleVector operator*(const double &scalar);
		
		vsDoubleVector operator=(vsDoubleVector vector);
		
		// Skalarprodukt und Kreuzprodukt (auf englisch?)
		// vsDoubleVector dot(vsDoubleVector
	protected:
		// Coordinates
		double x;
		double y;
		double z;
};

#endif // VSDOUBLEVECTOR_H
