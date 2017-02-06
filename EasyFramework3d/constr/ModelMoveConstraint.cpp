#include <vs/constr/ModelMoveConstraint.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <list>
#include <iostream>
#include <vs/base/util/Exception.h>

namespace vs
{
namespace constr
{
using namespace std;
using namespace base::math;
using namespace managed::gl::model;
using namespace vs::base::util;


ModelMoveConstraint::ModelMoveConstraint(AbstractConstraint *constraint, 
                                         ManagedModel *model, 
                                         unsigned int modelId,
                                         DoubleVector start, 
                                         DoubleVector end,
                                         double speed)
:ConstraintDecorator(constraint), model(model), modelId(modelId), startCoords(start), endCoords(end), 
time(0)
{
	assert(model);
	
	actualCoords = startCoords;
	directionVec = endCoords - startCoords;
	
	// t = s / v
	maxTime = (directionVec.abs() / speed) * 1000;
}

ModelMoveConstraint::~ModelMoveConstraint()
{
	
}

void ModelMoveConstraint::setNewTarget(DoubleVector endCoord)
{
	this->endCoords = endCoords;
	this->startCoords = actualCoords;
	directionVec = endCoords - startCoords;
}

void ModelMoveConstraint::update(double deltaT)
{
	assert(model);
	assert(modelId != 0);
	
	list<double>::iterator posIterator = model->getObjCenterIt(modelId);

	time += deltaT;
	
	if (time >= maxTime)
	{
		time = maxTime;
    
		actualCoords = endCoords;
		
        *posIterator++ = endCoords.x();
        *posIterator++ = endCoords.y();
        *posIterator = endCoords.z();
        
     	deleteThis();
	}
    else
    {
    	actualCoords = startCoords + directionVec * (time / maxTime);
  	
	    *posIterator++ = actualCoords.x();
	    *posIterator++ = actualCoords.y();
	    *posIterator = actualCoords.z();
    }
}

} // constr
} // vs
