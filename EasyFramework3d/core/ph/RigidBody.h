/**
 * @file RigidBody.h provides RigidBody class which represents a common physical
 * body with translation, rotation, acceleration etc.
 */

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

// includes
#include <vs/Build.hpp>
#include <vs/core/ph/PointBody.h>
#include <vs/core/ph/AcceleratingEuler.h>

namespace vs
{
namespace core
{
namespace ph
{

/**
 * @class RigidBody
 * can be used for player and other common stuff
 */
class VS_EXPORT RigidBody : public PointBody, public AcceleratingEuler
{
public:
	RigidBody();
	~RigidBody();
	
	virtual void update(double deltaT);
	
private:

};

} // ph
} // core
} // vs

#endif
