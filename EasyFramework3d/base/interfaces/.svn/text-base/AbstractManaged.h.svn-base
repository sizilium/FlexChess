/**
 * @file AbstractManaged.h
 * @author sizilium
 * @date 14.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_MANAGED_H
#define ABSTRACT_MANAGED_H

// includes
#include <vs/Build.hpp>
#include <string>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class AbstractManaged
 * All elements in the managers must implement a few basic methods like activate,
 * deactivate or getName. A "managed" is a thing wich can be active or inactive.
 * In the common case a "managed" is Updateable too. The name of a managed is important
 * for xml stuff and for the getter methods in the managers.
 * @see DefaultManaged
 */
class VS_EXPORT AbstractManaged
{
public:
	virtual ~AbstractManaged();
	
	/**
	 * Activates the managed. For example a ManagedModel (OpenGl stuff) will drawed
	 * from now on regularly. The managed now will regularly updated.
	 */
	virtual void activate() = 0;
	
	/**
	 * Deactivates the managed. For example a ManagedModel (OpenGl stuff) will hide
	 * from now on (it still exists). The managed now will not regularly updated.
	 */
	virtual void deactivate() = 0;
	
	/**
	 * Gets the name. The name is useful for resolving a pointer to the managed with
	 * the manager.
	 * @return The name. Note that unnamed managed returns an empty string.
	 */
	virtual std::string getName() const = 0;
	
	/**
	 * Check if active.
	 * @return True if the managed currently is active. 
	 */
	virtual bool isActive() const = 0;
};

} // interfaces
} // base
} // vs

#endif  // ABSTRACT_MANAGED_H
