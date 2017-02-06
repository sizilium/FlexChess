#include <vs/core/gl/Grid.h>

namespace vs
{
namespace core
{
namespace gl
{


Grid::Grid()
{
	xyPlane = NULL;
	xzPlane = NULL;
	yzPlane = NULL;
	
	axis = false;
	axisLength = AXIS_DEFAULT_LENGTH
	
	isXyPlane = false;
	isXzPlane = false;
	isYzPlane = false;
	
	xyColor = Color(0.5f, 0.5f, 0.5f, 1.0f);
	xzColor = Color(0.5f, 0.5f, 0.5f, 1.0f);
	yzColor = Color(0.5f, 0.5f, 0.5f, 1.0f);
}


Grid::~Grid()
{
	delete xyPlane;
	delete xzPlane;
	delete yzPlane;
}

bool Grid::getPlaneXy(Plane *&plane)
{
	if (isXyPlane)
	{
		plane = xyPlane;
		return true;
	}
	else
	{
		plane = NULL;
		return false;
	}
}

bool Grid::getPlaneXz(Plane *&plane)
{
	if (isXzPlane)
	{
		plane = xzPlane;
		return true;
	}
	else
	{
		plane = NULL;
		return false;
	}
}

bool Grid::getPlaneYz(Plane *&plane)
{
	if (isYzPlane)
	{
		plane = yzPlane;
		return true;
	}
	else
	{
		plane = NULL;
		return false;
	}
}

void Grid::update(double /*time*/)
{
	glPushMatrix();
	glPushAttrib(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);
	
	glTranslated(getCoords().x(), getCoords().y(), getCoords().z());
	// TODO Rotation with euler
	
	if (isXyPlane)
	{
		glPushMatrix();
		glColor4f(xyColor[0], xyColor[1], xyColor[2], xyColor[3]);
		//glRotated(90, 1, 0, 0);
		xyPlane->draw(axis);
		glPopMatrix();
	}
	
	if (isXzPlane)
	{
		glPushMatrix();
		glColor4f(xzColor[0], xzColor[1], xzColor[2], xzColor[3]);
		glRotated(-90, 1, 0, 0);
		xzPlane->draw(axis);
		glPopMatrix();
	}
	
	if (isYzPlane)
	{
		glPushMatrix();
		glColor4f(yzColor[0], yzColor[1], yzColor[2], yzColor[3]);
		glRotated(-90, 0, 1, 0);
		yzPlane->draw(axis);
		glPopMatrix();
	}
	
	if (axis)
	{
		glBegin(GL_LINES);
		
		// Red - x
		glColor3f(2, 0, 0);
		glVertex3d(-axisLength, 0, 0);
		glVertex3d(axisLength, 0, 0);
		
		// Green - y
		glColor3f(0, 2, 0);
		glVertex3d(0, -axisLength, 0);
		glVertex3d(0, axisLength, 0);
		
		// Blue - z
		glColor3f(0, 0, 2);
		glVertex3d(0, 0, -axisLength);
		glVertex3d(0, 0, axisLength);
		
		glEnd();
	}
	
	glPopAttrib();
	glPopMatrix();
}


Plane::Plane()
{
	min = -10;
	max = 10;
	step = 1;
}


void Plane::draw(bool withoutMidLine)
{
	double start = 0;

	glBegin(GL_LINES);
	
	if (withoutMidLine)
		start = step;
	for (double x = start; x < max; x += step)
	{
		glVertex3d(x, min, 0);
		glVertex3d(x, max, 0);
		glVertex3d(min, x, 0);
		glVertex3d(max, x, 0);
	}
	
	if (withoutMidLine)
		start = - step;
	for (double x = start; x > min; x -= step)
	{
		glVertex3d(x, min, 0);
		glVertex3d(x, max, 0);
		glVertex3d(min, x, 0);
		glVertex3d(max, x, 0);
	}
	
	glEnd();
	
}


} // gl
} // core
} // vs
