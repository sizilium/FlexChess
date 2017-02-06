// Vision Snythesis Model Loading Library
// Written by Maccesch. Started on Thursday, 25.11.2004
// Last modification:  02.03.2005
// Don't worry, be happy ;-)

// #define MODEL_LOADER_DRAW_NORMALS

#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>

#include <GL/glu.h>
#include <GL/gl.h>

#include <vs/core/gl/model/FaceGroupData.h>
#include <vs/core/gl/ImageLoader.h>
#include <vs/core/gl/model/ModelLoader.h>
#include <vs/core/gl/model/ObjectData.h>
#include <vs/core/gl/model/ModelData.h>

#include <vs/core/gl/Color.h>
#include <vs/base/util/FileException.h>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

using namespace vs::base::util;

const char ModelLoader::END_CHAR = '@';


void fileGood(string &filename, ifstream &file)
{
	// TODO : use exceptions instead of almost this (see "Die C++ Programmiersprache" Page 667)
	if (!file.good())
	{
		string desc;
		if (file.eof())
			desc = "Unexpected end of file";
		else
			desc = "Unknown io error";

		throw FileException("ModelLoader.cpp", "fileGood", desc, filename);
	}
}

void ModelLoader::visit(VertexData &vertex)
{
	try
	{
		fileGood(filename, modelFile);
	}
	catch (FileException e)
	{
		e.addPlaceOfError("ModelLoader.cpp", "ModelLoader::visit(VertexData)");
		throw e;
	}

	// load index of this vertex
	modelFile.read(reinterpret_cast<char *>(&(vertex.index)),
				   sizeof(vertex.index));

	// load normal vector
	modelFile.read(reinterpret_cast<char *>(vertex.norm), sizeof(vertex.norm));

	// UV Coordinates only when textured
	if (textured)
	{
		// load U-coordinate
		modelFile.read(reinterpret_cast<char *>(&(vertex.u)), sizeof(vertex.u));

		// load V-coordinate
		modelFile.read(reinterpret_cast<char *>(&(vertex.v)), sizeof(vertex.v));
	}
}

void ModelLoader::visit(FaceGroupData &faceGroup)
{
	try
	{
		fileGood(filename, modelFile);

        // load smoothness of this face group
		if (faceGroup.drawMode != GL_TRIANGLES)
		{
			char smooth;
            modelFile.read(&smooth, sizeof(smooth));
            if (smooth == '1')
            	faceGroup.smooth = GL_SMOOTH;
            else
            	faceGroup.smooth = GL_FLAT;
		}
		else
			faceGroup.smooth = GL_SMOOTH;

		// load number of faces
		modelFile.read(reinterpret_cast<char *>(&(faceGroup.faceNum)), sizeof(faceGroup.faceNum));

		// calc number of vertices
		unsigned int vertNum;
		if (faceGroup.drawMode != GL_TRIANGLES)
			vertNum = faceGroup.faceNum + 2;
		else
			vertNum = faceGroup.faceNum * 3;

		// load vertices
		for (unsigned int i = 0; i < vertNum; i++)
		{
			VertexData tempVert;
			visit(tempVert);

			faceGroup.verts.push_back(tempVert);
		}
	}
	catch (FileException e)
	{
		e.addPlaceOfError("ModelLoader.cpp", "ModelLoader::visit(FaceGroupData)");
		throw e;
	}
}

