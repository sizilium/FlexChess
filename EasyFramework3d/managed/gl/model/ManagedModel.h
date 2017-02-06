/**
 * @file ManagedModel.h
 * @author maccesch
 * @date 26.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MANAGED_MODEL_H
#define MANAGED_MODEL_H

// includes
#include <vs/Build.hpp>
#include <vs/base/interfaces/AbstractManaged.h>
#include <vs/managed/gl/model/ModelManager.h>
#include <list>
#include <map>

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{

/**
 * Represents a loaded model, that is managed by a ModelManager object.
 * @see ModelManager
 */
class VS_EXPORT ManagedModel : public base::interfaces::AbstractManaged
{
	friend class ModelFactory;

public:
	ManagedModel();
	virtual ~ManagedModel();

	/**
	 * Gets an id for the model object with the name objectName.
	 * For an example see getObjColorIt().
	 * @param objectName
	 * The name of the object whose id is returned. For an VSM Model
	 * which was exported from Blender (www.blender.org) this name
	 * corresponds to the name of the Blender object.
	 * @throw Exception when the ManagedModel doesn't have an model object
	 * with the specified name.
	 */
	unsigned int getObjectId(std::string objectName);

	/**
	 * Activates the model. A model is drawn by the ModelManager if
	 * and only if it is activated.
	 * @see deactivate()
	 */
	void activate();
	/**
	 * Deactivates the model. A model is drawn by the ModelManager if
	 * and only if it is activated.
	 * @see activate(), isActive()
	 */
	void deactivate();

	// TODO : picking comfort methods to (de)activate all model objects

	/**
	 * Activates picking for the model object, i.e. makes it clickable
	 * @param objectId The id of the model object that is to be activated for picking
	 * @see deactivatePicking(), isActive(), isPickingActive()
	 */
	void activatePicking(unsigned int objectId)
	{
		unsigned int modes = static_cast<unsigned int>(*(objectIds2drawingModes[objectId]))
				| ModelManager::DRAWING_MODE_PICKING;
		*(objectIds2drawingModes[objectId]) = modes;
	}

	/**
	 * Deactivates picking for the model object.
	 * @param objectId The id of the model object that is to be deactivated for picking
	 * @see activatePicking(), isPickingActive()
	 */
	void deactivatePicking(unsigned int objectId)
	{
		*(objectIds2drawingModes[objectId])
				= static_cast<unsigned int>(*(objectIds2drawingModes[objectId]))
						& (~ModelManager::DRAWING_MODE_PICKING);
	}

	/**
	 * Returns true, if the model object is activated for picking, i.e. if it is clickable.
	 * @param objectId The id of the model object whose picking state is to be queried.
	 * @return Picking status of the model.
	 * @see activatePicking(), deactivatePicking()
	 */
	bool isPickingActive(unsigned int objectId) const
	{
		return static_cast<unsigned int>(*(const_cast<std::map<unsigned int, std::list<double>::iterator > &>(objectIds2drawingModes)[objectId])) & ModelManager::DRAWING_MODE_PICKING;
	}

	/**
	 * Returns true if the model is active. A model is drawn by the ModelManager if
	 * and only if it is activated.
	 * @return Activation status of the model.
	 * @see activate(), deactivate()
	 */
	bool isActive() const
	{
		return renderQueuePart.empty();
	}

	/**
	 * Sets the name.
	 */
	void setName(std::string name)
	{
		this->name = name;
	}
	/**
	 * Gets the name.
	 */
	std::string getName() const
	{
		return name;
	}

	/**
	 * Returns the path of the model. Its the one you passed to ModelFactory::createManagedModel().
	 */
	std::string getPath() const
	{
		return filename;
	}

	/**
	 * Returns an iterator to the renderQueue (@see ModelManager::renderQueue).
	 * The iterator points to the renderQueue entry where the first color
	 * component (red) ist located.
	 * @code
	 * // Example how to set the color of an object named
	 * // 'some_object' to deep blue.
	 * 
	 * ...
	 * ManagedModel *model = modelFactory.createManagedModel("some_file.vsm", "some_name");
	 * unsigned int objId = model->getObjectId("some_object");
	 * 
	 * std::list<double>::iterator it = model->getObjColorIt(objId);
	 * *it = 0.0;	// set red to 0.0
	 * ++it;
	 * *it = 0.0;	// set green to 0.0
	 * ++it;
	 * *it = 1.0;	// set blue to 1.0
	 * ++it;
	 * *it = 1.0;	// set alpha to 1.0
	 * @endcode
	 * 
	 * @param objectId
	 * The returned iterator points to the color which belongs to the object
	 * which has the id objectId.
	 * 
	 * @warning
	 * The returned iterator points to the first of four list<double> elements.
	 * Don't iterate any further than to the fourth element! No error will be
	 * reported but you might get really strange behaviour.
	 */
	std::list<double>::iterator getObjColorIt(unsigned int objectId);
	/**
	 * Pretty much the same as getObjColorIt
	 * except that the returned iterator points to the first value 
	 * of the center which only has three values (x, y, z).
	 *
	 * @warning
	 * The returned iterator points to the first of three list<double> elements.
	 * Don't iterate any further than to the third element! No error will be
	 * reported but you might get really strange behaviour.
	 */
	std::list<double>::iterator getObjCenterIt(unsigned int objectId);
	/**
	 * Pretty much the same as getObjColorIt
	 * except that the returned iterator points to the first value of
	 * the euler (angle_x, angle_y, angle_z). The Model is rotated first
	 * around the z axis (with angle_z), then around y, then around x. 
	 *
	 * @warning
	 * The returned iterator points to the first of four list<double> elements.
	 * Don't iterate any further than to the fourth element! No error will be
	 * reported but you might get really strange behaviour.
	 */
	std::list<double>::iterator getObjEulerIt(unsigned int objectId);
	/**
	 * Pretty much the same as getObjColorIt
	 * except that the returned iterator points to the first value 
	 * of the size (scale_x, scale_y, scale_z) that is the scalation
	 * factor.
	 *
	 * @warning
	 * The returned iterator points to the first of three list<double> elements.
	 * Don't iterate any further than to the third element! No error will be
	 * reported but you might get really strange behaviour.
	 */
	std::list<double>::iterator getObjSizeIt(unsigned int objectId);

private:

	/// The part of the ModelManager::renderQueue that is needed to draw this model.
	/// When the model is activated this list is sliced into the renderQueue and the
	/// other way round when it is deactivated.
	/// @see activate(), deactivate(), isActive(), renderQueueStart, renderQueueEnd
	std::list<double> renderQueuePart;
	std::list<double>::iterator renderQueueStart;
	std::list<double>::iterator renderQueueEnd;

	std::string name;
	std::string filename;

	std::map<unsigned int, std::list<double>::iterator > objectIds2iterators;
	std::map<unsigned int, std::list<double>::iterator > objectIds2drawingModes;

	ModelManager *manager; ///< pointer to the manager of this object

#ifndef NDEBUG
	bool customCenters;
	bool customRotations;
	bool customSizes;
	bool customColors;
#endif
};

} // model
} // gl
} // managed
} // vs

#endif
