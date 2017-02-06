#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/DefaultManagment.h>

namespace vs
{
namespace base
{
namespace util
{

DefaultManaged::DefaultManaged()
:name(""), active(true)
{}

DefaultManaged::DefaultManaged(const DefaultManaged &)
{
	// nothing
}

DefaultManaged::~DefaultManaged()
{
	// manager must delete the managed too! else there is a null pointer...
	
	DefaultManagedMessage message;
	message.managed = this;
	message.toDelete = true;
	
	// notify std managment
	notify(message);

}

DefaultManaged& DefaultManaged::operator=(const DefaultManaged &op2)
{
	// nothing
	return *this;
}

void DefaultManaged::activate()
{
	if (active)
		return;

	// first make activ
	active = true;
	
	DefaultManagedMessage message;
	message.managed = this;
	
	// then notify
	notify(message);
}

void DefaultManaged::deactivate()
{
	if (!active)
		return;

	// first make inactiv
	active = false;
	
	DefaultManagedMessage message;
	message.managed = this;

	// then notify
	notify(message);
}

std::string DefaultManaged::getName() const				
{
	return name;
}

void DefaultManaged::setName(const std::string &name)	
{
	this->name = name;
}

bool DefaultManaged::isActive() const		
{
	return active;
}

} // util
} // base
} // vs
