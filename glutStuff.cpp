#include "glutStuff.h"
#include "Menues/Interface.h"
#include "Game.h"

#include <vs/core/gl/Grid.h>
#include <vs/Context.h>
#include <vs/core/gl/ObserverCamera.h>
#include <vs/base/util/Exception.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <vs/base/util/Time.h>

#include <iostream>
#include <vs/base/math/DoubleVector.h>

using namespace std;

using namespace vs;
using namespace vs::core::gl;
using namespace vs::managed::gl;
using namespace vs::managed::gui;
using namespace vs::base::math;
using namespace vs::base::util;


// global
bool motion = false;
extern Context *context;
extern Interface *interface;


void glutMouse(int button, int state, int x, int y)
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == 0)
			context->injectMouseLeftClick(x, viewport[3] - y, true);
		else
			context->injectMouseLeftClick(x, viewport[3] - y, false);
	}
	if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON || 
		button == GLUT_MIDDLE_BUTTON && !state)
		motion = false;
	
	glutPostRedisplay();
}


void glutMouseWheel(int wheel, int direction, int x, int y)
{
	if (direction < 0)
	{
		assert(context);
		ObserverCamera *cam = dynamic_cast<ObserverCamera *> (context->getOpenGlManager()->getCurrentCamera());
		if (cam)
		{
			if (cam->getDistance() < MAX_CAM_DISTANCE)
				cam->addDistance(1);
			else
				cam->setDistance(MAX_CAM_DISTANCE);
		}
		context->injectMouseWheel(3);
	}
	if (direction > 0)
	{
		assert(context);
		ObserverCamera *cam = dynamic_cast<ObserverCamera *> (context->getOpenGlManager()->getCurrentCamera());
		if (cam)
		{
			if (cam->getDistance() > MIN_CAM_DISTANCE)
				cam->addDistance(-1);
			else
				cam->setDistance(MIN_CAM_DISTANCE);
		}
		context->injectMouseWheel(-3);

	}
	
	glutPostRedisplay();
}


void glutPassiveMotion(int x, int y)
{
	static char count = 0;

	count++;
	if (count == 3)
	{
		count = 0;
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT,viewport);
		
		if(context)
			context->injectMouseHover(x, viewport[3] - y);
		
	    glutPostRedisplay();
	}
}


void glutMotion(int x, int y)
{
	static int xOld = 0;
	static int yOld = 0;

	// first setup motion
	if (!motion)
	{
		xOld = x;
		yOld = y;
		motion = true;
		return;
	}

	// calc mouse distance
	int dx = xOld - x;
	int dy = yOld - y;
	
	xOld = x;
	yOld = y;
	
	// setup camera
	assert(context);
	ObserverCamera *cam = dynamic_cast<ObserverCamera *> (context->getOpenGlManager()->getCurrentCamera());
	if (cam)
	{
		cam->addAngleZ(-dx/1.5);
		cam->addAngleXY(-dy/1.5);
		if (cam->getAngleXY() < 15)
			cam->setAngleXY(15);
	}
    glutPostRedisplay();
}


void glutKey(unsigned char key, int x, int y)
{
	assert(context);
	ObserverCamera *cam = dynamic_cast<ObserverCamera*> (context->getOpenGlManager()->getCurrentCamera() );
	assert (cam);
	
	Game *game = interface->getGame();
	
	switch (key)
    {
    case 'q': 
    case 'b':
    	interface->exit();
    	glutLeaveMainLoop();
    	break;
    case 'a':
    	interface->addCursor(-1, 0);
    	break;
    case 's':
    	interface->addCursor(0, -1);
    	break;
    case 'd':
    	interface->addCursor(1, 0);
    	break;
    case 'w':
    	interface->addCursor(0, 1);
    	break;
    case 'e':
    	interface->pressCursor();
    	break;
    case '8':
    	cam->addAngleXY(15);
    	break;
    case '2':
    	cam->addAngleXY(-15);
		if (cam->getAngleXY() < 15)
			cam->setAngleXY(15);
    	break;
    case '4':
    	cam->addAngleZ(15);
    	break;
    case '6':
    	cam->addAngleZ(-15);
    	break;  	
    case '9':
    	cam->addDistance(-1);
    	break;
    case '3':
    	cam->addDistance(1);
    	break;  	
    case 'i':
    	//context->outDebug();
    	//game->coutDebugBoard();
    	//game->coutDebugFigures();
    	//game->coutDebugPlayers();
    	game->coutPoints();
    	
    	break;
    	
    default:
        break;
    }
    glutPostRedisplay();
}


void glutDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    static StopWatch timer;

	if (context != NULL)
		context->update(timer.getFrameTime());

	interface->drawCursor();

    glutSwapBuffers();
}


void glutResize(int width, int height)
{
	// Set the viewport to be the entire window
	glViewport(0, 0, width, height);
	if (context)
		context->injectViewport(0, 0, width, height);
}
