/**
 * @file ConstraintDecorator.hpp
 * @author sizilium
 * @date 27.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef CONSTRAINT_DECORATOR_HPP
#define CONSTRAINT_DECORATOR_HPP

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractConstraint.hpp>

namespace vs
{
namespace constr
{

/** @class ConstraintDecorator
 * 
 */
class VS_EXPORT ConstraintDecorator : public base::interfaces::AbstractConstraint
{
public:
	ConstraintDecorator(base::interfaces::AbstractConstraint *constraint)	
	{
		this->constraint = constraint; 
		this->priority = Medium;
		this->deleteMe = false;
	}
	
	virtual ~ConstraintDecorator()		
	{ 
		delete constraint; 
		constraint = NULL; 
	}

	int getPriority() const
	{
		return (this->priority + constraint->getPriority()) / 2;
	}
	
	bool toDelete() const	
	{
		if (deleteMe)
			return true;
		else if (constraint)
			return constraint->toDelete();
		else
			return false;
	}

protected:
	void deleteThis()			{this->deleteMe = true;}
	
	base::interfaces::AbstractConstraint *constraint;
	bool deleteMe;
};

} // constr
} // vs

#endif	// CONSTRAINT_DECORATOR_HPP
