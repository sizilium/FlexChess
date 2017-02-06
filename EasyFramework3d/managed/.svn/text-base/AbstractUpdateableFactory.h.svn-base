/**
 * @file AbstractUpdateableFactory.h
 * @author sizilium
 * @date 12.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_UPDATEABLE_FACTORY_H
#define ABSTRACT_UPDATEABLE_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/managed/UpdateableManager.h>

namespace vs
{

// predeclarations
namespace base {namespace util { class DefaultManaged; }}

namespace managed
{

/** @class AbstractUpdateableManager
 * 
 */
class VS_EXPORT AbstractUpdateableFactory : public base::interfaces::AbstractFactory<UpdateableManager>
{
public:
	virtual ~AbstractUpdateableFactory();
	
	virtual const std::string getName() const = 0;	// from FactoryInterface
	const std::string getNamespace() const;
	
protected:
	void addManaged(base::util::DefaultManaged *managed);
};

} // managed
} // vs

#endif  // ABSTRACT_UPDATEABLE_FACTORY_H
