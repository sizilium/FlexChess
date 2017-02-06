/**
 * @file ManagerInterface.hpp
 * @author sizilium
 * @date 05.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MANAGER_INTERFACE_H
#define MANAGER_INTERFACE_H

// include
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/interfaces/Updateable.h>
#include <vs/base/cont/JavaStyleContainer.hpp>
#include <vs/base/cont/SmartIterator.hpp>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class ManagerInterface
 * An interface for all managers in EasyFramework. It is useful for the Context class which
 * contains a list of managers, that is ManagerInterface's and it provides consistency.\n
 * This manager base class supports some standard implementations too, see below.
 */
class VS_EXPORT ManagerInterface : public Updateable
{
public:
	virtual ~ManagerInterface() {}

	/**
	 * Gets all names currently stored in the manager. With the names you can get
	 * access to the managed objects using the getManaged(name) method.
	 * Note that these methods are slow (O(n)). They are meant to be used only once
	 * to get the pointers to the managed objects you're interested in. If you want
	 * to access the corresponding objects more than once, you should keep these pointers. 
	 * @param names The managed object names are stored in this container.
	 * You can pass any vs container.
	 * @code // Example
	 * ...
	 * List<std::string> myList;
	 * myManager->getManagedNames(&myList);
	 * ...
	 * @endcode
	 */
	virtual void getManagedNames(cont::JavaStyleContainer<std::string> *names) const = 0;
	
	/**
	 * Gets all names of the objects with a specific type currently stored in the manager.
	 * With the names you can get access to the managed using getManaged(name) method.
	 * Note that these methods are slow (O(n)). They are meant to be used only once
	 * to get the pointers to the managed objects you're interested in. If you want
	 * to access the corresponding objects more than once, you should keep these pointers. 
	 * @code // Example
	 * ...
	 * Tree<std::string> myTree;
	 * myManager->getManagedNames<Light*>(&myTree);  // gets all lights from manager
	 * myManager->getManagedNames<Camera*>(&myTree); // gets all cams from manager
	 * ...
	 * @endcode
	 */
	template<class T>
	void getManagedNamesCast(cont::JavaStyleContainer<std::string> *names) const
	{
		getManagedNames(names);
		
		cont::SmartIterator<std::string> it(names);
		
		while (it.hasNext())
		{
			// sorting out all other types
			if (getManagedCast<T>(it.current()) == NULL)
			{
				// if found, remove and start at the beginning
				names->remove(it.current());
				it = names->iterator();
				continue;
			}
			it.next();
		}
	}

	/**
	 * Returns the managed object which has the specified name. 
	 * Note that this method is slow (O(n)). It is meant to be used only once
	 * to get the pointer to the managed object you're interested in. If you want
	 * to access the corresponding object more than once, you should keep the pointer. 
	 * @param name The name of the managed object you're interested in
	 * @return The pointer to the managed object or a NULL pointer if
	 * the managed object wasn't found.
	 * @warning Check for NULL before you use the returned pointer!
	 */
	virtual base::interfaces::AbstractManaged* getManaged(const std::string &name) const = 0;
	
	/**
	 * Comfort method which is based on getManaged.
	 * This method will cast the managed object
	 * to a custom type - specified by the template argument - and returns it.
	 * Note that this method is slow (O(n)). It is meant to be used only once
	 * to get the pointer to the managed object you're interested in. If you want
	 * to access the corresponding object more than once, you should keep the pointer. 
	 * @param name Pass the search std::string of the managed.
	 * @return The casted pointer to the managed object or a NULL pointer if the 
	 * managed object wasn't found. 
	 * @warning Check for NULL before you use the returned pointer!
	 */
	template<class T>
	T getManagedCast(const std::string &name) const
	{
		T retVal;
		
		AbstractManaged *abstractManaged = getManaged(name);
		if (abstractManaged == NULL)
			return NULL;
		
		if ( (retVal = dynamic_cast<T> (abstractManaged)) )
			return retVal;
		else
			return NULL;
	}

	/**
	 * Removes a managed object.
	 * @param name Name of the managed object to remove. If the managed does
	 * not exist nothing happens.
	 */
	virtual void removeManaged(const std::string &name) = 0;

	/**
	 * Gets the Name of the manager
	 * @return The managers name as std string.
	 */
	virtual std::string getName() const = 0;
	
	/**
	 * This method clears all managed from the manager.
	 */
	virtual void clear() = 0;
	
	/**
	 * Prints some information about the manager to stdout.
	 */
	virtual void outDebug() const = 0;
	
private:
	
	/**
	 * Adds a new managed object. Consider the design of
	 * EasyFramework: only the factories should be able to add managed elements to the
	 * managers. That's why this method is private. The abstract factories will be friend to
	 * the managers and thus the corresponding subfactories too.
	 */
	virtual void addManaged(AbstractManaged *managed) = 0;
};

} // interfaces
} // base
} // vs

#endif	// MANAGER_INTERFACE_H
