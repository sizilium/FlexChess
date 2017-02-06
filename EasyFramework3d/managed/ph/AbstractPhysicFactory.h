/**
 * @file AbstractPhysicFactory.h
 * @author sizilium
 * @date 05.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_PHYSIC_FACTORY_H
#define ABSTRACT_PHYSIC_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/managed/ph/PhysicManager.h>

namespace vs
{
// predeclarations
namespace base {namespace util {class DefaultManaged; }}
namespace core
{
namespace ph
{
class Point;
class OrientatedPoint;
class Euler;
}
}

namespace managed
{
namespace ph
{

/** @class AbstractPhysicFactory
 * 
 */
class VS_EXPORT AbstractPhysicFactory : public base::interfaces::AbstractFactory<PhysicManager>
{
public:
	~AbstractPhysicFactory();
	
	virtual const std::string getName() const = 0;	// from FactoryInterface
	const std::string getNamespace() const;
	
protected:
	void addManaged(base::util::DefaultManaged *managed);
	void addPoint(core::ph::Point *point, const std::string &name);
	void addOrientatedPoint(core::ph::OrientatedPoint *orientatedPoint, const std::string &name);
	void addEuler(core::ph::Euler *euler, const std::string &name);
};


} // ph
} // managed
} // vs

#endif  // ABSTRACT_PHYSIC_FACTORY_H
