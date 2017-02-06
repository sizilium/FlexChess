/**
 * @file ConstraintProperty.hpp
 * @author sizilium
 * @date 27.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef CONSTRAINT_PROPERTY_HPP
#define CONSTRAINT_PROPERTY_HPP

// include
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractConstraint.hpp>

namespace vs
{
namespace constr
{

/** @class ConstraintProperty
 * 
 */
class VS_EXPORT ConstraintProperty : public base::interfaces::AbstractConstraint
{
public:
	ConstraintProperty(base::inerface::AbstractConstraint *constraint)	
	{
		this->constraint = constraint;
	}
	virtual ~ConstraintProperty()	{}

	virtual string getName() const		{return constraint->getName();}
	virtual void initPriority() = 0;

protected:
	base::interfaces::AbstractConstraint *constraint;
};

} // vs
} // constr

#endif	// CONSTRAINT_PROPERTY_HPP
