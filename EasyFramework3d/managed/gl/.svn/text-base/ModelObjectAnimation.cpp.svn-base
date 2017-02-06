#include <vs/managed/gl/ModelObjectAnimation.h>

namespace vs
{
namespace managed
{
namespace gl
{

ModelObjectAnimation::~ModelObjectAnimation()
{
}

void ModelObjectAnimation::transformObject()
{
	// TODO? : is it faster when channelsEmpty is queried for the need of change?
	// translation
	list<double>::iterator it = objectCenterIt;
	*it = currentValues[0];
	++it;
	*it = currentValues[1];
	++it;
	*it = currentValues[2];

	// euler (rotation)
	it = objectEulerIt;
	*it = currentValues[5];
	++it;
	*it = currentValues[4];
	++it;
	*it = currentValues[3];

	// scalation
	it = objectSizeIt;
	*it = currentValues[6];
	++it;
	*it = currentValues[7];
	++it;
	*it = currentValues[8];
}

} // gl
} // managed
} // vs
