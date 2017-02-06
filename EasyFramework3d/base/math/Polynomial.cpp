#include <vs/base/math/Polynomial.h>
#include <cmath>
#include <iostream>

namespace vs
{
namespace base
{
namespace math
{
using namespace std;

Polynomial::Polynomial()
:degree(1), coefficients() 
{
    coefficients.push_back(0);
    coefficients.push_back(0);
}
/*
Polynomial::Polynomial(const Polynomial &rhs)
: degree(rhs.degree), coefficients(rhs.coefficients)
{}

Polynomial &Polynomial::operator=(const Polynomial &rhs)
{
    degree = rhs.degree;
    coefficients = rhs.coefficients;
}
*/
void Polynomial::setDegree(short degree)
{
    if (degree > this->degree)
        coefficients.insert(coefficients.end(), degree - this->degree, 0.0);

    this->degree = degree;
}

// TODO : Optimize this (maybe with a double array instead of an vector?)
double Polynomial::operator()(double x)
{
    double sum = coefficients[0] + coefficients[1]*x;
    for (int i = 2; i <= degree; i++)
    {
        sum += pow(x, i) * coefficients[i];
    }
    return sum;
}

Polynomial getFlightParable(double gravity, double distance, double planarV)
{
    Polynomial result;
    result.setDegree(2);
    result[0] = 0;
    result[2] = -4 * gravity;
    result[1] = -result[2] * distance / planarV ;

    return result;
}

ostream& operator<<(ostream &os, const Polynomial &p)
{
    os.precision(5);

    os << "f(x) = ";
    os << p.coefficients[0] << " + " << p.coefficients[1] << "x";

    for (int i = 2; i <= p.degree; i++)
    {
        os << " + " << p.coefficients[i] << "x^" << i;
    }
    return os;
}

int over(int a, int b)
{
    int result = a;
    for (int i = 1; i < b; i++)
    {
        result *= result-1;
    }
    return result;
}

Polynomial Polynomial::derivation(int n) const
{
    Polynomial d;
    if (n > degree)
    {
        d.setDegree(0);
        return d;
    }

    d.setDegree(degree-n);

    for (int i = n; i <= degree; i++)
    {
        d[i-n] = over(i, n) * coefficients[i];
    }

    return d;
}


} // math
} // base
} // vs
