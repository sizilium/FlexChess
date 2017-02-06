/**
 * @file FactoryInterface.h
 * @author sizilium
 * @date 14.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FACTORY_INTERFACE_H
#define FACTORY_INTERFACE_H

// includes
#include <vs/Build.hpp>
#include <iostream>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class FactoryInterface
 * All factories in EasyFramework must implement a few common methods like setContext,
 * getName or getNamespace. This is important for xml stuff (and for more consistence).
 */
class VS_EXPORT FactoryInterface
{
public:
	virtual ~FactoryInterface() = 0;
	/**
	 * The factory must have a name. The xml mechanism use this name for sub tags...
	 */
	virtual const std::string getName() const = 0;
	
	/**
	 * The factory must have a namespace (vs, vs::ph, vs::gl, vs::constr...). The xml
	 * mechanism use this name for sub tags...
	 */
	virtual const std::string getNamespace() const = 0;
};

} // interfaces
} // base
} // vs

#endif  // ABSTRACT_FACTORY_INTERFACE_H
