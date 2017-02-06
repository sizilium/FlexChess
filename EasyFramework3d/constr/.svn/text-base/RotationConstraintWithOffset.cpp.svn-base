#include <vs/constr/RotationConstraintWithOffset.h>
#include <vs/core/ph/Euler.h>

namespace vs
{
namespace constr
{
using namespace base::interfaces;

RotationConstraintWithOffset::RotationConstraintWithOffset
								(AbstractConstraint *constraint, 
								 const Init &init)
:ConstraintDecorator(constraint)
{
	priority = High;	// default
	
	this->e1 = init.e1;
	this->e2 = init.e2;
	
	offset = e1->getRotation() - e2->getRotation(); 
}

RotationConstraintWithOffset::~RotationConstraintWithOffset()
{
}

void RotationConstraintWithOffset::update(double)
{
	e1->setRotation(e2->getRotation() + offset);
}

} // constr
} // vs
