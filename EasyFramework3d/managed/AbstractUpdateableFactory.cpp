#include <vs/managed/AbstractUpdateableFactory.h>
#include <vs/base/util/DefaultManaged.h>

namespace vs
{
namespace managed
{
using namespace std;
using namespace vs::base::util;

AbstractUpdateableFactory::~AbstractUpdateableFactory()
{
	this->manager = NULL;
}

void AbstractUpdateableFactory::addManaged(DefaultManaged *managed)
{
	manager->addManaged(managed);
}

const string AbstractUpdateableFactory::getNamespace() const
{
	return "vs";
}

} // managed
} // vs
