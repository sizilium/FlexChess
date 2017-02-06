/** @file SoundListener.h
 * This file contains the SoundListener class wich integrates the openAL
 * sound listener in the vs framework. This means the SoundListener is a
 * MovingPoint and has an orientation.
 * Also this file provides several function wich configure the openAL distance
 * settings.
 */
// test
#ifndef SOUND_LISTENER
#define SOUND_LISTENER

// includes
#include <vs/Build.hpp>
#include <AL/al.h>
#include <vs/core/ph/MovingOrientatedPoint.h>
#include <vs/core/ph/Point.h>
#include <vs/managed/al/ALException.h>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;
using namespace vs::core::ph;

/**
 * @class SoundListener
 * implements the open al listener (wrapper in vs framework)
 * position, rotation and velocity are often the same as camera position, rotation
 * and velocity for example.
 */
class VS_EXPORT SoundListener : public MovingOrientatedPoint
{
public:

	/**
	 * Constructor without parameters will set the default position to {0, 0, 0},
	 * velocity to {0, 0, 0} and orientation to { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 }
	 * (first 3 elements are "at", second 3 are "up")
	 */
	SoundListener();
	
	/**
	 * @param mop MovingPoint for 3d listener position and velocity
	 */
	SoundListener(MovingOrientatedPoint mop);

	~SoundListener();

	/**
	 * SoundSource is a ph::MovingPoint. So update calls ph::MovingPoint::update and
	 * then updates the al listener position and velocity. For correct sound
	 * call this update method regularly
	 */
	virtual void update(double deltaT);

    // wird duch constraints ersetzt? constraints sind friend...
    void set(Point point, Point lookAt);

};

/**
 * todo
 */
VS_EXPORT void setDistanceModelLinear();
/**
 * todo
 */
VS_EXPORT void setDistanceModelLinearClamped();
/**
 * todo
 */
VS_EXPORT void setDistanceModelExponent();
/**
 * todo
 */
VS_EXPORT void setDistanceModelExponentClamped();
/**
 * todo
 */
VS_EXPORT void setDistanceModelNone();

} // al
} // managed
} // vs

#endif
