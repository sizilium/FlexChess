#include <vs/managed/gl/AbstractAnimationFactory.h>

namespace vs
{
namespace managed
{
namespace gl
{

AbstractAnimationFactory::~AbstractAnimationFactory()
{
	this->manager = NULL;
}

void AbstractAnimationFactory::addAnimation(ModelAnimation *animation)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addManaged (animation);
}

} // gl
} // managed
} // vs
