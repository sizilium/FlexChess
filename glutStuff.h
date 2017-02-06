#ifndef GLUTSTUFF_H_
#define GLUTSTUFF_H_

// includes
#include <gl/openglut.h>
#include <gl/gl.h>

#define MIN_CAM_DISTANCE	5
#define MAX_CAM_DISTANCE	40

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...
 */
void glutMouse(int button, int state, int x, int y);

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...
 */
void glutMouseWheel(int wheel, int direction, int x, int y);

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...
 */
void glutPassiveMotion(int x, int y);

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...
 */
void glutMotion(int x, int y);

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...
 */
void glutKey(unsigned char key, int x, int y);

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...\n
 * 
 * The function regularly calls the interface draw method to draw the gui to opengl context.
 */
void glutDisplay();

/**
 * This is a glut function (open gl utility toolkit) for graphical stuff. Don't care about it
 * or change anything...
 */
void glutResize(int width, int height);



#endif /*GLUTSTUFF_H_*/
