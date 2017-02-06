#include <vs/managed/gui/AbstractGuiFactory.h>
#include <vs/base/interfaces/AbstractManaged.h>

namespace vs
{
namespace managed
{
namespace gui
{
using namespace std;
using namespace base::interfaces;

AbstractGuiFactory::~AbstractGuiFactory()
{
	this->manager = NULL;
}

void AbstractGuiFactory::addManaged(AbstractManaged *managed)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addManaged(managed);
}

const string AbstractGuiFactory::getNamespace() const
{
	return "gui";
}

} // gui
} // managed
} // vs
