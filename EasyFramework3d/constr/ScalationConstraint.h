/**
 * @file ScalationConstraint.h
 * @author sizilium
 * @date 11.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef SCALATION_CONSTRAINT_H
#define SCALATION_CONSTRAINT_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>

namespace vs
{
// predeclarations
namespace base { namespace math {class DoubleVector; }}

namespace constr
{

/** @class ScalationConstraint
 * 
 */
class VS_EXPORT ScalationConstraint : public ConstraintDecorator
{
public:
	struct Init
	{
		base::math::DoubleVector *scaleThis;
		const base::math::DoubleVector *scaleFrom;
	};
	
	ScalationConstraint(base::interfaces::AbstractConstraint *constraint, const Init &init);
	virtual ~ScalationConstraint();
	
	void update(double deltaT);	
	
private:
	base::math::DoubleVector *scaleThis;
	const base::math::DoubleVector *scaleFrom;
};

} // constr
} // vs

#endif  // SCALATION_CONSTRAINT_H
