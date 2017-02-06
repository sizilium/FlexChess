/**
 * @file MovingEuler.h
 * MovingEuler class is a Euler with a Vector for velocity.
 *
*/

#ifndef MOVINGEULER_H
#define MOVINGEULER_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/Euler.h>
#include <vs/base/util/DefaultManaged.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class MovingEuler
 * MovingEuler class is a Euler and contains additionally a DoubleVector torque
 * for angular momentum. In other words: a point with rotation
 */
class VS_EXPORT MovingEuler : public Euler, virtual public base::util::DefaultManaged
{
	public:
		MovingEuler();
		virtual ~MovingEuler();

		base::math::DoubleVector getTorque() const { return torque; }
		void setTorque(const base::math::DoubleVector setTorque) { this->torque = setTorque; }

		virtual void update(double deltaT);

	protected:
		base::math::DoubleVector torque;
};

} // ph
} // core
} // vs

#endif
