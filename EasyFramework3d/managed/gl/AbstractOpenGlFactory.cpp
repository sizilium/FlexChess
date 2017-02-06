#include <vs/managed/gl/AbstractOpenGlFactory.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/core/gl/Camera.h>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace core::gl;
using namespace base::util;


AbstractOpenGlFactory::~AbstractOpenGlFactory()
{
	this->manager = NULL;
}

void AbstractOpenGlFactory::addManaged(DefaultManaged *managed)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addManaged(managed);
}

void AbstractOpenGlFactory::addCamera(Camera *cam)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->addCamera(cam);
}

void AbstractOpenGlFactory::setOpenGlSettings(OpenGlSettings *settings)
{
	assert("Factory can't add managed. There is no current manager!" && manager != NULL);
	manager->setOpenGlSettings(settings);
}

OpenGlManager* AbstractOpenGlFactory::getCurrentManager()
{
	return manager;
}

} // gl
} // managed
} // vs
