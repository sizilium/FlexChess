#include <vs/managed/ph/PhysicManager.h>
#include <vs/managed/ph/AbstractPhysicFactory.h>
#include <vs/core/ph/Point.h>
#include <vs/core/ph/OrientatedPoint.h>
#include <vs/core/ph/Euler.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace managed
{
namespace ph
{
using namespace core::ph;
using namespace base::interfaces;
using namespace base::util;
using namespace base::cont;

PhysicManager::PhysicManager()
{
	
}

PhysicManager::~PhysicManager()
{

}

void PhysicManager::update(double deltaT)
{
	managment.update(deltaT);
}

void PhysicManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *cast = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(cast);
	cast->attach(&managment);
}

void PhysicManager::addPoint(Point *point, const string &name)
{
	points.push_back(point, name);
}

void PhysicManager::addOrientatedPoint(OrientatedPoint *orientatedPoint, const string &name)
{
	orientatedPoints.push_back(orientatedPoint, name);
}

void PhysicManager::addEuler(Euler *euler, const string &name)
{
	eulers.push_back(euler, name);
}

void PhysicManager::getManagedNames(JavaStyleContainer<std::string> *names) const
{
	managment.getManagedNames(names);
}

AbstractManaged* PhysicManager::getManaged(const string &name) const
{
	return managment.getManaged(name);
}

Point* PhysicManager::getPoint(const string &name) const
{
	StringList<Point*>::Iterator it;
	if (points.byName(name, it))
		return *it;
	else
		return NULL;
}

OrientatedPoint* PhysicManager::getOrientatedPoint(const string &name) const
{
	StringList<OrientatedPoint*>::Iterator it;
	if (orientatedPoints.byName(name, it))
		return *it;
	else
		return NULL;
}

Euler* PhysicManager::getEuler(const string &name) const
{
	StringList<Euler*>::Iterator it;
	if (eulers.byName(name, it))
		return *it;
	else
		return NULL;
}
		
void PhysicManager::removeManaged(const string &name)
{
	managment.removeManaged(name);
}

void PhysicManager::getAllManaged(StringList<DefaultManaged *> &stringList) const
{
	managment.getAllManaged(stringList);
}

void PhysicManager::getAllPoints(StringList<Point *> &stringList) const
{
	stringList = points;
}
	
void PhysicManager::getAllOrientatedPoints(StringList<OrientatedPoint *> &stringList) const
{
	stringList = orientatedPoints;
}
	
void PhysicManager::getAllEulers(StringList<Euler *> &stringList) const
{
	stringList = eulers;
}

void PhysicManager::clear()
{
	managment.clear();
}

void PhysicManager::outDebug() const
{
	out << "PhysicManager:"; // << endl;
	managment.outDebug();
}

} // ph
} // managed
} // vs
