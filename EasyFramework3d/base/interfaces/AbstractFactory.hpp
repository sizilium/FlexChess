/**
 * @file AbstractFactory.hpp
 * @author sizilium
 * @date 18.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_FACTORY_H
#define ABSTRACT_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/FactoryInterface.h>

namespace vs
{
namespace base
{
namespace interfaces
{

/** @class AbstractFactory
 * 
 */
template<class T>
class VS_EXPORT AbstractFactory : public FactoryInterface
{
public:
	AbstractFactory()
	{
		this->manager = T::getCurrentManager();
	}

	virtual ~AbstractFactory()
	{}

	void setManager (T* manager)
	{
		this->manager = manager;
	}

	void setCurrentManager()
	{
		this->manager = T::getCurrentManager();
	}
	
	T* getCurrentManager() const
	{
		return manager;
	}

protected:
	// subclasses have access to the manager
	T *manager;
};

} // interfaces
} // base
} // vs

#endif  // ABSTRACT_FACTORY_H
