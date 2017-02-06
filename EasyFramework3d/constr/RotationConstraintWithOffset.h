/**
 * @file RotationConstraintWithOffset.h
 * @author sizilium
 * @date 11.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ROTATION_CONSTRAINT_WITHOFFSET
#define ROTATION_CONSTRAINT_WITHOFFSET

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
// predeclarations
namespace core {namespace ph {class Euler; }}

namespace constr
{

/** @class RotationConstraintWithOffset
 * 
 */
class VS_EXPORT RotationConstraintWithOffset : public ConstraintDecorator
{
public:
	struct Init
	{
		core::ph::Euler *e1;
		const core::ph::Euler *e2;
	};
	
	RotationConstraintWithOffset(base::interfaces::AbstractConstraint *constraint, const Init &init);
	virtual ~RotationConstraintWithOffset();
	
	void update(double deltaT);	
	
private:
	core::ph::Euler *e1;
	const core::ph::Euler *e2;
	base::math::DoubleVector offset;
};

} // constr
} // vs

#endif  // ROTATION_CONSTRAINT_WITHOFFSET
