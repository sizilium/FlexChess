/**
 * @file ModelAnimation.h
 * @author maccesch
 * @date 30.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODELANIMATION_H_
#define MODELANIMATION_H_

// includes
#include <vs/Build.hpp>
#include <map>
#include <string>
#include <vs/managed/gl/ModelObjectAnimation.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/base/util/DefaultManaged.h>
#include <vs/base/util/FileException.h>
#include <vs/base/interfaces/AbstractProgressive.h>

namespace vs
{
namespace managed
{
namespace gl
{
// predeclarations
namespace model { class ManagedModel; }

using namespace std;

/**
 * This class represents a loaded animation bound to an ManagedModel object.
 * For an example how to use a model animation see AnimationFactory::createAnimation().
 * This class is the composite in the composite design pattern.
 */
class VS_EXPORT ModelAnimation : 	public base::util::DefaultManaged,
					   				public base::interfaces::AbstractProgressive
{
public:
	ModelAnimation();
	virtual ~ModelAnimation();

	/**
	 * Loads an animation from hard disk and binds it to the specified model.
	 * The binding is done by storing the render queue iterators for the centers,
	 * eulers.
	 * @param[in] filename The path of the animation file (.vsa) to be loaded.
	 * @param[in] model The model which is the animation to be bound to.
	 * @param[in] objNameAdapter Maps the model object names stored in the animation
	 * file to the object names of the model. This is useful if you want to apply an
	 * animation to another model than it was originally created for. 
	 * @throw Exception is thrown if an object name isn't found in the model. This
	 * can be caused for example if you forgot to map a name with objNameAdaper or
	 * if you mapped to a wrong name. See AnimationFactory::createAnimation().
	 * @throw FileException is thrown if the file can't be found or isn't a VSA file.
	 * @note The model has to be created with customCenters, customEulers and customSizes
	 * enabled. See ModelFactory.
	 */
	void load(string filename, model::ManagedModel &model,
			  const map<string, string> *objNameAdapter = NULL);

	/**
	 * See AbstractProgressive::update()
	 */
	void update(double deltaT);

	/**
	 * See AbstractProgressive::setCyclic()
	 */
	void setCyclic(bool cyclic);

	/**
	 * See AbstractProgressive::play()
	 */
	void play();
	/**
	 * See AbstractProgressive::stop()
	 */
	void stop();
	/**
	 * Sets the animation progress to the start (like seek(0)).
	 */
	void toStart();
	/**
	 * Sets the animation progress to the end (like seekFractional(1)).
	 */
	void toEnd();
	/**
	 * See AbstractProgressive::setSpeedFactor()
	 */
	void setSpeedFactor(float speedFactor);

protected:
	/**
	 * Hides the method AbstractProgressive::setDuration(), because the duration is
	 * determined by the animation file and cannot be changed afterwards. So this method
	 * is never called. If you want to have
	 * slowmotion use setSpeedFactor() with a value between 0 and 1.
	 */
	void setDuration(double duration);
	
	/// Character that signals the end of a string in the animation file
    static const char END_CHAR;

    /// Number of objects in the animation
	unsigned int objectNum;
	/// Array of ModelObjectAnimations (with size objectNum)
	ModelObjectAnimation *objectAnimations;
};

} // gl
} // managed
} // vs

#endif /*MODELANIMATION_H_*/
