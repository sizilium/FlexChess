/**
 * @file UpdateableManager.h
 * @author sizilium
 * @date 04.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef UPDATEABLE_MANAGER_H
#define UPDATEABLE_MANAGER_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManagment.h>

namespace vs
{
// predeclarations
namespace base {namespace interfaces {class AbstractManaged; }}

namespace managed
{
// predeclarations
class AbstractUpdateableFactory;


/** @class UpdateableManager
 * The UpdateableManager serves as an entry point for user defined DefaultManaged elements.
 * You can implement own DefaultManaged elements and put it to this manager (for regularly
 * updates). Of course you can programming your own managers and put it to this manager
 * too.\n
 * The second way to extending the EasyFramework with user defined managed elements is
 * the plugin mechanism in the "pg" namespace.
 * @see pg::PluginManager
 */
class VS_EXPORT UpdateableManager : public base::interfaces::AbstractManager<UpdateableManager>
{
public:
	UpdateableManager();
	virtual ~UpdateableManager();
	
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
	void getManagedNames(vs::base::cont::JavaStyleContainer<std::string> *names) const;

	/**
	 * Getter for managed elements.
	 * @name The search string of the managed.
	 * @return A pointer to the managed or a NULL pointer if the managed name not exist.
	 */
	vs::base::interfaces::AbstractManaged* getManaged(const std::string &name) const;
	
	/**
	 * Removes an element from the manager finally (no deactivate).
	 * @name The search string of the managed. If the managed does not exist nothing
	 * will happen.
	 */
	void removeManaged(const std::string &name);
	
	/**
	 * Updates the manager and with this all containing managed elements. Note that
	 * the Context::update will update this automatically.
	 */
	void update(double time);

	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "UpdateableManager"; }
	
	/**
	 * This method clears all managed from the manager.
	 */
	virtual void clear();
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;

private:
	friend class AbstractUpdateableFactory;
	/**
	 * Adds a managed object to the manager. The method is private. 
	 * Only the AbstractUpdateableFactory's (sub classes) can use this operation!
	 */
	void addManaged(vs::base::interfaces::AbstractManaged *managed);
	
private:
	vs::base::util::DefaultManagment managment;

};

} // managed
} // vs

#endif	// UPDATE_MANAGER_H
