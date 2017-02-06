#include <vs/constr/ScalationConstraintWithOffset.h>

namespace vs
{
namespace constr
{
using namespace base::interfaces;

ScalationConstraintWithOffset::ScalationConstraintWithOffset
								(AbstractConstraint *constraint, 
								 const Init &init)
:ConstraintDecorator(constraint)
{
	priority = High;	// default
	
	this->scaleThis = init.scaleThis;
	this->scaleFrom = init.scaleFrom;
	
	offset = *scaleThis - *scaleFrom;
}

ScalationConstraintWithOffset::~ScalationConstraintWithOffset()
{
}

void ScalationConstraintWithOffset::update(double)
{
	*scaleThis += offset;
}

} // constr
} // vs
