/*
  Author: Marc-Stefan Cassola
  Startdate: 13.04.05 20:51
  Description: Implementation of VsglFileModel.h
*/

#include "VsglFileModel.h"
#include <cstring>
#include "vsglm.h"

using namespace std;

VsglFileModel::VsglFileModel(const char *caFilename)
{
	this->caFilename = new char[strlen(caFilename)];
	strcpy(this->caFilename, caFilename);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	
	vsglInitModel(caFilename);
	
	iTextureNumber = vsglGetTexNum();
	uiaTextureObjects = new unsigned int[iTextureNumber];
	glGenTextures(iTextureNumber, uiaTextureObjects);
	
	iObjectNumber = vsglGetObjNum();
	uiDisplayLists = glGenLists(iObjectNumber);
	
	vsglBindModel(uiDisplayLists, uiaTextureObjects);
	
	glDisable(GL_TEXTURE_2D);
}

VsglFileModel::~VsglFileModel()
{
	glDeleteLists(uiDisplayLists, iObjectNumber);	
	glDeleteTextures(iTextureNumber, uiaTextureObjects);
}

void VsglFileModel::draw()
{
	for (int i = 0; i < iObjectNumber; i++)
		glCallList(uiDisplayLists + i);
}
