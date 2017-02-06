/**
 * @file MovingOrientatedPoint.h 
 * Provides a class which simply represent a MovingPoint with a moving rotation.
 */

#ifndef MOVING_ORIENTATED_POINT_H
#define MOVING_ORIENTATED_POINT_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/MovingPoint.h>
#include <vs/core/ph/MovingEuler.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class MovingOrientatedPoint
 * A simply class for point with rotation
 */
class VS_EXPORT MovingOrientatedPoint : public MovingPoint, public MovingEuler
{
friend class PhysicsAnimation;

public:
    MovingOrientatedPoint();
    ~MovingOrientatedPoint();

	virtual void update(double deltaT);
    
private:

};

} // ph
} // core
} // vs

#endif
