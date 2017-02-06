// Test for vsglm.h
// Written by Maccesch
// Last modificaion: 02.03.2005

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "vsglm.h"
#include "vsgli.h"
#include <gl/openglut.h>
#include "VsglFileModel.h"

using namespace std;

float angle = 0.0f;
GLuint uiTexObjects[10];
GLuint uiDisplayLists;
int iObjNum;
VsglFileModel *model;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	glRotatef(angle, 0.0f, 0.1f, 0.0f);
	glRotatef(270, 1.0f, 0.0f, 0.0f);	
	
	model->draw();
	
	glPopMatrix();
	
	glutSwapBuffers();
	
	angle += 0.5;
}

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,3.0,15.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("VSGLM Test");
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat diffuseLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glEnable(GL_LIGHT0);
	
	GLfloat lightPos[] = { -50.0f, 50.0f, 100.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	
	model = new VsglFileModel("test.vsm");

	glEnable(GL_TEXTURE_2D);
	
	glutMainLoop();
	
	delete model;
}
