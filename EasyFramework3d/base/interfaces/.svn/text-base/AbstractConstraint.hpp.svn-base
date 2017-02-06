/**
 * @file AbstractConstraint.hpp
 * @author sizilium
 * @date 25.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef ABSTRACTCONSTRAINT_H
#define ABSTRACTCONSTRAINT_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractManager.hpp>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/interfaces/Updateable.h>
#include <string>

namespace vs
{
namespace base
{
namespace interfaces
{
using namespace std;

/** @class AbstractConstraint
 * This class represents the base type of the decorator design pattern (this is an interfaces).\n
 * Constraints are a set of regulations and will be updated regularly by a ConstraintManager.
 * @see Constraint, ConstraintProperty
 */
class VS_EXPORT AbstractConstraint : public base::util::DefaultManaged
{
public:
	//AbstractConstraint();
	//virtual ~AbstractConstraint()		{}

	/**
	 * Possible prioritys for constraints. Used by ConstraintManager to
	 * schedule all constraints. The enum values simply represents a priority int number.
	 * A higher number means a higher priority.\n
	 */
	enum Priority
	{
		Realtime 	= 0,	/**< the constraint will updated often as possible (gl Render stuff)*/
		VeryHigh 	= 10,	/**< like Realtime but with possible exceptions in special cases (gl Render parent stuff)*/
		High		= 20,	/**< update will called nearly every second time*/
		Medium		= 30,	/**<	*/
		Low			= 40,	/**<	*/
		VeryLow		= 50, 	/**< updates the constraint only if the cpu is in idle (logging, statistics stuff)*/
	};

	void setPriority(int priority)			{this->priority = priority;}
	virtual int getPriority() const	= 0;
	
	virtual bool toDelete() const = 0;
	
protected:
	int priority;
};

} // interfaces
} // base
} // vs

#endif	// ABSTRACTCONSTRAINT_H
