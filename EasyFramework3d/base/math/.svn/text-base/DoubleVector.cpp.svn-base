#include <vs/base/math/DoubleVector.h>
#include <vs/base/util/Time.h>
#include <cassert>
#include <iomanip>

namespace vs
{
namespace base
{
namespace math
{
using namespace std;

DoubleVector::DoubleVector()
: xCoord(0), yCoord(0), zCoord(0)
{}

DoubleVector::~DoubleVector()
{}

DoubleVector::DoubleVector(double x, double y, double z)
: xCoord(x), yCoord(y), zCoord(z)
{}

DoubleVector::DoubleVector(double *coords)
: xCoord(coords[0]), yCoord(coords[1]), zCoord(coords[2])
{}

DoubleVector::DoubleVector(float *coords)
: xCoord(coords[0]), yCoord(coords[1]), zCoord(coords[2])
{}

DoubleVector::DoubleVector(const DoubleVector &vector)
: xCoord(vector.x()), yCoord(vector.y()), zCoord(vector.z())
{}

bool DoubleVector::operator==(const DoubleVector &vector) const
{
	if (xCoord == vector.x() && yCoord == vector.y() && zCoord == vector.z())
		return true;
	else
		return false;
}

DoubleVector &DoubleVector::operator+=(const DoubleVector &vector)
{
	xCoord += vector.x();
	yCoord += vector.y();
	zCoord += vector.z();
	return *this;
}

DoubleVector DoubleVector::operator+(const DoubleVector &vector) const
{
	DoubleVector temp(xCoord, yCoord, zCoord);
	return temp += vector;
}

DoubleVector &DoubleVector::operator-=(const DoubleVector &vector)
{
	xCoord -= vector.x();
	yCoord -= vector.y();
	zCoord -= vector.z();
	return *this;
}

DoubleVector DoubleVector::operator-(const DoubleVector &vector) const
{
	DoubleVector temp(xCoord, yCoord, zCoord);
	return temp -= vector;
}

DoubleVector &DoubleVector::operator*=(const double &scalar)
{
	xCoord *= scalar;
	yCoord *= scalar;
	zCoord *= scalar;
	return *this;
}

DoubleVector DoubleVector::operator*(const double &scalar) const
{
	DoubleVector temp(xCoord, yCoord, zCoord);
	return temp *= scalar;
}

DoubleVector &DoubleVector::operator/=(const double &scalar)
{
	xCoord /= scalar;
	yCoord /= scalar;
	zCoord /= scalar;
	return *this;
}

DoubleVector DoubleVector::operator/(const double &scalar) const
{
	DoubleVector temp(xCoord, yCoord, zCoord);
	return temp /= scalar;
}

DoubleVector& DoubleVector::operator=(const DoubleVector &vector)
{
	xCoord = vector.x();
	yCoord = vector.y();
	zCoord = vector.z();

	return *this;
}

double& DoubleVector::operator[](unsigned int n)
{
    if (n == 0)
        return xCoord;
    else if (n == 1)
        return yCoord;
    else if (n == 2)
        return zCoord;
    else
	{
        assert("Invalid index was used!" && false);
		return xCoord;
	}
}

DoubleVector &DoubleVector::operator%=(const DoubleVector &vector) {
    double xt = yCoord * vector.z() - zCoord * vector.y();
    double yt = zCoord * vector.x() - xCoord * vector.z();
    zCoord = xCoord * vector.y() - yCoord * vector.x();
    xCoord = xt;
    yCoord = yt;
    return *this;
}

DoubleVector DoubleVector::operator%(const DoubleVector &vector) {
    DoubleVector temp(*this);
    return temp %= vector;
}

double DoubleVector::operator*(const DoubleVector &vector) {
    return xCoord*vector.x() + yCoord*vector.y() + zCoord*vector.z();
}

double* DoubleVector::toArray() const
{
	double *retVal = new double[3];
	retVal[0] = xCoord;
	retVal[1] = yCoord;
	retVal[2] = zCoord;
	return retVal;
}

float* DoubleVector::toArrayF() const
{
	float *retVal = new float[3];
	retVal[0] = static_cast<float> (xCoord);
	retVal[1] = static_cast<float> (yCoord);
	retVal[2] = static_cast<float> (zCoord);
	return retVal;
}

ostream& operator<<(ostream &os, const DoubleVector &v)
{
    os.precision(5);

    os << "(" << left <<
    setw(6) << v.xCoord <<", "<<
    setw(6) << v.yCoord <<", "<<
    setw(6) << v.zCoord <<")";
    return os;
}
} // math
} // base
} // vs
