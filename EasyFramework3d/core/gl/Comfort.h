// TODO! rename this file to Comfort.hpp

#ifndef COMFORT_H
#define COMFORT_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/math/DoubleVector.h>
#include <vs/core/gl/Color.h>
#include <GL/gl.h>

namespace vs
{
namespace core
{
namespace gl
{

VS_EXPORT inline void glTranslatev(base::util::math::DoubleVector &v) {
	glTranslated(v.x(), v.y(), v.z());
}

VS_EXPORT inline void glColorv(Color &c)
{
	glColor4f(c.r(), c.g(), c.b(), c.a());
}

} // gl
} // core
} // vs

#endif // COMFORT_H
