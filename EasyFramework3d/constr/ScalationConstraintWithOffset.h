/**
 * @file ScalationConstraintWithOffset.h
 * @author sizilium
 * @date 11.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef SCALATION_CONSTRAINT_WITH_OFFSET
#define SCALATION_CONSTRAINT_WITH_OFFSET

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace constr
{

/** @class ScalationConstraintWithOffset
 * 
 */
class VS_EXPORT ScalationConstraintWithOffset : public ConstraintDecorator
{
public:
	struct Init
	{
		base::math::DoubleVector *scaleThis;
		const base::math::DoubleVector *scaleFrom;
	};
	
	ScalationConstraintWithOffset(base::interfaces::AbstractConstraint *constraint, const Init &init);
	virtual ~ScalationConstraintWithOffset();
	
	void update(double deltaT);	
	
private:
	base::math::DoubleVector *scaleThis;
	const base::math::DoubleVector *scaleFrom;
	base::math::DoubleVector offset;
};

} // constr
} // vs

#endif  // SCALATION_CONSTRAINT_WITH_OFFSET
