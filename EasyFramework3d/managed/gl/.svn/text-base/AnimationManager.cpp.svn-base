#include <vs/managed/gl/AnimationManager.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace base::interfaces;
using namespace base::cont;
using namespace base::util;

AnimationManager::AnimationManager()
{
	
}

AnimationManager::~AnimationManager()
{
}

void AnimationManager::getManagedNames(JavaStyleContainer<std::string> *names) const
{
	managment.getManagedNames(names);
}

AbstractManaged* AnimationManager::getManaged(const string &name) const
{
	return managment.getManaged(name);
}

void AnimationManager::removeManaged(const string &name)
{
	managment.removeManaged(name);
}

void AnimationManager::update(double deltaT)
{
	managment.update(deltaT);
}

void AnimationManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *cast = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(cast);
	cast->attach(&managment);
}

void AnimationManager::clear()
{
	managment.clear();
}

void AnimationManager::outDebug() const
{
	managment.outDebug();
}


} // gl
} // managed
} // vs
