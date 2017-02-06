#include <vs/core/gl/model/ObjectData.h>
#include <vs/core/gl/model/FaceGroupData.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

ObjectData::ObjectData()								// default constructor
	:
	name(), vertNum(0), texNames(), stripsNum(), fansNum(),
	facesGroups(), verts(NULL), textured(0), texNum(0)
{
	center[0] = 0;
	center[1] = 0;
	center[2] = 0;
	
	rotation[0] = 0;
	rotation[1] = 0;
	rotation[2] = 0;
	
	size[0] = 0;
	size[1] = 0;
	size[2] = 0;
	
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

ObjectData::ObjectData(const ObjectData &rhs)		// copy constructor
	:
	name(rhs.name),
	vertNum(rhs.vertNum),
	texNames(rhs.texNames),
	stripsNum(rhs.stripsNum),
	fansNum(rhs.fansNum),
	facesGroups(rhs.facesGroups),
	textured(rhs.textured),
	texNum(rhs.texNum)
{
	center[0] = rhs.center[0];
	center[1] = rhs.center[1];
	center[2] = rhs.center[2];
	rotation[0] = rhs.rotation[0];
	rotation[1] = rhs.rotation[1];
	rotation[2] = rhs.rotation[2];
	size[0] = rhs.size[0];
	size[1] = rhs.size[1];
	size[2] = rhs.size[2];
	verts = new float[rhs.vertNum * 3];
	memcpy((void *) verts, (void *) rhs.verts, sizeof(float[rhs.vertNum * 3]));
	color[0] = rhs.color[0];
	color[1] = rhs.color[1];
	color[2] = rhs.color[2];
	color[3] = rhs.color[3];
}

ObjectData &ObjectData::operator=(const ObjectData &rhs)
{
	if (&rhs != this)
	{
		name = rhs.name;
		texNames = rhs.texNames;
		stripsNum = rhs.stripsNum;
		fansNum = rhs.fansNum;
		facesGroups = rhs.facesGroups;
		vertNum = rhs.vertNum;
		center[0] = rhs.center[0];
		center[1] = rhs.center[1];
		center[2] = rhs.center[2];
	    rotation[0] = rhs.rotation[0];
	    rotation[1] = rhs.rotation[1];
	    rotation[2] = rhs.rotation[2];
	    size[0] = rhs.size[0];
	    size[1] = rhs.size[1];
	    size[2] = rhs.size[2];
		delete [] verts;
		verts = new float[rhs.vertNum * 3];
		memcpy((void *) verts, (void *) rhs.verts, sizeof(float[rhs.vertNum * 3]));
		color[0] = rhs.color[0];
		color[1] = rhs.color[1];
		color[2] = rhs.color[2];
		color[3] = rhs.color[3];
		textured = rhs.textured;
		texNum = rhs.texNum;
	}
	
	return *this;
}

ObjectData::~ObjectData()								// destructor
{
	delete [] verts;
	verts = NULL;
}

} // model
} // gl
} // core
} // vs
