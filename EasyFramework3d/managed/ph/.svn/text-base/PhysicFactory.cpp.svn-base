#include <vs/managed/ph/PhysicFactory.h>

#include <vs/core/ph/Point.h>
#include <vs/core/ph/MovingPoint.h>
#include <vs/core/ph/AcceleratingPoint.h>
#include <vs/core/ph/Euler.h>
#include <vs/core/ph/MovingEuler.h>
#include <vs/core/ph/AcceleratingEuler.h>
#include <vs/core/ph/MovingOrientatedPoint.h>
#include <vs/core/ph/OrientatedPoint.h>
#include <vs/core/ph/PointBody.h>
#include <vs/core/ph/RigidBody.h>
#include <vs/managed/ph/PhysicXmlEntries.h>

namespace vs
{
namespace managed
{
namespace ph
{
using namespace core::ph;
using namespace std;

PhysicFactory::PhysicFactory()
{
}

PhysicFactory::~PhysicFactory()
{
}

Point* PhysicFactory::createPoint(const string &name)
{
	Point *p = new Point();
	addPoint(p, name);
	
	PointXmlEntry *entry = new PointXmlEntry(name, p);
	addXmlEntry(entry);
	
	return p;
}

Euler* PhysicFactory::createEuler(const string &name)
{
	Euler *e = new Euler();
	addEuler(e, name);
	
	EulerXmlEntry *entry = new EulerXmlEntry(name, e);
	addXmlEntry(entry);
	
	return e;
}

OrientatedPoint* PhysicFactory::createOrientatedPoint (const string &name)
{
	OrientatedPoint *op = new OrientatedPoint();
	addOrientatedPoint(op, name);
	
	OrientatedPointXmlEntry *entry = new OrientatedPointXmlEntry(name, op);
	addXmlEntry(entry);
	
	return op;
}

// -----------------

MovingPoint* PhysicFactory::createMovingPoint (const string &name)
{
	MovingPoint *mvp = new MovingPoint();
	mvp->setName(name);
	addManaged(mvp);
	
	MovingPointXmlEntry *entry = new MovingPointXmlEntry(name, mvp);
	addXmlEntry(entry);

	
	return mvp;
}

AcceleratingPoint* PhysicFactory::createAcceleratingPoint (const string &name)
{
	AcceleratingPoint *accp = new AcceleratingPoint();
	accp->setName(name);
	addManaged(accp);
	
	AcceleratingPointXmlEntry *entry = new AcceleratingPointXmlEntry(name, accp);
	addXmlEntry(entry);
	
	return accp;
}

MovingEuler* PhysicFactory::createMovingEuler (const string &name)
{
	MovingEuler *mve = new MovingEuler();
	mve->setName(name);
	addManaged(mve);
	
	MovingEulerXmlEntry *entry = new MovingEulerXmlEntry(name, mve);
	addXmlEntry(entry);
	
	return mve;
}

AcceleratingEuler* PhysicFactory::createAcceleratingEuler (const string &name)
{
	AcceleratingEuler *acce = new AcceleratingEuler();
	acce->setName(name);
	addManaged(acce);
	
	AcceleratingEulerXmlEntry *entry = new AcceleratingEulerXmlEntry(name, acce);
	addXmlEntry(entry);
	
	return acce;
}

MovingOrientatedPoint* PhysicFactory::createMovingOrientatedPoint (const string &name)
{
	MovingOrientatedPoint *mvop = new MovingOrientatedPoint();
	mvop->setName(name);
	addManaged(mvop);
	
	MovingOrientatedPointXmlEntry *entry = new MovingOrientatedPointXmlEntry (name, mvop);
	addXmlEntry(entry);
	
	return mvop;
}

PointBody* PhysicFactory::createPointBody (const string &name)
{
	PointBody *pb = new PointBody();
	pb->setName(name);
	addManaged(pb);
	
	PointBodyXmlEntry *entry = new PointBodyXmlEntry (name, pb);
	addXmlEntry(entry);
	
	return pb;
}

RigidBody* PhysicFactory::createRigidBody (const string &name)
{
	RigidBody *rb = new RigidBody();
	rb->setName(name);
	addManaged(rb);
	
	RigidBodyXmlEntry *entry = new RigidBodyXmlEntry (name, rb);
	addXmlEntry(entry);
	
	return rb;
}

const string PhysicFactory::getName() const
{
	return "PhysicFactory";
}


} // ph
} // managed
} // vs
