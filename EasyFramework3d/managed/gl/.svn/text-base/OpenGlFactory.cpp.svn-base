#include <vs/managed/gl/OpenGlFactory.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <vs/core/gl/Camera.h>
#include <vs/core/gl/ObserverCamera.h>
#include <vs/core/gl/Grid.h>
#include <vs/core/gl/Light.h>
#include <vs/managed/gl/OpenGlXmlEntries.h>
#include <vs/base/math/DoubleVector.h>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace core::gl;
using namespace base::math;

OpenGlFactory::OpenGlFactory()
{
	
}

OpenGlFactory::~OpenGlFactory()
{
}

Camera* OpenGlFactory::createCamera(const string &name)
{
	Camera *cam = new Camera;
	cam->setName(name);
	
	// add to OpenglManager
	addCamera(cam);
	
	// activate cam if there is no other cam
	if (getCurrentManager() && !getCurrentManager()->isActivCamera())
		cam->activate();
	
	// TODO xml entry for cam
	
	return cam;
}

ObserverCamera* OpenGlFactory::createObserverCamera(const string &name)
{
	ObserverCamera *cam = new ObserverCamera;
	cam->setName(name);
	
	// add to OpenglManager
	addCamera(cam);
	
	// activate cam if there is no other cam
	if (getCurrentManager() && !getCurrentManager()->isActivCamera())
		cam->activate();
	
	// TODO xml entry for observer cam
	
	return cam;
}

Light* OpenGlFactory::createLight(const string &name, double x, double y, double z)
{
	Light *light = new Light;
	light->setName(name);
	light->setCoords(DoubleVector(x, y, z));
	//light->deactivate();
	
	// add to OpenGlManager
	addManaged(light);

	// add xml entry to XmlManager
	addXmlEntry(new gl::LightXmlEntry(name, light));
	
	// one update to set up the position
	light->update();
	
	return light;
}

Grid* OpenGlFactory::createGrid(const string &name)
{
	Grid *grid = new Grid;
	grid->setName(name);
	
	// add to OpenGlManager
	addManaged(grid);
	
	// add xml entry to XmlManager
	addXmlEntry(new gl::GridXmlEntry(name, grid));
	
	return grid;
}

OpenGlSettings* OpenGlFactory::createStdOpenGlSettings()
{
	// create new setting
	OpenGlSettings *settings = new OpenGlSettings;

	// set to standard material
	settings->enableColorMaterial();
	settings->addColorMaterial(GL_FRONT, GL_AMBIENT, Color(0.7f, 0.7f, 0.7f, 1.0f));
	settings->addColorMaterial(GL_FRONT, GL_DIFFUSE, Color(1.0f, 1.0f, 1.0f, 1.0f));
//	settings->addColorMaterial(GL_FRONT, GL_SPECULAR, Color(0.01f, 0.01f, 0.01f, 1.0f));

	// set to standard flags
	settings->setShadeModelSmooth();
	settings->enableLighting();
	settings->enableTexture();
	settings->setFrontFaceCW();
	settings->enableNormalize();
	settings->enableDepthTest();
	settings->enableCullFace();
	
	// add settings to the OpenGlManager
	setOpenGlSettings(settings);
	
	// add xml entry to XmlManager
	addXmlEntry(new gl::OpenGlSettingsXmlEntry("openGlSettings", settings));
	
	return settings;
}

} // gl
} // managed
} // vs
