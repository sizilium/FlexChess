#ifndef VSGL_MODEL_HEADER
#define VSGL_MODEL_HEADER

#include <list>
#include <gl/gl.h>

using namespace std;

void vsglInitModel(const char *cpFilename);		// load model data into memory. call this first

int vsglGetTexNum();							// calc number of textures to be generated
list<string> &vsglGetTexNames();				// get list of all texture names occuring in the model
int vsglGetObjNum();							// get number of objects (=display lists) of the model

												// finally bind the drawing of the model to the
												// display lists and the texture objects
												// removes also the current model from memory
void vsglBindModel(GLuint &uiDisplayLists, GLuint *uipTextureObjs);

#endif
