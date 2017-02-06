#include <vs/core/gl/model/VertexData.h>

namespace vs
{
namespace core
{
namespace gl
{
namespace model
{

VertexData::VertexData()								// standard constructor
{
	index = 0;
	norm[0] = 0;
	norm[1] = 0;
	norm[2] = 0;
	u = 0;
	v = 0;
}

VertexData::VertexData(const VertexData &rhs)		// copy constructor
{
	index = rhs.index;
	norm[0] = rhs.norm[0];
	norm[1] = rhs.norm[1];
	norm[2] = rhs.norm[2];
	u = rhs.u;
	v = rhs.v;
}

VertexData &VertexData::operator=(const VertexData &rhs)
{
	if (&rhs != this)
	{
		index = rhs.index;
		norm[0] = rhs.norm[0];
		norm[1] = rhs.norm[1];
		norm[2] = rhs.norm[2];
		u = rhs.u;
		v = rhs.v;
	}

	return *this;
}

} // model
} // gl
} // core
} // vs
