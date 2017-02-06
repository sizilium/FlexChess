/**
 * @file DoubleVector.h
 * DoubleVector class for x, y, z coordinate (3 * double) with a lot of
 * overloaded operators and functions.
 *
*/

#ifndef VSDOUBLEVECTOR_H
#define VSDOUBLEVECTOR_H

// includes
#include <vs/Build.hpp>
#include <cmath>
#include <string>
#include <fstream>

namespace vs
{
namespace base
{
namespace math
{

using namespace std;

/**
 * the DoubleVector class contains three double values.
 * It can be used vor 3d coordinates or euler (rotation) for example
 */
class VS_EXPORT DoubleVector
{
public:
	DoubleVector();
	~DoubleVector();
	DoubleVector(double x, double y, double z);
	DoubleVector(double *coords);
	DoubleVector(float *coords);
	DoubleVector(const DoubleVector &vector);

	void x(double x) { xCoord = x; }
	double x() const { return xCoord; }

	void y(double y) { yCoord = y; }
	double y() const { return yCoord; }

	void z(double z) { zCoord = z; }
	double z() const { return zCoord; }

	void set(double x, double y, double z) { xCoord = x; yCoord = y; zCoord = z; }

	bool operator==(const DoubleVector &vector) const;
	
	DoubleVector &operator+=(const DoubleVector &vector);
	DoubleVector operator+(const DoubleVector &vector) const;

	DoubleVector &operator-=(const DoubleVector &vector);
	DoubleVector operator-(const DoubleVector &vector) const;

	DoubleVector &operator*=(const double &scalar);
	DoubleVector operator*(const double &scalar) const;

	DoubleVector &operator/=(const double &scalar);
	DoubleVector operator/(const double &scalar) const;

	DoubleVector &operator=(const DoubleVector &vector);

	double &operator[](unsigned int n);

    /**
    * calculates the cross product
    */
	DoubleVector &operator%=(const DoubleVector &vector);

    /**
    * calculates the cross product
    */
	DoubleVector operator%(const DoubleVector &vector);

    /**
    * calculates the scalar product
    */
	double operator*(const DoubleVector &vector);

    /**
     * returns the absolute quadratic value of coordinate
     * (faster than abs() )
     */
     double abs_sqr() const { return (xCoord*xCoord + yCoord*yCoord + zCoord*zCoord); }

	/**
	 * returns the absolute value of the coordinates
     */
	double abs() const { return sqrt(abs_sqr()); }

	double* toArray() const;
	float* toArrayF() const;
	
    friend ostream& operator<<(ostream &os, const DoubleVector &v);

protected:
	// values
	double xCoord;
	double yCoord;
	double zCoord;
};

VS_EXPORT ostream& operator<<(ostream &os, const DoubleVector &v);

} // math
} // base
} // vs

#endif // VSDOUBLEVECTOR_H
