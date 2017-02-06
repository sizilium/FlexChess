/**
 * @file Euler.h
 * File provides a euler class for orientation stuff
 */

#ifndef EULER_H
#define EULER_H

// includes
#include <vs/Build.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class Euler
 * Euler class contains double alpha, beta, gamma rotation in radian.
 */
class VS_EXPORT Euler
{
protected:
	base::math::DoubleVector rotation;

public:
	Euler();
	Euler(base::math::DoubleVector rotation);
	Euler(double x, double y, double z);
	~Euler();

    /**
     * @return DoubleVector with alpha, beta, gamma rotation in radian
     */
	base::math::DoubleVector getRotation() const { return rotation; }
	
    /**
     * @param rotation DoubleVector with alpha, beta, gamma rotation in radian
     *
     */
	void setRotation(const base::math::DoubleVector &rotation) 
	{ 
		this->rotation = rotation; 
	}

};

} // ph
} // core
} // vs

#endif
