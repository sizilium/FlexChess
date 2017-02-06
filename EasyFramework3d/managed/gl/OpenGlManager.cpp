#include <vs/managed/gl/OpenGlManager.h>
#include <vs/core/gl/OpenGlSettings.h>
#include <vs/core/gl/Light.h>
#include <vs/base/cont/StringList.hpp>
#include <vs/base/cont/SmartIterator.hpp>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/IOStream.h>
#include <algorithm>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace std;
using namespace core::gl;
using namespace base::util;
using namespace base::cont;
using namespace base::interfaces;

OpenGlManager::OpenGlManager()
{
	settings = NULL;
	currentCam = NULL;
}

OpenGlManager::~OpenGlManager()
{
	delete settings;
	delete currentCam;
	settings = NULL;
	currentCam = NULL;
}

void OpenGlManager::getManagedNames(JavaStyleContainer<string> *names) const
{
	List<Camera *>::Const_Iterator it (cameras);
	
	// stdmanagment
	managment.getManagedNames(names);
	
	// cameras
	while (it.hasNext())
		names->add(it.next()->getName());
}

AbstractManaged* OpenGlManager::getManaged(const string &name) const
{
	List<Camera *>::Const_Iterator it (cameras);
	
	// search in managment
	AbstractManaged *managed = managment.getManaged(name);
	
	// search in camera list
	if (managed == NULL)
	{
		while (it.hasNext())
		{
			if (it.current()->getName() == name)
			{
				managed = it.current();
				break;
			}
			it.next();
		}
	}
	// can be NULL
	return managed;
}

Camera* OpenGlManager::getCamera(const string &name) const
{
	List<Camera*>::Const_Iterator it (cameras);
	while (it != cameras.end())
	{
		if ((*it)->getName() == name)
			break;
		++it;
	}
	if (it != cameras.end())
		return *it;
	else
		return NULL;
}

Camera* OpenGlManager::getCurrentCamera() const
{
	return currentCam;
}

bool OpenGlManager::isActivCamera() const
{
	if (currentCam)
		return true;
	else
		return false;
}

void OpenGlManager::removeManaged(const string &name)
{
	managment.removeManaged(name);
}

void OpenGlManager::removeCamera(const string &name)
{
	this->blockEvents(true);
	
	List<Camera*>::Iterator it (cameras);
	while (it != cameras.end())
	{
		if ((*it)->getName() == name)
			break;
		++it;
	}
	if (it != cameras.end())
	{
		// delete camera
		delete *it;
		
		// delete pointer
		cameras.erase(it);
	}
	
	this->blockEvents(false);
}

void OpenGlManager::update(double deltaT)
{
	// first apply the cam
	if (currentCam)
		currentCam->update(deltaT);
	
	// then the other open gl stuff
	managment.update(deltaT);
}

void OpenGlManager::injectViewport(int x, int y, int width, int height)
{
	List<Camera*>::Iterator it (cameras);
	while (it != cameras.end())
		(*it++)->setAspect(width, height);
}

void OpenGlManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *defaultManaged = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(defaultManaged);
	defaultManaged->attach(&managment);
}

void OpenGlManager::addCamera(Camera *cam)
{
	cameras.push_back(cam);
	
	// all cam events will sent to this class
	cam->attach(this);
}

// cam event handler
void OpenGlManager::notify(CameraMessage &message)
{
	// ckeck if the cam will be deleted
	if (message.toDelete)
		cameras.remove(message.cam);	// in this case delete pointer only! (cameras destructor was called)
	// check if there is a current cam anymore when a cam is deactivated
	else if (message.activateState == false && currentCam == message.cam)
		currentCam = NULL;
	// when a cam is activated it will be the current cam automatically
	else if (message.activateState == true)
		currentCam = message.cam;
}

void OpenGlManager::setOpenGlSettings(OpenGlSettings *settings)
{
	delete this->settings;
	this->settings = settings;
}

OpenGlSettings* OpenGlManager::getOpenGlSettings() const
{
	return this->settings;
}

list<string> OpenGlManager::getLightNames() const
{
	StringList<DefaultManaged*> myList;
	StringList<DefaultManaged*>::Iterator it;
	list<string> retVal;
	
	managment.getAllManaged(myList);
	it = myList.begin();
	while (it.hasNext())
	{
		if (dynamic_cast<Light*>(*it))
		{
			retVal.push_back(it.name());
		}
		it.next();
	}
	
	return retVal;
}

void OpenGlManager::clear()
{
	delete settings;
	settings = NULL;

	List<Camera *>::Iterator it (cameras);
	//while (it.hasNext())
	//	delete it.next();
	cameras.clear();
	// currentCam deleted too (from cameras)
	currentCam = NULL;
	
	managment.clear();
}

void OpenGlManager::outDebug() const
{
	managment.outDebug();
}
} // gl
} // managed
} // vs
