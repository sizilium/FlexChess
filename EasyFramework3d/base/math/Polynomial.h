#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

// includes
#include <vs/Build.hpp>
#include <cassert>
#include <vector>
#include <string>
#include <fstream>

namespace vs
{
namespace base
{
namespace math
{
using namespace std;

// TODO : Specialize (parables...)
/**
 * @class Polynomial
 * A polynomial coefficients[0] + coefficients[1] * x + coefficients[2] * x^2 + ...
 */
class VS_EXPORT Polynomial {

public:
    Polynomial();
/*    Polynomial(const Polynomial &rhs);

    Polynomial &operator=(const Polynomial &rhs);
*/
    /** setter for degree
     * @param degree The new degree
     */
    void setDegree(short degree);

    /** getter for degree
     * @return
     */
    short getDegree() const	{return degree;}

	double &operator[](short i)
	{
		assert(i >= 0 && i <= degree);
		return coefficients[i];
	}
	Polynomial &operator+=(double x) {
		coefficients[0] += x;
		return *this;
	}
	Polynomial operator+(double x) {
		Polynomial temp(*this);
		return temp += x;
	}

	double operator()(double x);

	// TODO? : A lot of more operators

    friend ostream& operator<<(ostream &os, const Polynomial &p);

    Polynomial derivation(int n) const;
protected:
	short degree;
	vector<double> coefficients;
};

VS_EXPORT ostream& operator<<(ostream &os, const Polynomial &p);

// TODO? : Parable
// TODO? : Formula in comment
/**
 * Calculates the flight path parable f(t), which gives the height dependent on
 * the passed time, with the given gravity, distance and the
 * planar velocity, that is velocity without the height component.
 * @param gravity   The acceleration of gravity on the flying object
 * @param distance  The distance from the start at height 0 to the target at height 0
 * @param planarV   The planar (projected) velocity of the flying object
 * @return The resulting flight path parable
 */
VS_EXPORT Polynomial getFlightParable(double gravity, double distance, double planarV);

} // math
} // base
} // vs
#endif // POLYNOMIAL_H
