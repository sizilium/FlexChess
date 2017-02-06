/**
 * @file RotationConstraint.h
 * @author sizilium
 * @date 11.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ROTATION_CONSTRAINT_H
#define ROTATION_CONSTRAINT_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>

namespace vs
{
// predeclarations
namespace core { namespace ph {class Euler; }}

namespace constr
{

/** @class RotationConstraint
 * 
 */
class VS_EXPORT RotationConstraint : public ConstraintDecorator
{
public:
	struct Init
	{
		core::ph::Euler *e1;
		const core::ph::Euler *e2;
	};
	
	RotationConstraint(base::interfaces::AbstractConstraint *constraint, const Init &init);
	virtual ~RotationConstraint();
	
	void update(double deltaT);	
	
private:
	core::ph::Euler *e1;
	const core::ph::Euler *e2;
};

} // constr
} // vs

#endif  // ROTATION_CONSTRAINT_H
