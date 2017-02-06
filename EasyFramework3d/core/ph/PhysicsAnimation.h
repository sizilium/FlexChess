#ifndef PHYSICSANIMATION_H_
#define PHYSICSANIMATION_H_

// includes
#include <vs/Build.hpp>
#include <vs/core/gl/ObjectAnimation.h>
#include <vs/core/ph/MovingOrientatedPoint.h>

namespace vs
{
namespace core
{
namespace ph
{

class VS_EXPORT PhysicsAnimation : public gl::ObjectAnimation
{
public:
	PhysicsAnimation();
	virtual ~PhysicsAnimation();

	void setObject(MovingOrientatedPoint &object)
	{
		this->object = &object;
		object.v[0] = 0;
		object.v[1] = 0;
		object.v[2] = 0;
		object.torque[0] = 0;
		object.torque[1] = 0;
		object.torque[2] = 0;
	}

	unsigned int getChannelNo() const;
protected:
	// template method used in update()
	// the object doesn't need to be updated
	void transformObject();

	MovingOrientatedPoint *object;
};

} // ph
} // core
} // vs

#endif /*PHYSICSANIMATION_H_*/
