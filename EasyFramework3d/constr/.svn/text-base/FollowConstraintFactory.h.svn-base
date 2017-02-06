/**
 * @file FollowConstraintFactory.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FOLLOWCONSTRAINT_FACTORY_H
#define FOLLOWCONSTRAINT_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/AbstractConstraintFactory.h>
#include <vs/base/xml/AbstractXmlFactory.h>

namespace vs
{
// predeclarations
namespace base 
{
namespace interfaces {class AbstractConstraint; }
namespace math {class DoubleVector; }
}
namespace core
{
namespace ph
{
class Point;
class Euler;
class OrientatedPoint;
class MovingOrientatedPoint;
class RigidBody;
}
}

namespace constr
{

/** @class FollowConstraintFactory
 * 
 */
class VS_EXPORT FollowConstraintFactory : 	public AbstractConstraintFactory, 
											public base::xml::AbstractXmlFactory
{
public:
	FollowConstraintFactory();
	virtual ~FollowConstraintFactory();
	const std::string getName() const;

	base::interfaces::AbstractConstraint* createTranslationConstraint
							(core::ph::Point *p1, const core::ph::Point *p2,
							 bool withOffset = true, const std::string &name = "");

	base::interfaces::AbstractConstraint* createRotationConstraint
							(core::ph::Euler *e1, const core::ph::Euler *e2,
							 bool withOffset = true, const std::string &name = "");

	base::interfaces::AbstractConstraint* createScalationConstraint
							(base::math::DoubleVector *scaleThis,
							 const base::math::DoubleVector *scaleFrom,
							 bool withOffset = true, const std::string &name = "");

	base::interfaces::AbstractConstraint* createTransRotCt
							(core::ph::OrientatedPoint *p1, const core::ph::OrientatedPoint *p2,
							 bool withOffset = true, const std::string &name = "");

	base::interfaces::AbstractConstraint* createTransRotCt
							(core::ph::MovingOrientatedPoint *p1,
							 const core::ph::MovingOrientatedPoint *p2,
							 bool withOffset = true, const std::string &name = "");

	base::interfaces::AbstractConstraint* createTransRotCt
							(core::ph::RigidBody *p1, const core::ph::RigidBody *p2,
							 bool withOffset = true, const std::string &name = "");

private:
	base::interfaces::AbstractConstraint* createTransRotHelper
							(core::ph::Point *p1, const core::ph::Point *p2,
							 core::ph::Euler *e1, const core::ph::Euler *e2,
							 bool withOffset = true, const std::string &name = "");
};

} // constr
} // vs

#endif  // FOLLOWCONSTRAINT_FACTORY_H
