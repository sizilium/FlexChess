/*
  Author: Marc-Stefan Cassola
  Startdate: 13.04.05 20:47
  Description: Object of basic model loaded from a file
*/

#ifndef VSGL_FILE_MODEL_HEADER
#define VSGL_FILE_MODEL_HEADER

#include <gl/gl.h>
#include "VsglGeometry.h"

class VsglFileModel : public VsglGeometry
{
protected:
	GLuint uiDisplayLists;
	GLuint *uiaTextureObjects;
	GLint iObjectNumber;
	GLint iTextureNumber;
	
	char *caFilename;
	
public:
	VsglFileModel(const char *cafilename);
	~VsglFileModel();
	
	void draw();
};

#endif
