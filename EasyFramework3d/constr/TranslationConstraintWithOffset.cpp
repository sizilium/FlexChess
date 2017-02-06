#include <vs/constr/TranslationConstraintWithOffset.h>
#include <vs/core/ph/Point.h>

namespace vs
{
namespace constr
{
using namespace base::interfaces;

TranslationConstraintWithOffset::TranslationConstraintWithOffset
									(AbstractConstraint *constraint, 
									 const Init &init)
:ConstraintDecorator(constraint)
{
	priority = High;	// default
	
	this->p1 = init.p1;
	this->p2 = init.p2;
	
	offset = p1->getCoords() - p2->getCoords();
}

TranslationConstraintWithOffset::~TranslationConstraintWithOffset()
{
}

void TranslationConstraintWithOffset::update(double /*time*/)
{
	p1->setCoords(p2->getCoords() + offset);
}

} // constr
} // vs
