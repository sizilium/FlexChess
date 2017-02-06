/**
 * @file DefaultManagment.h
 * @author sizilium
 * @date 14.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef STDMANAGMENT_H
#define STDMANAGMENT_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/base/interfaces/Updateable.h>
#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/base/util/DefaultManagedMessage.h>
#include <vs/base/cont/List.hpp>
#include <vs/base/cont/StringList.hpp>
#include <vs/base/cont/JavaStyleContainer.hpp>

namespace vs
{
namespace base
{
namespace util
{
// predeclarations
class DefaultManaged;


/** @class DefaultManagment
 * This container administrates DefaultManaged objects. 
 */
class VS_EXPORT DefaultManagment : 	public interfaces::MsgObserver<DefaultManagedMessage>, 
									public interfaces::Updateable
{
public:
	DefaultManagment();
	virtual ~DefaultManagment();
	
	virtual void update(double deltaT);
	
	void notify(DefaultManagedMessage &message);
	
	void addManaged(DefaultManaged *managed);
	
	DefaultManaged* getManaged(const std::string &name) const;
	void removeManaged(const std::string &name);

	void getManagedNames(cont::JavaStyleContainer<std::string> *names) const;
	void getAllManaged(cont::StringList<DefaultManaged *> &stringList) const;

	void clear();

	/**
	 * @return The number of active stored managed.
	 */
	int numActiveManaged() const			{return activeList.size();}
	
	/**
	 * @return The number of inactive stored managed.
	 */
	int numInactiveManaged() const			{return inactiveList.size();}
	
	/**
	 * Print some information about the manager to std console.
	 */
	void outDebug() const;
	
protected:
	cont::List <DefaultManaged *> activeList;
	cont::List <DefaultManaged *> inactiveList;

	cont::List<DefaultManaged *>::Const_Iterator findByName(const std::string &name, const cont::List<DefaultManaged*> &inList) const;
	cont::List<DefaultManaged *>::Iterator findByName(const std::string &name, cont::List<DefaultManaged*> &inList);
};

} // util
} // base
} // vs

#endif  // STDMANAGMENT_H
