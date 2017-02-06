// Vision Snythesis Model Loading Library
// Written by Maccesch. Started on Thursday, 25.11.2004
// Last modification:  02.03.2005
// Don't worry, be happy ;-)

#include "vsglm.h"

#include <fstream>
#include <iostream>
#include "vsgli.h"

using namespace std;

struct vsglVertexData
{
	unsigned int uiVertIndex;						// Index of the vertex in vsglObjectData::faVerts
	float f3Norm[3];								// Normal vector of the vertex
	float fU;										// U-Texture-coordinate
	float fV;										// V-Texture-coordinate
};

struct vsglFaceData
{
	vsglVertexData ct3Vertices[3];					// The 3 vertices of the Face
};

struct vsglFacesData
{
	char cDrawMode;									// Draw mode postet to glBegin() when
													// drawing the faces.
													// '0' = GL_TRIANGLES
													// '1' = GL_TRIANGLE_STRIP
													// '2' = GL_TRIANGLE_FAN
    unsigned int uiFaceNum;							// Number of Faces---???
    list<vsglFaceData> lstctFaces;					// Vertexindex and -normal for every face    
};

struct vsglObjectData
{
    unsigned int uiVertNum;							// Number of vertices
    float *faVerts;                         		// Vertex-array
    float f4Color[4];								// RGBA-color of object-material
    char cTextured;									// If object ist textured = '1' else '0'
    int iTexNum;									// Number of textures of object
    list<string> lststrTexNames;  					// Filename of textures if existing
    list<vsglFacesData> lstctFaceLists;				// The faces of each list entry share
    												// the same texture. If there aren't texs,
    												// this list contains only one entry.
};

