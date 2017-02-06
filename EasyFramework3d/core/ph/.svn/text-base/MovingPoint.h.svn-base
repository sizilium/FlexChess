/**
 * @file
 * MovingPoint class is a Point with a Vector for velocity.
 *
*/

#ifndef MOVINGPOINT_H
#define MOVINGPOINT_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/Point.h>
#include <vs/base/util/DefaultManaged.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class MovingPoint 
 * Is a Point and contains additionally a DoubleVector v
 * for velocity. This means the point has a direction too.
 */
class VS_EXPORT MovingPoint : public Point, virtual public base::util::DefaultManaged
{
public:
	MovingPoint();
	virtual ~MovingPoint();
	
	base::math::DoubleVector getV() const { return v; }
	void setV(const base::math::DoubleVector velocity) { this->v = velocity; }

	/**
	 * applies a acceleration 'a' to the Point in a time 'deltaT'
	 */
	virtual void applyAccel(const base::math::DoubleVector a, const double deltaT);
	
	/**
	 * moves the point in a time 'deltaT' (depends on velocity vector)
	 */
	virtual void update(double deltaT);

protected:
	base::math::DoubleVector v;
};

} // ph
} // core
} // vs

#endif // MOVINGPOINT_H
