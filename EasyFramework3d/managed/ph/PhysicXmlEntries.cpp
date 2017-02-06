#include <vs/managed/ph/PhysicXmlEntries.h>
#include <vs/managed/ph/PhysicFactory.h>
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

#include <vs/base/math/DoubleVector.h>

#include <vs/base/xml/XmlPrimitivesForMath.h>
#include <vs/core/ph/XmlPrimitivesForPhysic.h>

#include <assert.h>

namespace vs
{
namespace managed
{
namespace ph
{
using namespace core::ph;
using namespace base::xml;
using namespace base::cont;
using namespace base::util;
using namespace base::math;
using namespace std;

PointXmlEntry::PointXmlEntry(string name, ph::Point *point)
:AbstractXmlEntry(name), ptr(point)
{}

AbstractManaged* PointXmlEntry::read(const Tree<XmlTag*> *input)
{
	Point p;
	if (!getPointTag(input, p))
		throw XmlException (__FILE__, __LINE__, "Couldn't read PointTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	Point *point = factory.createPoint(this->getName());
	*point = p;

	return NULL;
}

void PointXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new PointTag(*ptr));
}


EulerXmlEntry::EulerXmlEntry(string name, Euler *euler)
:AbstractXmlEntry(name), ptr(euler)
{}

AbstractManaged* EulerXmlEntry::read(const Tree<XmlTag*> *input)
{
	Euler e;
	if (!getEulerTag(input, e))
		throw XmlException (__FILE__, __LINE__, "Couldn't read EulerTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	Euler *euler = factory.createEuler(this->getName());
	*euler = e;

	return NULL;
}

void EulerXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new EulerTag(*ptr));
}


OrientatedPointXmlEntry::OrientatedPointXmlEntry(string name, OrientatedPoint *orientatedPoint)
:AbstractXmlEntry(name), ptr(orientatedPoint)
{}

AbstractManaged* OrientatedPointXmlEntry::read(const Tree<XmlTag*> *input)
{
	OrientatedPoint op;
	if (!getOrientatedPointTag(input, op))
		throw XmlException (__FILE__, __LINE__, "Couldn't read OrientatedPointTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	OrientatedPoint *orientatedPoint = factory.createOrientatedPoint(this->getName());
	*orientatedPoint = op;

	return NULL;
}

void OrientatedPointXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new OrientatedPointTag(*ptr));
}


MovingPointXmlEntry::MovingPointXmlEntry(string name, MovingPoint *p)
:AbstractXmlEntry(name), ptr(p)
{}

AbstractManaged* MovingPointXmlEntry::read(const Tree<XmlTag*> *input)
{
	MovingPoint p;
	if (!getMovingPointTag(input, p))
		throw XmlException (__FILE__, __LINE__, "Couldn't read MovingPointTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	MovingPoint *movingPoint = factory.createMovingPoint(this->getName());
	*movingPoint = p;

	return movingPoint;
}

void MovingPointXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new MovingPointTag(*ptr));
}


MovingEulerXmlEntry::MovingEulerXmlEntry(string name, MovingEuler *e)
:AbstractXmlEntry(name), ptr(e)
{}

AbstractManaged* MovingEulerXmlEntry::read(const Tree<XmlTag*> *input)
{
	MovingEuler e;
	if (!getMovingEulerTag(input, e))
		throw XmlException (__FILE__, __LINE__, "Couldn't read MovingEulerTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	MovingEuler *movingEuler = factory.createMovingEuler(this->getName());
	*movingEuler = e;
	
	return movingEuler;
}

void MovingEulerXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new MovingEulerTag(*ptr));
}


MovingOrientatedPointXmlEntry::MovingOrientatedPointXmlEntry(string name, MovingOrientatedPoint *p)
:AbstractXmlEntry(name), ptr(p)
{}

AbstractManaged* MovingOrientatedPointXmlEntry::read(const Tree<XmlTag*> *input)
{
	MovingOrientatedPoint mop;
	if (!getMovingOrientatedPointTag(input, mop))
		throw XmlException (__FILE__, __LINE__, "Couldn't read MovingOrientatedPointTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	MovingOrientatedPoint *p = factory.createMovingOrientatedPoint(this->getName());
	*p = mop;
	
	return p;
}

void MovingOrientatedPointXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new MovingOrientatedPointTag(*ptr));
}


AcceleratingPointXmlEntry::AcceleratingPointXmlEntry(string name, AcceleratingPoint *p)
:AbstractXmlEntry(name), ptr(p)
{}

AbstractManaged* AcceleratingPointXmlEntry::read(const Tree<XmlTag*> *input)
{
	AcceleratingPoint accp;
	if (!getAcceleratingPointTag(input, accp))
		throw XmlException (__FILE__, __LINE__, "Couldn't read AcceleratingPointTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	AcceleratingPoint *p = factory.createAcceleratingPoint(this->getName());
	*p = accp;

	return p;
}

void AcceleratingPointXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new AcceleratingPointTag(*ptr));
}


AcceleratingEulerXmlEntry::AcceleratingEulerXmlEntry(string name, AcceleratingEuler *acce)
:AbstractXmlEntry(name), ptr(acce)
{}

AbstractManaged* AcceleratingEulerXmlEntry::read(const Tree<XmlTag*> *input)
{
	AcceleratingEuler acce;
	if (!getAcceleratingEulerTag(input, acce))
		throw XmlException (__FILE__, __LINE__, "Couldn't read AcceleratingEulerTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	AcceleratingEuler *e = factory.createAcceleratingEuler(this->getName());
	*e = acce;

	return e;
}

void AcceleratingEulerXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new AcceleratingEulerTag(*ptr));
}


PointBodyXmlEntry::PointBodyXmlEntry(string name, PointBody *p)
:AbstractXmlEntry(name), ptr(p)
{}

AbstractManaged* PointBodyXmlEntry::read(const Tree<XmlTag*> *input)
{
	PointBody pointBody;
	if (!getPointBodyTag(input, pointBody))
		throw XmlException (__FILE__, __LINE__, "Couldn't read PointBodyTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	PointBody *pb = factory.createPointBody(this->getName());
	*pb = pointBody;

	return pb;
}

void PointBodyXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new PointBodyTag(*ptr));
}


RigidBodyXmlEntry::RigidBodyXmlEntry(string name, RigidBody *pb)
:AbstractXmlEntry(name), ptr(pb)
{}

AbstractManaged* RigidBodyXmlEntry::read(const Tree<XmlTag*> *input)
{
	RigidBody rigidBody;
	if (!getRigidBodyTag(input, rigidBody))
		throw XmlException (__FILE__, __LINE__, "Couldn't read RigidBodyTag from tree (generated from xml file)!");
	
	PhysicFactory factory;
	RigidBody *rb = factory.createRigidBody(this->getName());
	*rb = rigidBody;
	
	return rb;
}

void RigidBodyXmlEntry::write(Tree<XmlTag*> *output)
{
	output->add(new RigidBodyTag(*ptr));
}

} // ph
} // managed
} // vs
