/**
 * @file DefaultManagedGroup.h
 * @author sizilium
 * @date 27.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACTED_MANAGED_GROUP_H
#define ABSTRACTED_MANAGED_GROUP_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractManaged.hpp>
#include <vs/base/cont/List.hpp>
#include <vector.h>
#include <string.h>

namespace vs
{
namespace base
{
namespace util
{

/** @class DefaultManagedGroup
 * This class is a abstract managed object and holds pointer to abstract managed objects 
 * (composite pattern).
 * Use this class to collect and group objects who are belonging together.
 * So you can call the methods activate, deactivate etc. for all collected object globaly.
 * You can handle several abstract managed as a one. Its like a container.
 */
class VS_EXPORT DefaultManagedGroup : public base::interfaces::AbstractManaged
{
public:
	DefaultManagedGroup();
	~DefaultManagedGroup();

	/**
	 * Activates all abstract managed object stored in this container.
	 */
	void activate();
	
	/**
	 * Deactivates all abstract managed objects stored in this container.
	 */
	void deactivate();
	
	/**
	 * Cleares the container. Remember that only the pointer to the abtract managed will be cleared.
	 */
	void clear();
	
	/**
	 * Gets the name. The name is useful for resolving a pointer to the managed with
	 * the manager.
	 * @return The name of the hole group. Note that unnamed managed returns an empty string.
	 */
	std::string getName() const;

	/**
	 * Gets the names of all abstract managed members in this group.
	 */
	std::vector<std::string> getNames() const;
	
	/**
	 * Check if the group (and with it all abstract managed members) active.
	 * @return True if the group currently is active. 
	 */
	bool isActive() const;
	
private:
	base::cont::List<base::interfaces::AbstractManaged *> group;
};

} // util
} // base
} // vs

#endif  // ABSTRACTED_MANAGED_GROUP_H
