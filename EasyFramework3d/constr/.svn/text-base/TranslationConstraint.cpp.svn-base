#include <vs/constr/TranslationConstraint.h>
#include <vs/core/ph/Point.h>

namespace vs
{
namespace constr
{
using namespace base::interfaces;

TranslationConstraint::TranslationConstraint
						(AbstractConstraint *constraint, 
						 const Init &init)
:ConstraintDecorator(constraint)
{
	priority = High;	// default
	
	this->p1 = init.p1;
	this->p2 = init.p2;
}

TranslationConstraint::~TranslationConstraint()
{
}

void TranslationConstraint::update(double)
{
	*p1 = *p2;
}

} // constr
} // vs
