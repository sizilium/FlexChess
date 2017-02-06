#include <vs/constr/ScalationConstraint.h>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace constr
{
using namespace base::interfaces;

ScalationConstraint::ScalationConstraint
						(AbstractConstraint *constraint, 
						 const Init &init)
:ConstraintDecorator(constraint)
{
	priority = High;	// default
	
	this->scaleThis = init.scaleThis;
	this->scaleFrom = init.scaleFrom;
}

ScalationConstraint::~ScalationConstraint()
{
}

void ScalationConstraint::update(double)
{
	*scaleThis = *scaleFrom;
}

} // constr
} // vs
