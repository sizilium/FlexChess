/**
 * @file AbstractConstraintFactory.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACTCONSTRAINT_FACTORY_H
#define ABSTRACTCONSTRAINT_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/constr/ConstraintManager.h>

namespace vs
{
namespace base { namespace util {class DefaultManaged; } }

namespace constr
{

/** @class AbstractConstraintFactory
 * 
 */
class VS_EXPORT AbstractConstraintFactory : public base::interfaces::AbstractFactory<ConstraintManager>
{
public:
	virtual ~AbstractConstraintFactory();
	
	virtual const std::string getName() const = 0;
	const std::string getNamespace() const;
		
protected:
	void addManaged(base::util::DefaultManaged *managed);
};

} // constr
} // vs

#endif  // ABSTRACTCONSTRAINT_FACTORY_H
