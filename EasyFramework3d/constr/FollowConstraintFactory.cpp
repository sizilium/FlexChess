#include <vs/constr/FollowConstraintFactory.h>
#include <vs/constr/TranslationConstraint.h>
#include <vs/constr/TranslationConstraintWithOffset.h>
#include <vs/constr/RotationConstraint.h>
#include <vs/constr/RotationConstraintWithOffset.h>
#include <vs/constr/ScalationConstraintWithOffset.h>
#include <vs/constr/ScalationConstraint.h>
#include <vs/constr/Constraint.hpp>
#include <vs/base/math/DoubleVector.h>
#include <vs/core/ph/MovingOrientatedPoint.h>
#include <vs/core/ph/RigidBody.h>
#include <vs/core/ph/Point.h>
#include <vs/core/ph/Euler.h>
#include <vs/core/ph/OrientatedPoint.h>

namespace vs
{
namespace constr
{
using namespace core::ph;
using namespace base::interfaces;
using namespace base::math;
using namespace base::xml;

FollowConstraintFactory::FollowConstraintFactory()
{

}

FollowConstraintFactory::~FollowConstraintFactory()
{
}

const string FollowConstraintFactory::getName() const
{
	return "FollowConstraintFactory";
}

AbstractConstraint* FollowConstraintFactory::createTranslationConstraint
												(Point *p1,
												 const Point *p2,
												 bool withOffset,
												 const string &name)
{
	Constraint *base = new Constraint(name);
	AbstractConstraint *constraint;

	if (withOffset)
	{
		TranslationConstraintWithOffset::Init init;
		init.p1 = p1;
		init.p2 = p2;
		constraint = new TranslationConstraintWithOffset(base, init);
		constraint->setName(name);
	}
	else
	{
		TranslationConstraint::Init init;
		init.p1 = p1;
		init.p2 = p2;
		constraint = new TranslationConstraint(base, init);
		constraint->setName(name);
	}

	// AbstractConstraintFactory
	this->addManaged(constraint);

	return constraint;
}

AbstractConstraint* FollowConstraintFactory::createRotationConstraint
												(Euler *e1,
												 const Euler *e2,
												 bool withOffset,
												 const string &name)
{
	Constraint *base = new Constraint(name);
	AbstractConstraint *constraint;

	if (withOffset)
	{
		RotationConstraintWithOffset::Init init;
		init.e1 = e1;
		init.e2 = e2;
		constraint = new RotationConstraintWithOffset(base, init);
		constraint->setName(name);
	}
	else
	{
		RotationConstraint::Init init;
		init.e1 = e1;
		init.e2 = e2;
		constraint = new RotationConstraint(base, init);
		constraint->setName(name);
	}

	// AbstractConstraintFactory
	this->addManaged(constraint);

	return constraint;
}

AbstractConstraint* FollowConstraintFactory::createScalationConstraint
											(DoubleVector *scaleThis,
											 const DoubleVector *scaleFrom,
											 bool withOffset,
											 const string &name)
{
	Constraint *base = new Constraint(name);
	AbstractConstraint *constraint;

	if (withOffset)
	{
		ScalationConstraintWithOffset::Init init;
		init.scaleThis = scaleThis;
		init.scaleFrom = scaleFrom;
		constraint = new ScalationConstraintWithOffset(base, init);
		constraint->setName(name);
	}
	else
	{
		ScalationConstraint::Init init;
		init.scaleThis = scaleThis;
		init.scaleFrom = scaleFrom;
		constraint = new ScalationConstraint(base, init);
		constraint->setName(name);
	}

	// AbstractConstraintFactory
	this->addManaged(constraint);

	return constraint;
}

AbstractConstraint* FollowConstraintFactory::createTransRotCt
											(OrientatedPoint *p1,
											 const OrientatedPoint *p2,
											 bool withOffset, const string &name)
{
	return createTransRotHelper(p1, p2, p1, p2, withOffset, name);
}

AbstractConstraint* FollowConstraintFactory::createTransRotCt
											(MovingOrientatedPoint *p1, 
											 const MovingOrientatedPoint *p2,
											 bool withOffset, const string &name)
{
	return createTransRotHelper(p1, p2, p1, p2, withOffset, name);
}
									 
AbstractConstraint* FollowConstraintFactory::createTransRotCt
											(RigidBody *p1, 
											 const RigidBody *p2,
											 bool withOffset, 
											 const string &name)								 
{
	return createTransRotHelper(p1, p2, p1, p2, withOffset, name);
}

AbstractConstraint* FollowConstraintFactory::createTransRotHelper
												(Point *p1, 
												 const Point *p2,
												 Euler *e1, 
												 const Euler *e2,
												 bool withOffset, 
												 const string &name)
{
	Constraint *base = new Constraint(name);

	AbstractConstraint *translationCt;
	AbstractConstraint *rotationCt;

	if (withOffset)
	{
		TranslationConstraintWithOffset::Init init;
		init.p1 = p1;
		init.p2 = p2;
		translationCt = new TranslationConstraintWithOffset(base, init);
		translationCt->setName(name);

		RotationConstraintWithOffset::Init init2;
		init2.e1 = e1;
		init2.e2 = e2;
		rotationCt = new RotationConstraintWithOffset(translationCt, init2);
		rotationCt->setName(name);
	}
	else
	{
		TranslationConstraint::Init init;
		init.p1 = p1;
		init.p2 = p2;
		translationCt = new TranslationConstraint(base, init);
		translationCt->setName(name);

		RotationConstraint::Init init2;
		init2.e1 = e1;
		init2.e2 = e2;
		rotationCt = new RotationConstraint(translationCt, init2);
		rotationCt->setName(name);
	}

	// AbstractConstraintFactory
	this->addManaged(rotationCt);

	return rotationCt;
}

} // constr
} // vs
