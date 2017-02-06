#include <vs/base/util/DefaultManagedGroup.h>

namespace vs
{
namespace base
{
namespace util
{
using namespace base::cont;

DefaultManagedGroup::DefaultManagedGroup()
{
}

DefaultManagedGroup::~DefaultManagedGroup()
{
	clear();
}

void DefaultManagedGroup::notify(DefaultManagedMessage &message)
{
	List<DefaultManaged *>::Iterator it;
	
	// if managed deleted remove old link
	if (message.toDelete)
	{
		it = findByName (message.managed->getName(), group);
		if (it != group.end())
			group.erase(it);
	}
}

void DefaultManagedGroup::clear()
{
	// loose all observer connections
	List<DefaultManaged *>::Iterator it (group);
	while (it.hasNext())
		it.next()->detach(this);
	
	// remove all links
	group.clear();
}

int DefaultManagedGroup::size() const
{
	return group.size();
}

void DefaultManagedGroup::removeAndClear()
{
	List<DefaultManaged *>::Iterator it (group);
	while (it.hasNext())
		delete it.next();
	group.clear();
}

void DefaultManagedGroup::addManaged(DefaultManaged *op2)
{
	// connect observer messages
	op2->attach(this);
	
	// add link to group
	if (!group.contains(op2))
		group.push_back(op2);
}

void DefaultManagedGroup::removeManaged(DefaultManaged *op2)
{
	// loose the observer connection
	op2->detach(this);
	
	// remove link
	group.remove(op2);
}

DefaultManaged* DefaultManagedGroup::operator=(DefaultManaged *op2)
{
	if (op2 != this)
	{
		addManaged(op2);
	}
	return op2;
}

void DefaultManagedGroup::update(double deltaT)
{
	// activate all members
	List<DefaultManaged *>::Iterator it (group);
	while (it.hasNext())
		it.next()->update(deltaT);
}

void DefaultManagedGroup::activate()
{
	// activate all members
	List<DefaultManaged *>::Iterator it (group);
	while (it.hasNext())
		it.next()->activate();
	
	// activate group object
	DefaultManaged::activate();
}

void DefaultManagedGroup::deactivate()
{
	// deactivate all members
	List<DefaultManaged *>::Iterator it (group);
	while (it.hasNext())
		it.next()->deactivate();
	
	// deactivate group object
	DefaultManaged::deactivate();
}

std::vector<std::string> DefaultManagedGroup::getNames() const
{
	vector<string> retList;
	
	// deactivate all members
	List<DefaultManaged *>::Const_Iterator it (group);
	while (it.hasNext())
		retList.push_back(it.next()->getName());
	
	return retList;
}

List<DefaultManaged*>::Iterator DefaultManagedGroup::findByName(const string &name, List<DefaultManaged*> &inList)
{
	List<DefaultManaged*>::Iterator it (inList);
	while (it != inList.end())
	{
		if ((*it)->getName() == name)
			break;
		++it;
	}
	return it;
}

} // util
} // base
} // vs
