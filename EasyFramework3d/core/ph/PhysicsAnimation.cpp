#include <vs/core/ph/PhysicsAnimation.h>

namespace vs
{
namespace core
{
namespace ph
{

PhysicsAnimation::PhysicsAnimation() 
: object(NULL)
{
}

PhysicsAnimation::~PhysicsAnimation()
{
}

unsigned int PhysicsAnimation::getChannelNo() const
{
	return 9;
}

void PhysicsAnimation::transformObject()
{
	object->coords[0] = currentValues[0];
	object->coords[1] = currentValues[1];
	object->coords[2] = currentValues[2];

	object->rotation[0] = currentValues[3];
	object->rotation[1] = currentValues[4];
	object->rotation[2] = currentValues[5];

	// channels 6 to 8 are omitted
}

} // ph
} // core
} // vs
