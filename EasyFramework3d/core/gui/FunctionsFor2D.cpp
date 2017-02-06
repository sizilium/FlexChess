#include <vs/core/gui/FunctionsFor2D.h>
#include <vs/core/gui/Widget.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

namespace vs
{
namespace core
{
namespace gui
{

void setOrthographicProjection(int x, int y, int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(x, x+width, y, y+height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void resetPerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

bool hitWidget(const Widget *widget, int x, int y, int &localX, int &localY)
{
	assert(widget);		// maybe the widget in the gui manager is toggled to inactive list during event signalling ...
	
	// get widget dimensions
	float widgetPosX, widgetPosY, widgetWidth, widgetHeight;
	widget->getPosition(widgetPosX, widgetPosY);
	widget->getSize(widgetWidth, widgetHeight);
	
	// calc local
	localX = x - (int)widgetPosX;
	localY = y - (int)widgetPosY;
	
	// check
	if (localX >= 0 && localX <= widgetWidth && localY >= 0 && localY <= widgetHeight)
		return true;
	else
		return false;
}

} // gui
} // core
} // vs