void ModelLoader::visit(ObjectData &object)
{
	try
	{
		string tempStr;
		char tempCStr[24];

		fileGood(filename, modelFile);

		// load object name
		char temp = ' ';
		object.name = "";
		while (temp != END_CHAR)
		{
			modelFile.read(&temp, sizeof(temp));
			if (temp != END_CHAR)
				object.name += temp;
		}

		// load object center
		modelFile.read(reinterpret_cast<char *>(object.center), sizeof(float) * 3);

	    // load object rotation
		modelFile.read(reinterpret_cast<char *>(object.rotation), sizeof(float) * 3);
	    // load object size
		modelFile.read(reinterpret_cast<char *>(object.size), sizeof(float) * 3);

		// load number of vertices
		modelFile.read(reinterpret_cast<char *>(&(object.vertNum)), sizeof(object.vertNum));
		// load vertex-array
		object.verts = new float[object.vertNum * 3];
		modelFile.read(reinterpret_cast<char *>(object.verts), sizeof(float) * object.vertNum * 3);

		// load color of object-material
		modelFile.read(reinterpret_cast<char *>(object.color), sizeof(object.color));

		// load textured "bit"
		modelFile.read(&(object.textured), sizeof(object.textured));

		textured = false;
		object.texNum = 1;
		if (object.textured == '1')			// only loaded if model has textures
		{
			// load number of textures
			modelFile.read(reinterpret_cast<char *>(&(object.texNum)), sizeof(object.texNum));

			// load list of texture-filenames
			for (int j = 0; j < object.texNum; j++)
			{
				tempCStr[23] = '\0';
				modelFile.read(tempCStr, sizeof(char[23]));
				tempStr = tempCStr;

				// erase trailing spaces
				for (int i = tempStr.length() - 1; i >= 0; i--)
				{
					if (tempStr[i] == ' ')
						tempStr.erase(i);
					else
						break;
				}

				object.texNames.push_back(tempStr);
			}

			textured = true;
		}

		// load face lists
		for (int j = 0; j < object.texNum; j++)
		{
			fileGood(filename, modelFile);

			// triangle strips first
			unsigned int stripsNum;
			// load number of triangle strips
			modelFile.read(reinterpret_cast<char *>(&(stripsNum)), sizeof(stripsNum));
			object.stripsNum.push_back(stripsNum);

			for (unsigned int k = 0; k < stripsNum; k++)
			{
                FaceGroupData tempFaces;
                tempFaces.drawMode = GL_TRIANGLE_STRIP;
				// load list of triange strips
				visit(tempFaces);

				object.facesGroups.push_back(tempFaces);
			}

			// triangle fans second
			unsigned int fansNum;
			// load number of triangle fans
			modelFile.read(reinterpret_cast<char *>(&(fansNum)), sizeof(fansNum));
			object.fansNum.push_back(fansNum);

			for (unsigned int k = 0; k < fansNum; k++)
			{
                FaceGroupData tempFaces;
                tempFaces.drawMode = GL_TRIANGLE_FAN;
				// load list of triange fans
				visit(tempFaces);

				object.facesGroups.push_back(tempFaces);
			}

			// third: load list of triangles
            FaceGroupData tempFaces;
            tempFaces.drawMode = GL_TRIANGLES;
			visit(tempFaces);

			object.facesGroups.push_back(tempFaces);
		}
	}
	catch (FileException e)
	{
		e.addPlaceOfError("ModelLoader.cpp", "ModelLoader::visit(ObjectData)");
		throw e;
	}
}

void ModelLoader::load(const string &filename, ModelData &model)
{
	this->filename = filename;
	modelFile.open(filename.c_str(), ios_base::binary);

	if (!modelFile.good())							// error
		throw FileException("ModelLoader.cpp", "ModelLoader::load",
                            "The file couldn't be opened (maybe the file wasn't found)", filename);

	try
	{
		fileGood(this->filename, modelFile);
	}
	catch (FileException e)
	{
		e.addPlaceOfError("ModelLoader.cpp", "ModelLoader::load");
		throw e;
	}

	visit(model);
}

void ModelLoader::visit(ModelData &model)
{
	// separate the filename from its path and store both in model
	unsigned int index = filename.find_last_of('/');
	if (index < filename.length())
		index = filename.find_last_of('\\');

	if (index < filename.length())
	{
		model.path = filename.substr(0, index);

		model.filename = filename.substr(index + 1);
	}
	else
	{
		model.filename = filename;
		model.path = "";
	}

	// load file's version of VSM standard
	char temp[9];
	temp[8] = '\0';
	modelFile.read(temp, sizeof(char) * 8);
	model.formatVersion = atof(&temp[4]);

	// a model file has to start with "VSM"
	if (strncmp(temp, "VSM", 3) != 0)
		throw FileException("ModelLoader.cpp", "ModelLoader::load",
		                    "The file is not a Vision Synthesis Model File", filename);

	// load level of detail
	modelFile.read(reinterpret_cast<char *>(&(model.lod)), sizeof(model.lod));

	// load number of objects
	modelFile.read(reinterpret_cast<char *>(&(model.objNum)), sizeof(model.objNum));

	// load the objects (see class ObjectData)
	try
	{
		for (unsigned int i = 0; i < model.objNum; i++)
		{
			ObjectData object;
			visit(object);
			model.objects.push_back(object);
		}
	}
	catch (FileException e)
	{
		e.addPlaceOfError("ModelLoader.cpp", "loadModel");
		throw e;
	}

	// check if all data has been read
	char tempChar;

	// one byte is always too much in the file
	modelFile.read(&tempChar, 1);

	if (!modelFile.eof())
	{
		double i = 0;
		while (!modelFile.eof())
		{
			modelFile.read(&tempChar, 1);
			i++;
		}
		string unit = "byte";
		if (i > 1)
			unit += "s";
		if (i >= 1024)
		{
			i /= 1024;
			unit = "kilobytes";
		}
		if (i >= 1024)
		{
			i /= 1024;
			unit = "Megabytes";
		}

		ostringstream desc;
		desc << "The file contains too much data (" << i << " " <<
				unit << " have been remaining after reading was finished)";
		throw FileException("ModelLoader.cpp", "loadModel", desc.str(), filename);
	}

	modelFile.close();
}

} // namespace model
} // namespace gl
} // namespace core
} // namespace vs
