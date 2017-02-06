#ifndef MAIN_CPP
#define MAIN_CPP

#include "glutStuff.h"
#include "Menues/Interface.h"
#include <gl/openglut.h>
#include <gl/gl.h>
#include <iostream>
#include <time.h>

#include <vs/Context.h>
#include <vs/managed/gl/OpenGlFactory.h>
#include <vs/managed/gui/GuiManager.h>
#include <vs/managed/gl/model/ModelManager.h>
#include <vs/core/gl/Grid.h>
#include <vs/core/gl/Light.h>
#include <vs/core/gl/ObserverCamera.h>
#include <vs/base/util/Exception.h>
#include <vs/base/math/DoubleVector.h>
#include "Game.h"
#include <vs/managed/gl/model/ModelFactory.h>
using namespace vs::managed::gl::model;

#define LOOP_TIME	10

using namespace std;
using namespace vs;
using namespace vs::core::gl;
using namespace vs::managed::gl;
using namespace vs::managed::gui;
using namespace vs::base::math;
using namespace vs::base::util;

// global
Interface *interface = NULL;
Context *context = NULL;


void setupOpenGl()
{
	OpenGlFactory factory;
	Light *light = factory.createLight("light 1", 90, -90, 100);
	light->setAmbient(Color(0.1, 0.1, 0.1));
	light->setDiffuse(Color(0.8, 0.8, 0.8));
	light->setSpecular(Color(1, 1, 1, 1));
	
	OpenGlSettings *settings = factory.createStdOpenGlSettings();
	settings->setLineWidth(2);
//	settings->disableCullFace();
	settings->applyToOpenGl();
	
	glutPostRedisplay();
}


void setupEasyFramework()
{
	// EasyFramework stuff
	context = Context::getCurrentContext();
	
	OpenGlFactory factory;
	
    ObserverCamera *cam = factory.createObserverCamera("ObserverCam");
    cam->setLookAt(DoubleVector(3.5, 3.5, 0));
    cam->setDistance(15);
    
//	Grid *grid = factory.createGrid("Grid_1");
//    grid->enableAxis(true);
//    grid->setCoords(DoubleVector(3.5, 3.5, 0.1));
//    Plane *plane = new Plane;
//    plane->setStep(1);
//    plane->setMax(10);
//    plane->setMin(-10);
//    grid->setPlaneXy(plane);
    
    GuiManager *guiManager = context->getGuiManager();
    guiManager->setCoordinateMode(GuiManager::relativeCoordinates);
    guiManager->setReferenceResolution(0, 0, 1500, 1000);

//    context->enableGuiManager(false);

    context->getModelManager()->enableUntextured();
    context->getModelManager()->enableTextured();
//    context->getModelManager()->disableUntextured();
//    context->getModelManager()->disableTextured();

}

void setupGame()
{
    // start game in menu
	interface = new Interface();
}

/**
 * This is the main loop. It runs the game with the run method, checks the winner and cals
 * the glutDisplay function.\n
 * The loop will leaved if a quit button was pressed or the gui exit button was pressed.
 */
void loop(int)
{
	if (interface->getGame())
	{
		if (!interface->getGame()->run())
			interface->showWinner();
	}

	if (interface->checkExit())
	{
	    glutLeaveMainLoop();
	    return;
	}

    glutPostRedisplay();
	glutMainLoopEvent();
	glutTimerFunc(LOOP_TIME, loop, 0);
}

int main(int argc, char **argv)
{
	// glut stuff
    glutInitWindowSize(1024,768);
    glutInitWindowPosition(40,40);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("FlexChess");
    glutReshapeFunc(glutResize);
    glutDisplayFunc(glutDisplay);
    glutKeyboardFunc(glutKey);
    glutMouseFunc(glutMouse);
    glutMouseWheelFunc(glutMouseWheel);
    glutPassiveMotionFunc(glutPassiveMotion);
    glutMotionFunc(glutMotion);
    //glutIdleFunc(glutDisplay);

    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
//    glutGameModeString("1024x768:32");
//    if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE))
//        {
//            glutEnterGameMode();
//        }
	
    // EasyFramework3d stuff
    setupEasyFramework();

    // opengl stuff
    setupOpenGl();
    
    // FlexChess init & start
    setupGame();
   
    
    glutTimerFunc(LOOP_TIME, loop, 0);
    glutMainLoop();
    delete interface;
}

#endif