struct vsglModelData
{
    char caFormatVersion[9];                        // Version of vsm-format
    short sLod;                                     // Level of detail of this model
    unsigned int uiObjNum;							// Number of Blender-objects
    list<vsglObjectData> lstctObjects;				// List of (Blender)-objects
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
static vsglModelData *ctCurrentModel = 0;

static void vsglLoadFaces(ifstream &modelFile, vsglFacesData &ctTempFaces, bool bTextured)
{
	vsglFaceData ctTempFace;
	int i;
	for (int j = 0; j < ctTempFaces.uiFaceNum; j++)
	{
		vsglVertexData ct3TempVertex[3];
		for (i = 0; i < 3; i++)
		{
													// load index of this vertex
			modelFile.read(reinterpret_cast<char *>(&(ct3TempVertex[i].uiVertIndex)),
						   sizeof(ct3TempVertex[i].uiVertIndex));
	
													// load normal vector
			modelFile.read(reinterpret_cast<char *>(ct3TempVertex[i].f3Norm), sizeof(float[3]));
			
			if (bTextured)							// UV Coordinates only when textured
			{
													// load U-coordinate
				modelFile.read(reinterpret_cast<char *>(&(ct3TempVertex[i].fU)), sizeof(ct3TempVertex[i].fU));
		
													// load V-coordinate
				modelFile.read(reinterpret_cast<char *>(&(ct3TempVertex[i].fV)), sizeof(ct3TempVertex[i].fV));
			}
		}
		ctTempFace.ct3Vertices[0] = ct3TempVertex[0];
		ctTempFace.ct3Vertices[1] = ct3TempVertex[1];
		ctTempFace.ct3Vertices[2] = ct3TempVertex[2];
		ctTempFaces.lstctFaces.push_back(ctTempFace);
	}
}

static void vsglLoadFaceLists(ifstream &modelFile, vsglObjectData &ctTempObject)
{
	int iTexs = ctTempObject.iTexNum;
	bool bTextured = true;
	if (iTexs == 0)
	{
		iTexs = 1;
		bTextured = false;
	}
	
	vsglFacesData ctTempFaces;	
	for (int i = 0; i < iTexs; i++)
	{
													// load drawmode
		modelFile.read(&(ctTempFaces.cDrawMode), sizeof(ctTempFaces.cDrawMode));
		
													// load number of faces
		modelFile.read(reinterpret_cast<char *>(&(ctTempFaces.uiFaceNum)), sizeof(ctTempFaces.uiFaceNum));
		
													// load face list
		vsglLoadFaces(modelFile, ctTempFaces, bTextured);
		
		ctTempObject.lstctFaceLists.push_back(ctTempFaces);
	}
}

static void vsglLoadObjects(ifstream &modelFile, vsglModelData *ctModel)
{
	int j;
	string strTempStr;
	char caTempStr[25];
	for (int i = 0; i < ctModel->uiObjNum; i++)		// for every object:
	{
		vsglObjectData ctTempObject;				// object which is currently beeing readed
													// load number of vertices
		modelFile.read(reinterpret_cast<char *>(&(ctTempObject.uiVertNum)), sizeof(ctTempObject.uiVertNum));
		
													// load vertex-array
		ctTempObject.faVerts = new float[ctTempObject.uiVertNum*3];				// geht das so?				??????
		modelFile.read(reinterpret_cast<char *>(ctTempObject.faVerts), sizeof(float[ctTempObject.uiVertNum*3]));

													// load color of object-material
		modelFile.read(reinterpret_cast<char *>(ctTempObject.f4Color), sizeof(float[4]));

													// load textured "bit"
		modelFile.read(&(ctTempObject.cTextured), sizeof(ctTempObject.cTextured));

		ctTempObject.iTexNum = 0;
		if (ctTempObject.cTextured == '1')			// only loaded if model has textures
		{
													// load number of textures
			modelFile.read(reinterpret_cast<char *>(&(ctTempObject.iTexNum)), sizeof(ctTempObject.iTexNum));
			
													// load list of texture-filenames
			for (j = 0; j < ctTempObject.iTexNum; j++)
			{
				for (int i = 0; i < 25; i++)
					caTempStr[i] = '\0';
				modelFile.read(caTempStr, sizeof(char[24])-1);
				strTempStr = caTempStr;
				ctTempObject.lststrTexNames.push_back(strTempStr);
			}
		}
			
		vsglLoadFaceLists(modelFile, ctTempObject);	// load list of facelists	
		
		ctModel->lstctObjects.push_back(ctTempObject);	//	was wird übergeben? zeiger, value?				??????
	}
}

static void vsglRoundModel(vsglModelData *ctModel)	// rounds every float-value
{
	/* TODO (Maccesch#1#): Das Runden implementieren */
}

static void vsglLoadModel(const char *cpFilename, vsglModelData *ctModel)
{
	ifstream modelFile;								// open file to read data from
	modelFile.open(cpFilename, ios_base::binary);
	
	if (modelFile.bad())							// error
		cerr << cpFilename << "couldn't be opened!\n";

	ctModel->caFormatVersion[8] = '\0';				// load file's version of VSM standard
	modelFile.read(ctModel->caFormatVersion, sizeof(ctModel->caFormatVersion)-1);
	
													// load level of detail
	modelFile.read(reinterpret_cast<char *>(&(ctModel->sLod)), sizeof(ctModel->sLod));

													// load number of objects
	modelFile.read(reinterpret_cast<char *>(&(ctModel->uiObjNum)), sizeof(ctModel->uiObjNum));
	
	vsglLoadObjects(modelFile, ctModel);			// load each Object
	
	vsglRoundModel(ctModel);						// round all float-values
	
	modelFile.close();
}

void vsglInitModel(const char *cpFilename)
{
	if (ctCurrentModel != 0)
	{
		// TODO : Throw Exception (one model already initialised)
	}
	
	ctCurrentModel = new vsglModelData;
	vsglLoadModel(cpFilename, ctCurrentModel);
}

int vsglGetTexNum()			// calc number of textures to be generated
{
	if (ctCurrentModel == 0)
	{
		// TODO : Throw Exception (no model initialised)
	}


	int iTexNumber = 0;
	list<vsglObjectData>::iterator objIterator;
	for (objIterator = ctCurrentModel->lstctObjects.begin(); objIterator != ctCurrentModel->lstctObjects.end(); objIterator++)
		iTexNumber += objIterator->iTexNum;
		
	return iTexNumber;
}

list<string> &vsglGetTexNames()			//  get list of all texture names occuring in the model
{
	if (ctCurrentModel == 0)
	{
		// TODO : Throw Exception (no model initialised)
	}

	list<vsglObjectData>::iterator objIterator;
	list<string>::iterator strIterator;
	list<string> *lststrTexNames = new list<string>;
	for (objIterator = ctCurrentModel->lstctObjects.begin(); objIterator != ctCurrentModel->lstctObjects.end(); objIterator++)
	{
		if (objIterator->cTextured == '1')
		{
			for (strIterator = objIterator->lststrTexNames.begin(); strIterator != objIterator->lststrTexNames.end(); strIterator++)
					lststrTexNames->push_back(*strIterator);
		}
	}

	lststrTexNames->sort();			// each texture name should occur only once in the list
	lststrTexNames->unique();
	return *lststrTexNames;
}

int vsglGetObjNum()
{
	if (ctCurrentModel == 0)
	{
		// TODO : Throw Exception (no model initialised)
	}
	
	return ctCurrentModel->uiObjNum;
}

void vsglBindModel(GLuint &uiDisplayLists, GLuint *uipTextureObjs)
{
	if (ctCurrentModel == 0)
	{
		// TODO : Throw Exception (no model initialised)
	}

	list<string> lststrTexNames = vsglGetTexNames();
	list<string>::iterator strIterator;
	int i = 0;
	for (strIterator = lststrTexNames.begin(); strIterator != lststrTexNames.end(); strIterator++, i++)
	{
		vsglLoadTex(strIterator->c_str(), *(uipTextureObjs + i));
	}

	list<vsglObjectData>::iterator objIterator;
	list<vsglFacesData>::iterator facesIterator;
	list<vsglFaceData>::iterator faceIterator;
	list<string>::iterator strIter2;
	
	int iNumOfObj = 0;
	for (objIterator = ctCurrentModel->lstctObjects.begin(); objIterator != ctCurrentModel->lstctObjects.end(); objIterator++, iNumOfObj++)
	{
		glNewList(uiDisplayLists + iNumOfObj, GL_COMPILE);
		
		glColor4fv(objIterator->f4Color);
		
		strIterator = objIterator->lststrTexNames.begin();
		for (facesIterator = objIterator->lstctFaceLists.begin(); facesIterator != objIterator->lstctFaceLists.end(); facesIterator++, strIterator++)
		{
			// determine texture object number out of the texture name
			i = 0;
			for (strIter2 = lststrTexNames.begin(); strIter2 != lststrTexNames.end(); strIter2 ++, i++)
			{
				if (*strIter2 == *strIterator) break;
			}
			glBindTexture(GL_TEXTURE_2D, *(uipTextureObjs + i));
			
			switch (facesIterator->cDrawMode)
			{
				case '0' :
					glBegin(GL_TRIANGLES);
					break;
				case '1' : 
					glBegin(GL_TRIANGLE_STRIP);
					break;
				case '2' : 
					glBegin(GL_TRIANGLE_FAN);
					break;
			}
			for (faceIterator = facesIterator->lstctFaces.begin();  faceIterator != facesIterator->lstctFaces.end(); faceIterator++)
			{
				if (objIterator->cTextured == '1')
					glTexCoord2f(faceIterator->ct3Vertices[0].fU, faceIterator->ct3Vertices[0].fV);
				glNormal3fv(faceIterator->ct3Vertices[0].f3Norm);
				glVertex3fv(&objIterator->faVerts[faceIterator->ct3Vertices[0].uiVertIndex*3]);

				if (objIterator->cTextured == '1')
					glTexCoord2f(faceIterator->ct3Vertices[1].fU, faceIterator->ct3Vertices[1].fV);
				glNormal3fv(faceIterator->ct3Vertices[1].f3Norm);
				glVertex3fv(&objIterator->faVerts[faceIterator->ct3Vertices[1].uiVertIndex*3]);

				if (objIterator->cTextured == '1')
					glTexCoord2f(faceIterator->ct3Vertices[2].fU, faceIterator->ct3Vertices[2].fV);
				glNormal3fv(faceIterator->ct3Vertices[2].f3Norm);
				glVertex3fv(&objIterator->faVerts[faceIterator->ct3Vertices[2].uiVertIndex*3]);

// draw normals
//				if (faceIterator == ++facesIterator->lstctFaces.begin()--)
//				{
//					glEnd();
//					glBegin(GL_LINES);
//					
//					glVertex3fv(&objIterator->faVerts[faceIterator->ct3Vertices[0].uiVertIndex*3]);
//					glVertex3f(faceIterator->ct3Vertices[0].f3Norm[0] + objIterator->faVerts[faceIterator->ct3Vertices[0].uiVertIndex*3],
//							   faceIterator->ct3Vertices[0].f3Norm[1] + objIterator->faVerts[faceIterator->ct3Vertices[0].uiVertIndex*3+1],
//							   faceIterator->ct3Vertices[0].f3Norm[2] + objIterator->faVerts[faceIterator->ct3Vertices[0].uiVertIndex*3+2]);
//	
//					glVertex3fv(&objIterator->faVerts[faceIterator->ct3Vertices[1].uiVertIndex*3]);
//					glVertex3f(faceIterator->ct3Vertices[1].f3Norm[0] + objIterator->faVerts[faceIterator->ct3Vertices[1].uiVertIndex*3],
//							   faceIterator->ct3Vertices[1].f3Norm[1] + objIterator->faVerts[faceIterator->ct3Vertices[1].uiVertIndex*3+1],
//							   faceIterator->ct3Vertices[1].f3Norm[2] + objIterator->faVerts[faceIterator->ct3Vertices[1].uiVertIndex*3+2]);
//	
//					glVertex3fv(&objIterator->faVerts[faceIterator->ct3Vertices[2].uiVertIndex*3]);
//					glVertex3f(faceIterator->ct3Vertices[2].f3Norm[0] + objIterator->faVerts[faceIterator->ct3Vertices[2].uiVertIndex*3],
//							   faceIterator->ct3Vertices[2].f3Norm[1] + objIterator->faVerts[faceIterator->ct3Vertices[2].uiVertIndex*3+1],
//							   faceIterator->ct3Vertices[2].f3Norm[2] + objIterator->faVerts[faceIterator->ct3Vertices[2].uiVertIndex*3+2]);
//					
//					glEnd();
//					glBegin(GL_TRIANGLES);
//				}
			}
			
			glEnd();

		}
		
	glEndList();
	}

	delete ctCurrentModel;
	ctCurrentModel = 0;
}

// for traversing the several layers in the model structure
//
//int main(int argc, char *argv[])
//{
//	vsglModelData *ctModel = new vsglModelData;
//	vsglLoadModel("test.vsm", ctModel);
//	
//	cout << "caFormatVersion: " << ctModel->caFormatVersion << endl;
//	cout << "sLod: " << ctModel->sLod << endl;
//	cout << "uiObjNum: " << ctModel->uiObjNum << endl;
//	cout << endl;
//	
//	list<vsglObjectData>::iterator objIterator;
//	list<vsglFacesData>::iterator facesIterator;
//	list<string>::iterator strIterator;
//	list<vsglFaceData>::iterator faceIterator;
//	for (objIterator = ctModel->lstctObjects.begin(); objIterator != ctModel->lstctObjects.end(); objIterator++)
//	{
//		cout << "  uiVertNum: " << objIterator->uiVertNum << endl;
//		cout << "  faVerts: " << endl;
//		for (int i = 0; i < objIterator->uiVertNum; i++)
//			cout << "    (" << objIterator->faVerts[i*3] << ", " << 
//							objIterator->faVerts[i*3+1]  << ", " <<
//							objIterator->faVerts[i*3+2] << ")" << endl;
//		cout << "  f4Color (3): " << objIterator->f4Color[0] << ", " << objIterator->f4Color[1] << ", " << objIterator->f4Color[2] << endl;
//		cout << "  cTextured: " << (objIterator->cTextured == '1' ? "true" : "false") << endl;
//		if (objIterator->cTextured == '1')
//		{
//			cout << "  iTexNum: " << objIterator->iTexNum << endl;
//			cout << "  lststrTexNames: " << endl;
//			for (strIterator = objIterator->lststrTexNames.begin(); strIterator != objIterator->lststrTexNames.end(); strIterator++)
//				cout << "    " << *strIterator << endl;
//		}
//		
//		cout << endl;
//		for (facesIterator = objIterator->lstctFaceLists.begin(); facesIterator != objIterator->lstctFaceLists.end(); facesIterator++)
//		{
//			cout << "    cDrawMode: " << (facesIterator->cDrawMode == '0' ? "TRIANGLES" : (facesIterator->cDrawMode == '1' ? "TRIANGLE_STRIP" : "TRIANGLE_FAN")) << endl;
//			cout << "    uiFaceNum: " << facesIterator->uiFaceNum << endl;
//			for (faceIterator = facesIterator->lstctFaces.begin();  faceIterator != facesIterator->lstctFaces.end(); faceIterator++)
//			{
//				cout << "      ctVertices[0]: " << endl;
//				cout << "        uiVertIndex: " << faceIterator->ct3Vertices[0].uiVertIndex << endl;
//				cout << "        f3Norm: (" << faceIterator->ct3Vertices[0].f3Norm[0] << ", " 
//											<< faceIterator->ct3Vertices[0].f3Norm[1] << ", "
//											<< faceIterator->ct3Vertices[0].f3Norm[2] << ")" << endl;
//				if (objIterator->cTextured == '1')
//				{
//					cout << "        fU: " << faceIterator->ct3Vertices[0].fV << endl;
//					cout << "        fV: " << faceIterator->ct3Vertices[0].fU << endl;
//				}
//				cout << endl;
//
//				cout << "      ctVertices[1]: " << endl;
//				cout << "        uiVertIndex: " << faceIterator->ct3Vertices[1].uiVertIndex << endl;
//				cout << "        f3Norm: (" << faceIterator->ct3Vertices[1].f3Norm[1] << ", " 
//											<< faceIterator->ct3Vertices[1].f3Norm[1] << ", "
//											<< faceIterator->ct3Vertices[1].f3Norm[2] << ")" << endl;
//				if (objIterator->cTextured == '1')
//				{
//					cout << "        fU: " << faceIterator->ct3Vertices[1].fV << endl;
//					cout << "        fV: " << faceIterator->ct3Vertices[1].fU << endl;
//				}
//				cout << endl;
//
//				cout << "      ctVertices[2]: " << endl;
//				cout << "        uiVertIndex: " << faceIterator->ct3Vertices[2].uiVertIndex << endl;
//				cout << "        f3Norm: (" << faceIterator->ct3Vertices[2].f3Norm[2] << ", " 
//											<< faceIterator->ct3Vertices[2].f3Norm[1] << ", "
//											<< faceIterator->ct3Vertices[2].f3Norm[2] << ")" << endl;
//				if (objIterator->cTextured == '1')
//				{
//					cout << "        fU: " << faceIterator->ct3Vertices[2].fV << endl;
//					cout << "        fV: " << faceIterator->ct3Vertices[2].fU << endl;
//				}
//				cout << "      ---------------------" << endl;
//			}
//
//		}
//		
//		cout << endl;
//	}
//
//	delete ctModel;
//
//	system("PAUSE");	
//	return 0;
//}

