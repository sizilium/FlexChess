/**
 * @file DefaultManagedGroup.h
 * @author sizilium
 * @date 27.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef DEFAULT_MANAGED_GROUP_H
#define DEFAULT_MANAGED_GROUP_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/base/cont/List.hpp>
#include <vector>
#include <string>

namespace vs
{
namespace base
{
namespace util
{

/** @class DefaultManagedGroup
 * This class is a default managed object and holds pointer to default managed objects 
 * (composite pattern).
 * Use this class to collect and group objects who are belonging together.
 * So you can call the methods activate, deactivate etc. for all collected object globaly.
 * You can handle several default managed as a one. Its like a container.
 * If you removes a default managed from a container, a message will send to this group and will
 * removed from this group too. So it's secure that there come no pointer errors!
 */
class VS_EXPORT DefaultManagedGroup : 	public DefaultManaged,
										public interfaces::MsgObserver<DefaultManagedMessage>
{
public:
	DefaultManagedGroup();
	/**
	 * The destructor calls the clears only this object with his links, not the default managed
	 * objects itself.
	 */
	virtual ~DefaultManagedGroup();

	/**
	 * Make sure that a removed managed (from the manager) will remove from this group too.
	 * Each managed destructor emits a message by observer pattern.
	 */
	void notify(DefaultManagedMessage &message);
	
	/**
	 * Cleares the container. Remember that only the pointer to the abtract managed will be cleared.
	 * The managed element will be already stored in the manager.
	 * @see removeAndClear
	 */
	void clear();
	
	/**
	 * Returns the number of stored default managed objects.
	 */
	int size() const;
	
	/**
	 * Removes all default managed stored in this container physically from the manager. Then the
	 * links will be removed.
	 */
	void removeAndClear();
	
	/**
	 * Adds a link (pointer) to a default managed object to this group.
	 * The method also checks if the link already exists. In this case nothing happens. There are
	 * only one link per object in the group!
	 */
	void addManaged(DefaultManaged *op2);
	
	/**
	 * Removes a link (pointer) to a default managed object from this group.
	 */
	void removeManaged(DefaultManaged *op2);
	
	/**
	 * Another way to add managed to this group.
	 * @return Returns the op2 pointer (redirected), not the group itself!
	 * @see addManaged
	 */
	DefaultManaged* operator=(DefaultManaged *op2);
	
	/**
	 * Updates all default managed objects stored in this group.
	 */
	void update(double deltaT);
	
	/**
	 * Activates all default managed objects stored in this group.
	 * Note: If you activate a single default managed wich is member of this group and the group 
	 * was deactivated, only the one default managed will be activated, it has no effect to the 
	 * hole group.
	 */
	void activate();
	
	/**
	 * Deactivates all default managed objects stored in this group.
	 * Note: If you deactivate a single default managed wich is member of this group and the group 
	 * was activated, only the one default managed will be deactivated, it has no effect to the 
	 * hole group.
	 */
	void deactivate();
	
	// The getName() and setName() methods inherited from DefaultManaged referes to this group.
	
	/**
	 * Gets the names of all default managed members in this group.
	 * @return The names will returned in chronological order.
	 */
	std::vector<std::string> getNames() const;
	
private:
	cont::List<DefaultManaged *> group;
	
	cont::List<DefaultManaged *>::Iterator findByName(const std::string &name, cont::List<DefaultManaged*> &inList);
};

} // util
} // base
} // vs

#endif  // DEFAULT_MANAGED_GROUP_H
