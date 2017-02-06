/**
 * @file AbstractManager.hpp
 * @author sizilium
 * @date 18.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_MANAGER_H
#define ABSTRACT_MANAGER_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/ManagerInterface.hpp>
#include <vs/base/interfaces/AbstractContext.h>
#include <vs/base/util/ReferenceCounting.h>
#include <vs/base/util/IOStream.h>
#include <string>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class AbstractManager
 * This class encapsulates a current manager pointer. It already a pure abstract class
 * because some methods from ManagerInterface are not implemented.
 * All Managers in the EasyFramework should inherit this class.
 */
template<class T>
class VS_EXPORT AbstractManager : public util::RcObject, public ManagerInterface
{
public:
	virtual ~AbstractManager()
	{
		// perform context action
		// currentContext->performAction("refreshManagers");
	}
	
	static bool isCurrentManager()
	{
		if (currentManager)
			return true;
		else
			return false;
	}
	
	static T* getCurrentManager()
	{
		if (currentManager == NULL)
		{
			// if there is no current manager, create one!
			currentManager = new T;
			
			// perform context action
			if (currentContext)
				currentContext->performAction("refreshManagers");
		}

		// dynamic_cast mit try catch?
		return (T*)currentManager;
	}
	
private:
	// only Context allowed to call this (about AbstractContext)
	static void setCurrentManager(ManagerInterface *manager)
	{
		currentManager = manager;
	}

	// only Context allowed to call this
	static void setCurrentContext(AbstractContext *context)
	{
		currentContext = context;
	}
	
	// about AbstractContext the Context class has access to the private
	// methods.
	friend class AbstractContext;
	
	static ManagerInterface *currentManager;
	static AbstractContext *currentContext;
};

template<class T>
ManagerInterface* AbstractManager<T>::currentManager = NULL;

template<class T>
AbstractContext* AbstractManager<T>::currentContext = NULL;

} // interfaces
} // base
} // vs

#endif  // ABSTRACT_MANAGER_H
