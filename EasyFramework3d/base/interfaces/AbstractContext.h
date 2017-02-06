/**
 * @file AbstractContext.h
 * @author sizilium
 * @date 18.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_CONTEXT_H
#define ABSTRACT_CONTEXT_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/Updateable.h>
#include <vs/base/interfaces/ManagerInterface.hpp>
#include <string>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class AbstractContext
 * 
 */
class VS_EXPORT AbstractContext : public base::interfaces::Updateable
{
public:
	virtual ~AbstractContext();
	
	virtual void performAction(std::string action) = 0;

protected:
	// here Context have access to these Managers private methods
	template<class T> 
	void setCurrentManager(ManagerInterface *manager)
	{
		T::setCurrentManager(manager);
	}
	template<class T> 
	void setCurrentContext(AbstractContext *context)
	{
		T::setCurrentContext(context);
	}
};

} // interfaces
} // base
} // vs

#endif  // ABSTRACT_CONTEXT_H
