#include <vs/core/ph/XmlPrimitivesForPhysic.h>
#include <vs/base/xml/XmlPrimitivesForMath.h>
#include <vs/core/ph/Point.h>
#include <vs/core/ph/Euler.h>
#include <vs/core/ph/OrientatedPoint.h>
#include <vs/core/ph/MovingPoint.h>
#include <vs/core/ph/MovingEuler.h>
#include <vs/core/ph/MovingOrientatedPoint.h>
#include <vs/core/ph/AcceleratingPoint.h>
#include <vs/core/ph/PointBody.h>
#include <vs/core/ph/RigidBody.h>
#include <vs/core/ph/AcceleratingEuler.h>
#include <vs/base/cont/SmartIterator.hpp>

namespace vs
{
namespace core
{
namespace ph
{
using namespace base::cont;
using namespace base::math;

PointTag::PointTag(const Point &point)
{
	this->coords = point.getCoords();
}

PointTag::PointTag(double x, double y, double z)
{
	coords = DoubleVector(x, y, z);
}

void PointTag::cout(ofstream &os) const
{
	DoubleVectorTag tmp("coords", coords);
	tmp.cout(os);
}

void PointTag::cout(ostream &os) const
{
	DoubleVectorTag tmp("coords", coords);
	tmp.cout(os);
}

bool getPointTag (const Tree<XmlTag*> *tree, Point &point)
{
	DoubleVector tmp;
	bool retVal = getDoubleVector("coords", tree, tmp);
	point.setCoords(tmp);
	return retVal;
}


EulerTag::EulerTag(const Euler &rotation)
{
	this->rotation = rotation.getRotation();
}

EulerTag::EulerTag(double a, double b, double c)
{
	rotation = DoubleVector(a, b, c);
}

void EulerTag::cout(ofstream &os) const
{
	DoubleVectorTag tmp("rotation", rotation);
	tmp.cout(os);
}

void EulerTag::cout(ostream &os) const
{
	DoubleVectorTag tmp("rotation", rotation);
	tmp.cout(os);
}

bool getEulerTag (const Tree<XmlTag*> *tree, Euler &euler)
{
	DoubleVector tmp;
	bool retVal = getDoubleVector("rotation", tree, tmp);
	euler.setRotation(tmp);
	return retVal;
}


OrientatedPointTag::OrientatedPointTag(const OrientatedPoint &orientatedPoint)
:PointTag(orientatedPoint), EulerTag(orientatedPoint)
{}

void OrientatedPointTag::cout(ofstream &os) const
{
	PointTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	EulerTag::cout(os);
}

void OrientatedPointTag::cout(ostream &os) const
{
	PointTag::cout(os);
	os << newSpacedLine(this->getSpace());
	EulerTag::cout(os);
}

bool getOrientatedPointTag (const Tree<XmlTag*> *tree, OrientatedPoint &orientatedPoint)
{
	bool retVal_1 = getPointTag(tree, orientatedPoint);
	bool retVal_2 = getEulerTag(tree, orientatedPoint);
	return retVal_1 && retVal_2;
}


MovingPointTag::MovingPointTag(const MovingPoint &movingPoint)
:PointTag(movingPoint)
{
	this->velocity = movingPoint.getV();
}

void MovingPointTag::cout(ofstream &os) const
{
	PointTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	DoubleVectorTag tmp("velocity", velocity);
	tmp.cout(os);
}

void MovingPointTag::cout(ostream &os) const
{
	PointTag::cout(os);
	os << newSpacedLine(this->getSpace());
	DoubleVectorTag tmp("velocity", velocity);
	tmp.cout(os);
}

bool getMovingPointTag (const Tree<XmlTag*> *tree, MovingPoint &movingPoint)
{
	bool retVal_1 = getPointTag(tree, movingPoint);
	DoubleVector tmp;
	bool retVal_2 = getDoubleVector("velocity", tree, tmp);
	movingPoint.setV(tmp);
	return retVal_1 && retVal_2;
}


MovingEulerTag::MovingEulerTag(const MovingEuler &movingEuler)
:EulerTag(movingEuler)
{
	this->torque = movingEuler.getTorque();
}

void MovingEulerTag::cout(ofstream &os) const
{
	EulerTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	DoubleVectorTag tmp("torque", torque);
	tmp.cout(os);
}

void MovingEulerTag::cout(ostream &os) const
{
	EulerTag::cout(os);
	os << newSpacedLine(this->getSpace());
	DoubleVectorTag tmp("torque", torque);
	tmp.cout(os);
}

bool getMovingEulerTag (const Tree<XmlTag*> *tree, MovingEuler &movingEuler)
{
	bool retVal_1 = getEulerTag(tree, movingEuler);
	DoubleVector tmp;
	bool retVal_2 = getDoubleVector("torque", tree, tmp);
	movingEuler.setTorque(tmp);
	return retVal_1 && retVal_2;
}


MovingOrientatedPointTag::MovingOrientatedPointTag(const MovingOrientatedPoint &mop)
:MovingPointTag(mop), MovingEulerTag(mop)
{
}

void MovingOrientatedPointTag::cout(ofstream &os) const
{
	MovingPointTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	MovingEulerTag::cout(os);
}

void MovingOrientatedPointTag::cout(ostream &os) const
{
	MovingPointTag::cout(os);
	os << newSpacedLine(this->getSpace());
	MovingEulerTag::cout(os);
}

bool getMovingOrientatedPointTag (const Tree<XmlTag*> *tree, MovingOrientatedPoint &mop)
{
	bool retVal_1 = getMovingPointTag(tree, mop);
	bool retVal_2 = getMovingEulerTag(tree, mop);
	return retVal_1 && retVal_2;
}


AcceleratingPointTag::AcceleratingPointTag(const AcceleratingPoint &accp)
:MovingPointTag(accp)
{
	this->acceleration = accp.getA();
}

void AcceleratingPointTag::cout(ofstream &os) const
{
	MovingPointTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	DoubleVectorTag tmp("acceleration", acceleration);
	tmp.cout(os);
}

void AcceleratingPointTag::cout(ostream &os) const
{
	MovingPointTag::cout(os);
	os << newSpacedLine(this->getSpace());
	DoubleVectorTag tmp("acceleration", acceleration);
	tmp.cout(os);
}

bool getAcceleratingPointTag (const Tree<XmlTag*> *tree, AcceleratingPoint &accp)
{
	bool retVal_1 = getMovingPointTag(tree, accp);
	DoubleVector tmp;
	bool retVal_2 = getDoubleVector("acceleration", tree, tmp);
	accp.setA(tmp);
	return retVal_1 && retVal_2;
}


AcceleratingEulerTag::AcceleratingEulerTag(const AcceleratingEuler &acce)
:MovingEulerTag(acce)
{
	this->torqueA = acce.getTorqueA();
}

void AcceleratingEulerTag::cout(ofstream &os) const
{
	MovingEulerTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	DoubleVectorTag tmp("torqueA", torqueA);
	tmp.cout(os);
}

void AcceleratingEulerTag::cout(ostream &os) const
{
	MovingEulerTag::cout(os);
	os << newSpacedLine(this->getSpace());
	DoubleVectorTag tmp("torqueA", torqueA);
	tmp.cout(os);
}

bool getAcceleratingEulerTag (const Tree<XmlTag*> *tree, AcceleratingEuler &acce)
{
	bool retVal_1 = getMovingEulerTag(tree, acce);
	DoubleVector tmp;
	bool retVal_2 = getDoubleVector("torqueA", tree, tmp);
	acce.setTorqueA(tmp);
	return retVal_1 && retVal_2;
}


PointBodyTag::PointBodyTag(const PointBody &pointBody)
:AcceleratingPointTag(pointBody)
{
	this->mass = pointBody.getMass();
}

void PointBodyTag::cout(ofstream &os) const
{
	AcceleratingPointTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	os << Value("mass", mass);
}

void PointBodyTag::cout(ostream &os) const
{
	AcceleratingPointTag::cout(os);
	os << newSpacedLine(this->getSpace());
	os << Value("mass", mass);
}

bool getPointBodyTag (const Tree<XmlTag*> *tree, PointBody &pointBody)
{
	bool retVal_1 = getAcceleratingPointTag(tree, pointBody);
	bool retVal_2 = false;

	// get mass
	Tree<XmlTag*>::Const_Iterator it (tree);
	while (it.hasNext())
	{
		if (it.current()->getName() == "mass")
		{
			retVal_2 = true;
			pointBody.setMass(atof(it.current()->getValue().c_str()));
			break;
		}
		it.next();
	}
	return retVal_1 && retVal_2;
}


RigidBodyTag::RigidBodyTag(const RigidBody &rigidBody)
:PointBodyTag(rigidBody), AcceleratingEulerTag(rigidBody)
{

}

void RigidBodyTag::cout(ofstream &os) const
{
	PointBodyTag::cout(os);
	os << newSpacedLine(this->getSpace()).c_str();
	AcceleratingEulerTag::cout(os);
//	os << newSpacedLine(this->getSpace()).c_str();
}

void RigidBodyTag::cout(ostream &os) const
{
	PointBodyTag::cout(os);
	os << newSpacedLine(this->getSpace());
	AcceleratingEulerTag::cout(os);
//	os << newSpacedLine(this->getSpace());
}

bool getRigidBodyTag (const Tree<XmlTag*> *tree, RigidBody &rigidBody)
{               
	bool retVal_1 = getPointBodyTag(tree, rigidBody);
	bool retVal_2 = getAcceleratingEulerTag(tree, rigidBody);
// ...
	
	return retVal_1 && retVal_2;
}


} // ph
} // core
} // vs
