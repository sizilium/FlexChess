/**
 * @file PluginFactoryInterface.hpp
 * @author sizilium
 * @date 12.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef PLUGIN_FACTORY_INTERFACE_H
#define PLUGIN_FACTORY_INTERFACE_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/interfaces/AbstractManaged.h>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class AbstractUpdateableManager
 * 
 */
class VS_EXPORT PluginFactoryInterface
{
public:
	virtual const std::string getName() const = 0;	// from FactoryInterface
	virtual const std::string getNamespace() const;
	
	virtual AbstractManaged* create(const std::string &name) const = 0;
};

} // interfaces
} // base
} // vs

#endif  // PLUGIN_FACTORY_INTERFACE_H
