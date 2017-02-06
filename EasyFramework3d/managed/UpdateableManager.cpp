#include <vs/managed/UpdateableManager.h>
#include <vs/managed/AbstractUpdateableFactory.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace managed
{
using namespace vs::base::interfaces;
using namespace vs::base::util;
using namespace vs::base::cont;

UpdateableManager::UpdateableManager()
{

}

UpdateableManager::~UpdateableManager()
{
}

void UpdateableManager::update(double deltaT)
{
	managment.update(deltaT);
}

void UpdateableManager::getManagedNames(JavaStyleContainer<std::string> * /*names*/) const
{
	
}

void UpdateableManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *cast = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(cast);
	cast->attach(&managment);
}

AbstractManaged* UpdateableManager::getManaged(const std::string &name) const
{
	return managment.getManaged(name);
}
		
void UpdateableManager::removeManaged(const std::string &name)
{
	managment.removeManaged(name);
}

void UpdateableManager::clear()
{
	managment.clear();
}

void UpdateableManager::outDebug() const
{
	managment.outDebug();
}

} // managed
} // vs
