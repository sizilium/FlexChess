#include <vs/managed/plug/PluginManager.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace managed
{
namespace plug
{
using namespace base::interfaces;
using namespace base::util;
using namespace base::cont;

PluginManager::PluginManager()
{

}

PluginManager::~PluginManager()
{
}

void PluginManager::update(double deltaT)
{
	managment.update(deltaT);
}

void PluginManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *cast = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(cast);
	cast->attach(&managment);
}

void PluginManager::getManagedNames(JavaStyleContainer<std::string> *names) const
{
	managment.getManagedNames(names);
}

AbstractManaged* PluginManager::getManaged(const string &name) const
{
	return managment.getManaged(name);
}
		
void PluginManager::removeManaged(const string &name)
{
	managment.removeManaged(name);
}

void PluginManager::clear()
{
	managment.clear();
}

void PluginManager::outDebug() const
{
	
}

} // plug
} // managed
} // vs
