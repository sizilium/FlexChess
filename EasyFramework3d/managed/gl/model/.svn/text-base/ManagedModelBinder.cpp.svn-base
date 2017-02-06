/**
 * @file ManagedModelBinder.cpp
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */


#ifndef HEADER_H
#define HEADER_H

// includes

namespace vs
{
namespace subNamespace
{
	
/** @class className
 * 
 */
class className
{
public:
	className();
	~className();
	
private:
	
};

}  // subNamespace
}  // vs

#endif  // HEADER_H

#include <vs/managed/gl/model/ManagedModelBinder.h>
#include <vs/base/util/FileException.h>
#include <vs/managed/gl/model/ModelManager.h>
#include <vs/core/gl/TextureManager.h>
#include <vs/base/math/DoubleVector.h>
#include <vs/core/gl/GLException.h>
#include <vs/base/util/Exception.h>
#include <vs/core/gl/Color.h>
#include <vs/core/gl/model/FaceGroupData.h>
#include <vs/core/gl/model/ModelData.h>
#include <vs/core/gl/model/ObjectData.h>
#include <vs/core/gl/model/VertexData.h>
#include <sstream>

using namespace std;

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{

using namespace vs::base::math;
using namespace vs::base::util;
using namespace vs::core::gl::model;
using namespace vs::core::gl;

void ManagedModelBinder::bind(ModelData &model)
{
	try
	{
		visit(model);
	}
	catch (GLException e)
	{
		e.addPlaceOfError("ModelBinder.cpp", "ModelBinder::bind");
		throw e;
	}
	catch (Exception e)
	{
		e.addPlaceOfError("ModelBinder.cpp", "ModelBinder::bind");
		throw e;
	}
}

void ManagedModelBinder::visit(ModelData &model)
{
	// this binder assumes that the model file has at least version 1.10
	if (model.formatVersion < 1.10f)
	{
		ostringstream desc;
		desc << "The model version " << model.formatVersion <<" of the model file is too old. You need at least version 1.10.";
		throw FileException("ModelBinder.cpp", "ModelBinder::visit(ModelData)", desc.str(),
				model.filename);
	}

	// test if opengl has been initialized
	glPushMatrix();
	glPopMatrix();
	if (glGetError() != GL_NO_ERROR)
		throw Exception(__FILE__, __LINE__, "OpenGL isn't ready to use. Initialize first.");

	list<ObjectData>::iterator it;

	// set path and modelpath
	path = "";
	if (model.path != "")
	{
		path = model.path + "/";
		modelpath = path + model.filename;
	}
	else
	{
		modelpath = model.filename;
	}

	// bind every object
	for (it = model.objects.begin(); it != model.objects.end(); ++it)
	{
		visit(*it);
	}

	// check for OpenGL Errors finally
	GLenum errorCode = glGetError();
	if (errorCode != GL_NO_ERROR)
		throw GLException("ModelBinder.cpp", "ModelBinder::visit(ModelData)", errorCode);
}

void ManagedModelBinder::visit(ObjectData &object)
{
	list<FaceGroupData>::iterator it;

	verts = object.verts;

	// each object corresponds to a modelManager-model-id
	ModelManager *modelManager = ModelManager::getCurrentManager();
	currentModelId = modelManager->modelIdGen.getNextID();

	// store the filename related relations in the model manager
	modelManager->filenames2models[modelpath].push_back(currentModelId);
	modelManager->objNamesFilenames2models[make_pair(object.name, modelpath)] = currentModelId;

	// store the properties of the current object in the model manager
	modelManager->models2rotations[currentModelId] = DoubleVector(&(object.rotation[0]));
	modelManager->models2sizes[currentModelId] = DoubleVector(&(object.size[0]));
	modelManager->models2centers[currentModelId] = DoubleVector(&(object.center[0]));
	modelManager->models2colors[currentModelId] = Color(object.color);

	currObjTextured = (object.textured == '1');

	unsigned int drawnGroups = 0;

	// number of strip face groups for the current texture
	list<unsigned int>::iterator stripsIt = object.stripsNum.begin();

	// number of fan face groups for the current texture
	list<unsigned int>::iterator fansIt = object.fansNum.begin();

	// current texture name
	list<string>::iterator strIterator = object.texNames.begin();

	for (it = object.facesGroups.begin(); it != object.facesGroups.end(); ++it)
	{
		// start the next display list
		if (drawnGroups == 0)
		{
			GLuint displayList = glGenLists(1);
			glNewList(displayList, GL_COMPILE);

			if (currObjTextured)
			{
				// store the texture related relations of the model manager
				GLuint currentTexture = core::gl::textureManager.getTexId(path + *strIterator);
				modelManager->modelsTex2displayLists[make_pair(currentModelId, currentTexture)].push_back(displayList);
				modelManager->models2textures[currentModelId].push_back(currentTexture);
			}
			else
			{
				modelManager->models2untexturedDLists[currentModelId].push_back(displayList);
			}
		}

		// draw the current face group
		visit(*it);

		drawnGroups++;

		// if every face group for a texture is drawn end the current display list
		// and goto the next texture
		// every face group = all strips, all fans and the triangles group
		if (drawnGroups == (*stripsIt) + (*fansIt) + 1)
		{
			glEndList();

			drawnGroups = 0;
			// TODO : untextured objects?
			++strIterator;
			++stripsIt;
			++fansIt;
		}
	}
}

void ManagedModelBinder::visit(FaceGroupData &faceGroup)
{
	list<VertexData>::iterator it;

	// TODO? : optimize: minimize state changes? state change isn't performed when already active
	glShadeModel(faceGroup.smooth);

	glBegin(faceGroup.drawMode);

	// call every vertex
	for (it = faceGroup.verts.begin(); it != faceGroup.verts.end(); ++it)
	{
		visit(*it);
	}

	glEnd();

}

void ManagedModelBinder::visit(VertexData &vertex)
{
	// TODO : Use Array list
	if (currObjTextured)
		glTexCoord2f(vertex.u, vertex.v);
	glNormal3fv(vertex.norm);
	glVertex3fv(&verts[vertex.index*3]);
}

} // model
} // gl
} // managed
} // vs
