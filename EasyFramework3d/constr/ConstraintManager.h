/**
 * @file ConstraintManager.h
 * @author sizilium
 * @date 25.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef CONSTRAINTMANAGER_H
#define CONSTRAINTMANAGER_H

// include
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManagment.h>
#include <vs/base/cont/StringList.hpp>
#include <vs/Context.h>
#include <iostream>

namespace vs
{
// predeclarations
namespace base 
{
namespace interfaces 
{
class AbstractManaged;
class AbstractConstraint;
}
}

/**
 * Constraint namespace contains all EasyFramework constraint stuff.\n
 * Constraints a a set of conditions wich will update regularly.
 * @see vs::constr::ConstraintManager
 */
namespace constr
{


/** @class ConstraintManager
 * 
 */
class VS_EXPORT ConstraintManager : public base::interfaces::AbstractManager<ConstraintManager>
{
public:
	ConstraintManager();
	virtual ~ConstraintManager();
	
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
	base::interfaces::AbstractManaged* getManaged(const std::string &name) const;

	void getAllConstraints(base::cont::StringList<base::interfaces::AbstractConstraint *> &stringList) const;
	
	/**
	 * Removes an element from the manager finally (no deactivate).
	 * @name The search string of the managed. If the managed does not exist nothing
	 * will happen.
	 */
	void removeManaged(const std::string &name);
	
	void schedule();

	/**
	 * Updates the manager and with this all containing managed elements. Note that
	 * the Context::update will update this automatically.
	 */
	virtual void update(double deltaT);
	
	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "ConstraintManager"; }
	
	/**
	 * @return The number of active stored managed.
	 */
	int numActiveManaged() const			{return managment.numActiveManaged();}
	
	/**
	 * @return The number of inactive stored managed.
	 */
	int numInactiveManaged() const			{return managment.numInactiveManaged();}
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;
	
	/**
	 * This method clears all managed from the manager.
	 */
	void clear();
	
private:
	friend class AbstractConstraintFactory;
	/**
	 * Adds a managed object to the manager. The method is private. 
	 * Only the AbstractConstraintFactory's (sub classes) can use this operation!
	 */
	void addManaged(base::interfaces::AbstractManaged *managed);
	
private:
	base::util::DefaultManagment managment;
};

} // constr
} // vs

#endif	// CONSTRAINTMANAGER_H
