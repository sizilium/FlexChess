#include <vs/constr/ModelConstraintFactory.h>
#include <vs/constr/ModelMoveConstraint.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/constr/Constraint.hpp>

namespace vs
{
namespace constr
{
using namespace base::math;
using namespace base::interfaces;
using namespace managed::gl::model;


ModelConstraintFactory::ModelConstraintFactory()
{
	
}

ModelConstraintFactory::~ModelConstraintFactory()
{
}

const string ModelConstraintFactory::getName() const
{
	return "ModelConstraintFactory";
}

AbstractConstraint* ModelConstraintFactory::createModelMoveConstraint (
													managed::gl::model::ManagedModel *model,
													unsigned int modelId,
													base::math::DoubleVector startCoord,
													base::math::DoubleVector endCoord,
													double time,
													const std::string &name)
{
	Constraint *base = new Constraint(name);
	AbstractConstraint *constraint;
	
	constraint = new ModelMoveConstraint(base, model, modelId, startCoord, endCoord, time);
	constraint->setName(name);

	// AbstractConstraintFactory
	this->addManaged(constraint);

	return constraint;
}

} // constr
} // vs
