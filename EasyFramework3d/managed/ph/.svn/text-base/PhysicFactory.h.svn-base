/**
 * @file PhysicFactory.h
 * @author sizilium
 * @date 05.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef PHYSICFACTORY_H
#define PHYSICFACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/managed/ph/AbstractPhysicFactory.h>
#include <vs/base/xml/AbstractXmlFactory.h>

namespace vs
{
// predeclarations
namespace core
{
namespace ph
{
class Point;
class Euler;
class OrientatedPoint;
class MovingPoint;
class AcceleratingPoint;
class MovingEuler;
class AcceleratingEuler;
class MovingOrientatedPoint;
class PointBody;
class RigidBody;
}
}

namespace managed
{
namespace ph
{


/** @class PhysicFactory
 * 
 */
class VS_EXPORT PhysicFactory : public AbstractPhysicFactory, public base::xml::AbstractXmlFactory 
{
public:
	PhysicFactory();
	virtual ~PhysicFactory();
	
	const std::string getName() const;

	// no DefaultManaged Elements
	core::ph::Point* createPoint (const std::string &name = "");
	core::ph::Euler* createEuler (const std::string &name = "");
	core::ph::OrientatedPoint *createOrientatedPoint (const std::string &name = "");
	
	// DefaultManaged Elements
	core::ph::MovingPoint *createMovingPoint (const std::string &name = "");
	core::ph::AcceleratingPoint* createAcceleratingPoint (const std::string &name = "");
	core::ph::MovingEuler* createMovingEuler (const std::string &name = "");
	core::ph::AcceleratingEuler *createAcceleratingEuler (const std::string &name = "");
	core::ph::MovingOrientatedPoint* createMovingOrientatedPoint (const std::string &name = "");
	core::ph::PointBody* createPointBody (const std::string &name = "");
	core::ph::RigidBody* createRigidBody (const std::string &name = "");
	
private:

};

} // ph
} // managed
} // vs

#endif  // PHYSICFACTORY_H
