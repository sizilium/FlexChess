#include <vs/managed/ph/AbstractPhysicFactory.h>
#include <vs/base/util/DefaultManaged.h>

namespace vs
{
namespace managed
{
namespace ph
{
using namespace core::ph;
using namespace std;
using namespace base::util;

AbstractPhysicFactory::~AbstractPhysicFactory()
{
	this->manager = NULL;
}

void AbstractPhysicFactory::addManaged(DefaultManaged *managed)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addManaged(managed);	
}

void AbstractPhysicFactory::addPoint(Point *point, const string &name)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addPoint(point, name);
}

void AbstractPhysicFactory::addOrientatedPoint(OrientatedPoint *orientatedPoint, const string &name)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addOrientatedPoint(orientatedPoint, name);
}

void AbstractPhysicFactory::addEuler(Euler *euler, const string &name)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addEuler(euler, name);
}

const string AbstractPhysicFactory::getNamespace() const
{
	return "ph";
}


} // ph
} // managed
} // vs
