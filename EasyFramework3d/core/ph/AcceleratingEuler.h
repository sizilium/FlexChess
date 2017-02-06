/**
 * @file AcceleratingEuler.h provides AcceleratingEuler class wich is a
 * MovingEunler wich accelerating torque
 */

#ifndef ACCELERATING_EULER_H
#define ACCELERATING_EULER_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/MovingEuler.h>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class AcceleratingEuler
 * only an accelerating euler. There is no position information
 */
class VS_EXPORT AcceleratingEuler : public MovingEuler
{
public:
	AcceleratingEuler();
	~AcceleratingEuler();

	/** setter for torqueA
	 * @param setTorqueA
	 */
	void setTorqueA(base::math::DoubleVector setTorqueA)	
	{
		torqueA = setTorqueA;
	
	}
	/** getter for torqueA
	 * @return
	 */
	base::math::DoubleVector getTorqueA() const	{return torqueA;}

protected:
	base::math::DoubleVector torqueA;
private:
};

} // ph
} // core
} // vs

#endif
