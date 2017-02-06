#include <vs/constr/RotationConstraint.h>
#include <vs/core/ph/Euler.h>

namespace vs
{
namespace constr
{
using namespace base::interfaces;

RotationConstraint::RotationConstraint(AbstractConstraint *constraint, 
                                       const Init &init)
:ConstraintDecorator(constraint)
{
	priority = High;	// default
	
	this->e1 = init.e1;
	this->e2 = init.e2;
}

RotationConstraint::~RotationConstraint()
{
}

void RotationConstraint::update(double)
{
	*e1 = *e2;
}

} // constr
} // vs
