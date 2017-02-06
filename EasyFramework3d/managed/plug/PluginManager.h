/**
 * @file PluginManager.h
 * @author sizilium
 * @date 04.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManagment.h>

namespace vs
{
namespace managed
{
namespace plug
{
using namespace std;

/** @class PluginManager
 * 
 */
class VS_EXPORT PluginManager : public base::interfaces::AbstractManager<PluginManager>
{
public:
	PluginManager();
	~PluginManager();

	/**
	 * Gets all names actually stored in the manager. With the names you can get
	 * access to the managed using getManaged(name) method. Note that these methods
	 * are not optimal for performance. Use handler (pointer) to the managed instead.
	 * @param names Pass any vs container.
	 * @code // Example
	 * ...
	 * List<string> myList;
	 * myManager->getManagedNames(&myList);
	 * ...
	 * @endcode
	 */
	void getManagedNames(base::cont::JavaStyleContainer<std::string> *names) const;
	
	/**
	 * Getter for managed elements.
	 * @name The search string of the managed.
	 * @return A pointer to the managed or a NULL pointer if the managed name not exist.
	 */
	base::interfaces::AbstractManaged* getManaged(const string &name) const;
	
	/**
	 * Removes an element from the manager finally (no deactivate).
	 * @name The search string of the managed. If the managed does not exist nothing
	 * will happen.
	 */
	void removeManaged(const string &name);
	
	/**
	 * Updates the manager and with this all containing managed elements. Note that
	 * the Context::update will update this automatically.
	 */
	void update(double time);
				
	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "PluginManager"; }
	
	/**
	 * This method clears all managed from the manager.
	 */
	void clear();
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;
private:
	//friend class base::interfaces::PluginFactoryInterface;
	/**
	 * Adds a managed element to the manager. The method is private. 
	 */
	void addManaged(base::interfaces::AbstractManaged *managed);

private:
	base::util::DefaultManagment managment;
};

} // plug
} // managed
} // vs

#endif	// PLUGIN_MANAGER_H
