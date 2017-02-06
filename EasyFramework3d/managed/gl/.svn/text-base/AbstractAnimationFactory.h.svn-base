/**
 * @file AbstractAnimationFactory.h
 * @author sizilium
 * @date 21.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ABSTRACT_ANIMATION_FACTORY_H
#define ABSTRACT_ANIMATION_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/managed/gl/AnimationManager.h>
#include <vs/managed/gl/ModelAnimation.h>

namespace vs
{
namespace managed
{
namespace gl
{

/** @class AbstractAnimationFactory
 * 
 */
class VS_EXPORT AbstractAnimationFactory : public base::interfaces::AbstractFactory<managed::gl::AnimationManager>
{
public:
	virtual ~AbstractAnimationFactory();
	
	virtual const string getName() const = 0;
	const string getNamespace() const	{ return "vs::managed::gl"; }
	
protected:
	void addAnimation(ModelAnimation *animation);
};

} // gl
} // managed
} // vs

#endif  // ABSTRACT_ANIMATION_FACTORY_H
