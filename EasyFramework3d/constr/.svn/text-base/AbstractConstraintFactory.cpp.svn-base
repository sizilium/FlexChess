#include <vs/constr/AbstractConstraintFactory.h>
#include <vs/base/util/DefaultManaged.h>

namespace vs
{
namespace constr
{
using namespace std;

AbstractConstraintFactory::~AbstractConstraintFactory()
{
	this->manager = NULL;
}

const string AbstractConstraintFactory::getNamespace() const
{
	return "constr";
}

void AbstractConstraintFactory::addManaged(base::util::DefaultManaged *managed)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addManaged(managed);
}


} // constr
} // vs
