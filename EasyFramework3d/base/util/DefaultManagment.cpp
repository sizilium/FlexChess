#include <vs/base/util/DefaultManagment.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/cont/SmartIterator.hpp>
#include <vs/base/util/IOStream.h>

namespace vs
{
namespace base
{
namespace util
{
using namespace std;
using namespace cont;

DefaultManagment::DefaultManagment()
{
	
}

DefaultManagment::~DefaultManagment()
{
	clear();
}

void DefaultManagment::update(double deltaT)
{
	List<DefaultManaged *>::Iterator it;
	
	it = activeList.begin();
	while (it != activeList.end())
	{
		(*it)->update(deltaT);
		++it;
	}
}

void DefaultManagment::notify(DefaultManagedMessage &message)
{
	List<DefaultManaged *>::Iterator it;
	
	// 1 - delete
	if (message.toDelete)
	{
		if (message.managed->isActive())
		{
			it = findByName (message.managed->getName(), activeList);
			assert("Couldn't delete StdManaged* ; must be in activeList!" && it != activeList.end());
			activeList.erase(it);	// only delete reference! (the objects destructor was called)
		}
		else
		{
			it = findByName (message.managed->getName(), inactiveList);
			assert("Couldn't delete StdManaged* ; must be in inactiveList!" && it != inactiveList.end());
			inactiveList.erase(it);	// only delete reference! (the objects destructor was called)
		}
	}
	
	// 2 - activate
	else if (message.managed->isActive())
	{
		it = findByName (message.managed->getName(), inactiveList);
		assert("Couldn't activate StdManaged* ; must be in inactiveList!" && it != inactiveList.end());
		List<DefaultManaged *>::Iterator begin(activeList);
		activeList.splice(begin, inactiveList, it);
	}
	
	// 3 - deactivate
	else
	{
		it = findByName (message.managed->getName(), activeList);
		assert("Couldn't activate StdManaged* ; must be in activeList!" && it != activeList.end());
		List<DefaultManaged *>::Iterator begin(inactiveList);
		inactiveList.splice(begin, activeList, it);
	}
}

void DefaultManagment::addManaged(DefaultManaged *managed)
{
	if (managed->isActive())
	{
		activeList.push_front(managed);
		managed->iterator = activeList.iterator();
	}
	else
	{
		inactiveList.push_front(managed);
		managed->iterator = inactiveList.iterator();
	}
}

DefaultManaged* DefaultManagment::getManaged(const string &name) const
{
	List<DefaultManaged *>::Const_Iterator it;
	
	if ((it = findByName(name, activeList)) != activeList.end())
		return *it;
	else if ((it = findByName(name, inactiveList)) != inactiveList.end())
		return *it;
	else
		return NULL;
}

void DefaultManagment::removeManaged(const string &name)
{
	List<DefaultManaged *>::Iterator it;
	
	if ((it = findByName(name, activeList)) != activeList.end())
	{
		// delete object
		(*it)->detach(this);
		delete *it;
		
		// delete pointer
		activeList.erase(it);
	}
	else if ((it = findByName(name, inactiveList)) != inactiveList.end())
	{
		// delete object
		(*it)->detach(this);
		delete *it;
		
		// delete pointer 
		inactiveList.erase(it);
	}
}

List<DefaultManaged*>::Const_Iterator DefaultManagment::findByName(const string &name, const List<DefaultManaged*> &inList) const
{
	List<DefaultManaged*>::Const_Iterator it (inList);
	while (it != inList.end())
	{
		if ((*it)->getName() == name)
			break;
		++it;
	}
	return it;
}

void DefaultManagment::getManagedNames(JavaStyleContainer<std::string> *names) const
{
	// return active and inactive managed names with iterator
	SmartIterator<DefaultManaged*> it;
	
	it = activeList.iterator();
	while (it.hasNext())
		names->add(it.next()->getName());
		
	it = inactiveList.iterator();
	while (it.hasNext())
		names->add(it.next()->getName());
}

void DefaultManagment::getAllManaged(StringList<DefaultManaged *> &stringList) const
{
	// return active and inactive pointers to managed with iterator
	SmartIterator<DefaultManaged*> it;
	it = activeList.iterator();
	while (it.hasNext())
	{
		stringList.push_back(it.current(), it.current()->getName());
		it.next();
	}
	it = inactiveList.iterator();
	while (it.hasNext())
	{
		stringList.push_back(it.current(), it.current()->getName());
		it.next();
	}
}

List<DefaultManaged*>::Iterator DefaultManagment::findByName(const string &name, List<DefaultManaged*> &inList)
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

void DefaultManagment::clear()
{
	this->blockEvents(true);
	
	List<DefaultManaged *>::Iterator it;
	
	// clear active list
	it = activeList.begin();
	while (it != activeList.end())
	{
		delete *it;
		++it;
	}
	activeList.clear();
	
	// clear inactive list
	it = inactiveList.begin();
	while (it != inactiveList.end())
	{
		delete *it;
		++it;
	}
	inactiveList.clear();
	
	this->blockEvents(false);
}

void DefaultManagment::outDebug() const
{
	List <DefaultManaged *>::Const_Iterator itActiv (activeList);
	List <DefaultManaged *>::Const_Iterator itInact (inactiveList);
	while (itActiv.hasNext())
		out << " (activ)    " << itActiv.next()->getName(); // << endl;
	while (itInact.hasNext())
		out << " (inactiv)  " << itInact.next()->getName(); // << endl;
}


} // util
} // base
} // vs
