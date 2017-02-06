#include <vs/base/util/ReferenceCounting.h>

namespace vs
{
namespace base
{
namespace util
{

RcObject::RcObject()
:refCount(0), shareable(true)
{}

RcObject::RcObject(const RcObject&)
:refCount(0), shareable(true)
{}

RcObject& RcObject::operator=(const RcObject&)
{
	return *this;
}

RcObject::~RcObject()
{}

void RcObject::addReference()
{
	++refCount;
}

void RcObject::removeReference()
{
	if (--refCount == 0)
		delete this;
}

void RcObject::markUnshareable()
{
	shareable = false;
}

bool RcObject::isShareable() const
{
	return shareable;
}

bool RcObject::isShared() const
{
	return refCount > 1;
}

} // util
} // base
} // vs
