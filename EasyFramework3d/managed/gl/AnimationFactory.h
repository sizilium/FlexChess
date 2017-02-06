/**
 * @file AnimationFactory.h
 * @author sizilium
 * @date 21.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef ANIMATION_FACTORY_H
#define ANIMATION_FACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/managed/gl/AbstractAnimationFactory.h>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <iostream>

namespace vs
{
namespace managed
{
namespace gl
{
// predeclarations
class ModelAnimation;
namespace model { class ManagedModel; }


/**
 * Factory class to create ModelAnimtion objects.
 * See createAnimation() for an example.
 */
class VS_EXPORT AnimationFactory : 	public AbstractAnimationFactory, 
									public base::xml::AbstractXmlFactory
{
public:
	AnimationFactory();
	virtual ~AnimationFactory();
	
	/**
	 * See base::interfaces::AbstractFactory::getName()
	 */
	const string getName() const
	{
		return "AnimationFactory";
	}

	/**
	 * Loads an animation from hard disk and binds it to the specified model.
	 * The binding is done by storing the render queue iterators for the centers,
	 * eulers.
	 * @param[in] vsa_path The path of the animation file (.vsa) to be loaded.
	 * @param[in] model The model which is the animation to be bound to.
	 * @param[in] objNameAdapter Maps the model object names stored in the animation
	 * file to the object names of the model. This is useful if you want to apply an
	 * animation to another model than it was originally created for. 
	 * 
	 * @throw Exception is thrown if an object name isn't found in the model. This
	 * can be caused for example if you forgot to map a name with objNameAdaper or
	 * if you mapped to a wrong name. See AnimationFactory::createAnimation().
	 * 
	 * @note The model has to be created with customCenters, customEulers and customSizes
	 * enabled. See ModelFactory.
	 * 
	 * @code // Example
	 * ...
	 * // assume that this model has two objects called 'Cube' and 'Sphere'
	 * ModelFactory modelFactory;
	 * ManagedModel *model = 
	 *     modelFactory.create("CubeAndSphere.vsm", "CubeSphere", true, true, true);
	 * 
	 * // now assume that this animation was created for two objects called 'Angled' and 'Round'.
	 * map<string, string> adapter;
	 * adapter["Angled"] = "Cube";
	 * AnimationFactory animationFactory;
	 * 
	 * // throws Exception: 'Round' is not known by model
	 * ModelAnimation *animation = 
	 *     animationFactory.createAnimation("AngledAndRound.vsa", model,
	 *
	 * adapter["Round"] = "Ball";
	 *
	 * // throws Exception: 'Ball' is not known by model
	 * ModelAnimation *animation = 
	 *     animationFactory.createAnimation("AngledAndRound.vsa", model,
	 *
	 * adapter["Round"] = "Sphere";
	 *
	 * // ok
	 * ModelAnimation *animation = 
	 *     animationFactory.createAnimation("AngledAndRound.vsa", model,
	 * @endcode
	 */
	ModelAnimation* createAnimation (const string &vsa_path,
	                                 model::ManagedModel *model,
	                                 const map<string, string> *objNameAdapter = NULL,
	                                 const std::string &animationName = "");

private:

};

} // gl
} // managed
} // vs

#endif  // ANIMATION_FACTORY_H
