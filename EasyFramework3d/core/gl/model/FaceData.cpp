#include <vs/core/gl/model/FaceData.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

FaceData::FaceData()									// default constructor
{
	VertexData empty;
	vertices[0] = empty;
	vertices[1] = empty;
	vertices[2] = empty;
}

FaceData::FaceData(const FaceData &rhs)			// copy constructor
{
	vertices[0] = rhs.vertices[0];
	vertices[1] = rhs.vertices[1];
	vertices[2] = rhs.vertices[2];
}

FaceData &FaceData::operator=(const FaceData &rhs)
{
	if (&rhs != this)
	{
		vertices[0] = rhs.vertices[0];
		vertices[1] = rhs.vertices[1];
		vertices[2] = rhs.vertices[2];
	}

	return *this;
}

} // model
} // gl
} // core
} // vs
