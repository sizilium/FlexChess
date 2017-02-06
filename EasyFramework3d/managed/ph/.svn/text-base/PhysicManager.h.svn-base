/**
 * @file PhysicManager.h
 * @author sizilium
 * @date 01.06.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef PHYSIC_MANAGER_H
#define PHYSIC_MANAGER_H

// includes
#include <vs/Build.hpp>
#include <iostream>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManagment.h>
#include <vs/base/cont/StringList.hpp>

namespace vs
{
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
/**
 * Physic engine namespace. Contains all physic classes, operations and the PhysicManager.
 * @see vs::ph::PhysicManager
 */
namespace ph
{

using namespace std;

/** @class PhysicManager
 * This manager contain all physic object like Point's, Euler's, RigidBody's etc.\n
 * The moving objects (MovingPoint / MovingEuler and sub classes) are DefaultManaged elements.
 * You can get these with the getManaged() method.\n
 * The static objects (Point, OrientatedPoint and Euler) will managed separately.
 * You can get these with the specific methods, for example getPoint(), getEuler() etc.
 */
class VS_EXPORT PhysicManager : public base::interfaces::AbstractManager<PhysicManager>
{
public:
	PhysicManager();
	virtual ~PhysicManager();
	
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
	 * Gets a named list (StringList) of the containing managed elements. Useful for
	 * debugging.
	 * @code // Example
	 * PhysicManager *manager = Context::getCurrentContext()->getPhysicManager();
	 * ...
	 * ut::StringList<DefaultManaged*> list;
	 * manager->getAllManaged(list);
	 * list.coutNames();
	 * @endcode
	 */
	void getAllManaged(base::cont::StringList<base::util::DefaultManaged *> &stringList) const;
	
	/**
	 * Special getter for Point's, because points are static objects (no update needed).
	 * @param name The search string for the Point.
	 * @return A pointer to the Point or a NULL pointer if the Point does not exist. 
	 */
	core::ph::Point* getPoint(const string &name) const;
	
	/**
	 * Special getter for OrientatedPoint's, because orientated points are static objects
	 * (no update needed).
	 * @param name The search string for the OrientatedPoint.
	 * @return A pointer to the OrientatedPoint or a NULL pointer if the OrientatedPoint does not exist. 
	 */
	core::ph::OrientatedPoint* getOrientatedPoint(const string &name) const;
	
	/**
	 * Special getter for Euler's, because points are static objects (no update needed).
	 * @param name The search string for the Euler.
	 * @return A pointer to the Euler or a NULL pointer if the Euler does not exist. 
	 */
	core::ph::Euler* getEuler(const string &name) const;
	
	/**
	 * Like getAllManaged for Point's.
	 * @see getAllManaged
	 */
	void getAllPoints(base::cont::StringList<core::ph::Point *> &stringList) const;
	
	/**
	 * Like getAllManaged for OrientatedPoint's.
	 * @see getAllManaged
	 */
	void getAllOrientatedPoints(base::cont::StringList<core::ph::OrientatedPoint *> &stringList) const;
	
	/**
	 * Like getAllManaged for Euler's.
	 * @see getAllManaged
	 */
	void getAllEulers(base::cont::StringList<core::ph::Euler *> &stringList) const;
	
	/**
	 * Updates the manager and with this all containing managed elements. Note that
	 * the Context::update will update this automatically.
	 */
	virtual void update(double time);
	
	/**
	 * Returns the name of the manager as std string.
	 * @return The managers name as string.
	 */
	std::string getName() const { return "PhysicManager"; }
	
	/**
	 * This method clears all managed from the manager.
	 */
	void clear();
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;
private:
	friend class AbstractPhysicFactory;
	/**
	 * Adds a managed element to the manager. The method is private. 
	 * Only the AbstractPhysicFactory's (sub classes) can use this operation!
	 */
	void addManaged(base::interfaces::AbstractManaged *managed);
	
	/**
	 * Adds a point object to the manager. The method is private. 
	 * Only the AbstractPhysicFactory's (sub classes) can use this operation!
	 */
	void addPoint(core::ph::Point *point, const string &name);
	
	/**
	 * Adds an orientated point object to the manager. The method is private. 
	 * Only the AbstractPhysicFactory's (sub classes) can use this operation!
	 */
	void addOrientatedPoint(core::ph::OrientatedPoint *orientatedPoint, const string &name);
	
	/**
	 * Adds an euler object to the manager. The method is private. 
	 * Only the AbstractPhysicFactory's (sub classes) can use this operation!
	 */
	void addEuler(core::ph::Euler *euler, const string &name);
	
private:
	// elements with update
	base::util::DefaultManagment managment;
	
	// elements without updates
	base::cont::StringList<core::ph::Point *> points;
	base::cont::StringList<core::ph::OrientatedPoint *> orientatedPoints;
	base::cont::StringList<core::ph::Euler *> eulers;
};

} // ph
} // managed
} // vs

#endif	// PHYSIC_MANAGER_H
