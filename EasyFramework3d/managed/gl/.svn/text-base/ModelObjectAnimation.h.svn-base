/**
 * @file ModelObjectAnimation.h
 * @author maccesch
 * @date 28.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODELOBJECTANIMATION_H_
#define MODELOBJECTANIMATION_H_

// includes
#include <vs/Build.hpp>
#include <list>
#include <vs/core/gl/ObjectAnimation.h>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace std;

class VS_EXPORT ModelObjectAnimation : public core::gl::ObjectAnimation
{
public:
	virtual ~ModelObjectAnimation();

	void setObjectCenterIt(const list<double>::iterator &centerIt) { objectCenterIt = centerIt; }
	void setObjectEulerIt(const list<double>::iterator &eulerIt) { objectEulerIt = eulerIt; }
	void setObjectSizeIt(const list<double>::iterator &sizeIt) { objectSizeIt = sizeIt; }

protected:
	// template method used in update()
	void transformObject();

	list<double>::iterator objectCenterIt;		///< pointer to the center of the object in the render queue
	list<double>::iterator objectEulerIt;		///< pointer to the euler of the object in the render queue
	list<double>::iterator objectSizeIt;		///< pointer to the size of the object in the render queue
};

} // gl
} // managed
} // vs

#endif /*MODELOBJECTANIMATION_H_*/
