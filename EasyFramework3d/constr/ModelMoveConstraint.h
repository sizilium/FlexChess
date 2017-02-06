/**
 * @file ModelMoveConstraint.h
 * @author sizilium
 * @date 13.01.2008
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODEL_MOVE_CONSTRAINT_H
#define MODEL_MOVE_CONSTRAINT_H

// includes
#include <vs/Build.hpp>
#include <vs/constr/ConstraintDecorator.hpp>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
// predeclarations
namespace managed {namespace gl {namespace model {class ManagedModel; }}}

namespace constr
{
using namespace base::interfaces;

/** @class ModelMoveConstraint
 * 
 */
class VS_EXPORT ModelMoveConstraint : public ConstraintDecorator
{
public:
	ModelMoveConstraint(base::interfaces::AbstractConstraint *constraint, 
	                    managed::gl::model::ManagedModel *model, unsigned int modelId,
	                    base::math::DoubleVector startCoord, 
	                    base::math::DoubleVector endCoord,
	                    double speed);	// speed: LE per second
	~ModelMoveConstraint();
	
	void setNewTarget(base::math::DoubleVector endCoord);
	
	void update(double deltaT);	
	
private:
	managed::gl::model::ManagedModel *model;
	unsigned int modelId;
	base::math::DoubleVector actualCoords, startCoords, endCoords, directionVec;
	double time, maxTime;
};

} // constr
}
// vs

#endif  // MODEL_MOVE_CONSTRAINT_H
