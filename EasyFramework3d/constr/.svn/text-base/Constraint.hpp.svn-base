/**
 * @file Constraint.hpp
 * @author sizilium
 * @date 27.05.2007
 * @brief visit www.vision-synthesis.de
 */

#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractConstraint.hpp>

namespace vs
{
namespace constr
{

/** @class Constraint
 * 
 */
class VS_EXPORT Constraint : public base::interfaces::AbstractConstraint
{
public:
	Constraint(const std::string name)
	{
		this->priority = Realtime;
		setName(name);
	}
	virtual ~Constraint()
	{}

	virtual void update(double deltaT)
	{}
	
	int getPriority() const
	{
		return this->priority;
	}
	
	bool toDelete() const
	{
		return false;
	}

private:
};

} // constr
} // vs

#endif	// CONSTRAINT_HPP
