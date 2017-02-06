#include <vs/constr/ConstraintManager.h>
#include <vs/base/interfaces/AbstractConstraint.hpp>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace constr
{
using namespace std;
using namespace base::interfaces;
using namespace base::util;
using namespace base::cont;

ConstraintManager::ConstraintManager()
{

}

ConstraintManager::~ConstraintManager()
{

}

void ConstraintManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *cast = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(cast);
	cast->attach(&managment);
}

void ConstraintManager::getManagedNames(JavaStyleContainer<string> *names) const
{
	return managment.getManagedNames(names);
}

AbstractManaged* ConstraintManager::getManaged(const string &name) const
{
	return managment.getManaged(name);
}

void ConstraintManager::getAllConstraints(StringList<AbstractConstraint *> &stringList) const
{
	StringList<DefaultManaged *> list;
	StringList<DefaultManaged *>::Iterator it;

	managment.getAllManaged(list);
	
	it = list.begin();
	while (it.hasNext())
	{
		AbstractConstraint *tmp;
		tmp = dynamic_cast<AbstractConstraint *> (*it);
		if (tmp)
			stringList.add(tmp, (*it)->getName());
		++it;
	}
}

void ConstraintManager::removeManaged(const string &name)
{
	managment.removeManaged(name);
}

void ConstraintManager::schedule()
{
	
}

void ConstraintManager::update(double deltaT)
{
	managment.update(deltaT);
	
	// check old constraints (deletion)
	StringList<DefaultManaged *> list;
	StringList<DefaultManaged *>::Iterator it;

	managment.getAllManaged(list);
	
	it = list.begin();
	while (it.hasNext())
	{
		AbstractConstraint *tmp;
		tmp = dynamic_cast<AbstractConstraint *> (*it);
		if (tmp && tmp->toDelete())
			managment.removeManaged((*it)->getName());
		++it;
	}
}

void ConstraintManager::clear()
{
	managment.clear();
}

void ConstraintManager::outDebug() const
{
	managment.outDebug();
}

} // constr

} // vs
