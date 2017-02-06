#include <vs/core/gl/model/VertexArrayBuilder.h>
#include <vs/core/gl/model/FaceGroupData.h>
#include <vs/core/gl/model/ModelData.h>
#include <vs/core/gl/model/ObjectData.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

VertexArrayBuilder::VertexArrayBuilder()
//: array(NULL)
{
}

VertexArrayBuilder::~VertexArrayBuilder()
{
//	delete [] array;
//	array = NULL;
}

void VertexArrayBuilder::visit(ModelData &model)
{
	for (list<ObjectData>::iterator it = model.objects.begin(); it != model.objects.end(); ++it)
	{
		visit(*it);
	}
}

void VertexArrayBuilder::visit(ObjectData &object)
{
	// object.verts
	// layout of the vertex array when textured is:
	// GL_T2F_N3F_V3F
	for (list<FaceGroupData>::iterator it = object.facesGroups.begin(); it != object.facesGroups.end(); ++it)
	{
		visit(*it);
	}
}

void VertexArrayBuilder::visit(FaceGroupData &faceGroup)
{
//	faceGroup.drawMode;
//	faceGroup.smooth;
	for (list<VertexData>::iterator it = faceGroup.verts.begin(); it != faceGroup.verts.end(); ++it)
	{
		visit(*it);
	}
}

void VertexArrayBuilder::visit(VertexData &vertex)
{
	
}

} // model
} // gl
} // core
} // vs
