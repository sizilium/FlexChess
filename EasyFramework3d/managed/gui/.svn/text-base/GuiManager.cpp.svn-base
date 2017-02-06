#include <vs/managed/gui/GuiManager.h>
#include <vs/managed/gui/AbstractGuiFactory.h>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/core/gui/FunctionsFor2D.h>
#include <vs/core/gui/Widget.hpp>

#include <GL/gl.h>

namespace vs
{
namespace managed
{
namespace gui
{
using namespace vs::base::interfaces;
using namespace vs::base::util;
using namespace vs::base::cont;
using namespace vs::core::gui;

GuiManager::GuiManager()
:viewportX(0), viewportY(0), viewportWidth(1024), viewportHeight(768), 
refViewportX(0), refViewportY(0), refViewportWidth(1024), refViewportHeight(768), 
coordinateMode(absoluteCoordinates), oldX(0), oldY(0), selectedWidget(NULL), managment(this)
{
}

GuiManager::~GuiManager()
{
	clear();
}

void GuiManager::setCoordinateMode(enum GuiCoordinateMode mode)
{
	coordinateMode = mode;
}

void GuiManager::setReferenceResolution(int x, int y, int width, int height)
{
	this->refViewportX = x;
	this->refViewportY = y;
	this->refViewportWidth = width;
	this->refViewportHeight = height;
}

GuiManager::GuiCoordinateMode GuiManager::getCoordinateMode() const
{
	return coordinateMode;
}

void GuiManager::injectViewport(int x, int y, int width, int height)
{
	assert ("Wrong viewport dimensions injected!" && x >= 0 && y >= 0 && width >= 0 && height >= 0);
	this->viewportX = x;
	this->viewportY = y;
	this->viewportWidth = width;
	this->viewportHeight = height;
}

void GuiManager::injectMouseHover(int x, int y)
{
	// important for relative coordinate mode (scales the x and y values)
	checkCoordinateMode(x, y);
	
	// declarations
	bool hit, oldHit;
	int localX, localY;
	Widget *widget = NULL;
	List<DefaultManaged *>::Iterator it;

	// check all active widgets
	it = managment.activeList.begin();
	while (it != managment.activeList.end())
	{
		// cast widget for one time
		widget = dynamic_cast<Widget*> (*it);
		
		// check hit
		if (hit = hitWidget(widget, x, y, localX, localY))
		{
			// emit hover event
			widget->mouseHoverEvent(localX, localY);
			// check entered or leaved event
			oldHit = hitWidget(widget, oldX, oldY, localX, localY);	// check old hit
			if (hit && !oldHit)
				widget->mouseEnteredEvent();
			else if (!hit && oldHit)
				widget->mouseLeavedEvent();
			break;
		}
		
		// check entered or leaved event
		oldHit = hitWidget(widget, oldX, oldY, localX, localY);	// check old hit
		if (hit && !oldHit)
		{
			widget->mouseEnteredEvent();
			break;
		}
		else if (!hit && oldHit)
		{
			widget->mouseLeavedEvent();
			break;
		}
		
		++it;
	}
	oldX = x;
	oldY = y;
}

void GuiManager::injectMouseLeftClick(int x, int y, bool pressed)
{
	// important for relative coordinate mode (scales the x and y values)
	checkCoordinateMode(x, y);
	
	int localX, localY;
	List<DefaultManaged *>::Iterator it;

	// check all active widgets
	it = managment.activeList.begin();
	while (it != managment.activeList.end())
	{
		// check hit
		if (hitWidget( dynamic_cast<Widget*> (*it), x, y, localX, localY))
		{
			// emit click event
			(dynamic_cast<Widget*> (*it) )->mouseLeftClickEvent(localX, localY, pressed);
			break;
		}
		++it;
	}
}

void GuiManager::injectMouseRightClick(int x, int y, bool pressed)
{
	// important for relative coordinate mode (scales the x and y values)
	checkCoordinateMode(x, y);
	
	int localX, localY;
	List<DefaultManaged *>::Iterator it;

	// check all active widgets
	it = managment.activeList.begin();
	while (it != managment.activeList.end())
	{
		// check hit
		if (hitWidget( dynamic_cast<Widget*> (*it), x, y, localX, localY))
		{
			// emit click event
			(dynamic_cast<Widget*> (*it) )->mouseRightClickEvent(localX, localY, pressed);
			break;
		}
		++it;
	}
}

void GuiManager::injectMouseMiddleClick(int x, int y, bool pressed)
{
	// important for relative coordinate mode (scales the x and y values, bool pressed)
	checkCoordinateMode(x, y);
	
	int localX, localY;
	List<DefaultManaged *>::Iterator it;

	// check all active widgets
	it = managment.activeList.begin();
	while (it != managment.activeList.end())
	{
		// check hit
		if (hitWidget( dynamic_cast<Widget*> (*it), x, y, localX, localY))
		{
			// emit click event
			(dynamic_cast<Widget*> (*it) )->mouseMiddleClickEvent(localX, localY, pressed);
			break;
		}
		++it;
	}
}

void GuiManager::injectMouseWheel(char ticks)
{
	if (selectedWidget)
		selectedWidget->mouseWheelEvent(ticks);
}

void GuiManager::injectKeyPress(unsigned char key)
{
	if (selectedWidget)
		selectedWidget->keyPressEvent(key);
}

void GuiManager::injectKeyRelease(unsigned char key)
{
	if (selectedWidget)
		selectedWidget->keyReleaseEvent(key);
}

void GuiManager::update(double deltaT)
{
	// prepare & save opengl states
	glPushMatrix();
	glPushAttrib(GL_LIGHTING);
	glPushAttrib(GL_BLEND);
	glPushAttrib(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	
	// prepare projection for 2d
	if (coordinateMode == absoluteCoordinates)
		setOrthographicProjection(viewportX, viewportY, viewportWidth, viewportHeight);
	else if (coordinateMode == relativeCoordinates)
		setOrthographicProjection(refViewportX, refViewportY, refViewportWidth, refViewportHeight);
	else
		assert("CoordinateMode not implemented in GuiManager!" && false);

	// update active widgets
	managment.update(deltaT);

	// restore opengl projection & states
	resetPerspectiveProjection();
	glPopAttrib();
	glPopAttrib();
	glPopAttrib();
	glPopMatrix();
}

void GuiManager::getManagedNames(JavaStyleContainer<std::string> * names) const
{
	managment.getManagedNames(names);
}

void GuiManager::addManaged(AbstractManaged *managed)
{
	DefaultManaged *cast = dynamic_cast<DefaultManaged *>(managed);
	managment.addManaged(cast);
	cast->attach(&managment);
}

AbstractManaged* GuiManager::getManaged(const std::string &name) const
{
	return managment.getManaged(name);
}
		
void GuiManager::removeManaged(const std::string &name)
{
	managment.removeManaged(name);
}

void GuiManager::clear()
{
	managment.clear();
}

void GuiManager::outDebug() const
{
	managment.outDebug();
}

void GuiManager::checkCoordinateMode(int &x, int &y)
{
	if (coordinateMode == relativeCoordinates)
	{
		// first multiply then divide, else the result is always 0 (because int)
		x = (x * refViewportWidth) / viewportWidth;
		y = (y * refViewportHeight) / viewportHeight;
	}
}

void GuiManager::checkMouseEntered(Widget *widget)
{
	int lx, ly;
	if (hitWidget(widget, oldX, oldY, lx, ly))
		widget->mouseEnteredEvent();
}


// ------------------------------------------------------------------------------------------


GuiManagment::GuiManagment(GuiManager *guiManager)
{
	assert (guiManager != NULL);
	this->guiManager = guiManager;
}


void GuiManagment::update(double deltaT)
{
	List<DefaultManaged *>::Iterator it;
	
	it = activeList.begin();
	while (it != activeList.end())
	{
		glLoadIdentity();
		(*it++)->update(deltaT);
	}
}


void GuiManagment::notify(DefaultManagedMessage &message)
{
	// call the DefaultManagment code
	DefaultManagment::notify(message);

	// when widget activated, check for mouseEnteredEvent !
	if (message.managed->isActive())
	{
		Widget *widget = dynamic_cast<Widget*> (message.managed);
		guiManager->checkMouseEntered(widget);	// GuiManagment can call private method (friend)
	}
}


} // gui
} // managed
} // vs
