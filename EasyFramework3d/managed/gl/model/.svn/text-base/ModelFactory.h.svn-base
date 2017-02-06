/**
 * @file ModelFactory.h
 * @author sizilium
 * @date 10.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef MODELFACTORY_H
#define MODELFACTORY_H

// includes
#include <vs/Build.hpp>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <vs/base/interfaces/AbstractFactory.hpp>
#include <vs/managed/gl/model/ModelManager.h>
#include <iostream>

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{

using namespace std;

class ManagedModel;

/** 
 * Factory class to load and bind ManagedModels.
 */
class VS_EXPORT ModelFactory : 	public base::interfaces::AbstractFactory<ModelManager>,
								public base::xml::AbstractXmlFactory
{
public:
	ModelFactory();
	virtual ~ModelFactory();

	/**
	 * See AbstractFactory::getName()
	 */
	const string getName() const
	{
		return "ModelFactory";
	}

	/**
	 * Loads a model file and binds it to the current ModelManager. If the specified file 
	 * is already loaded the loaded data is simply copied without hard disk access.
	 * After calling loadModelFile() the ModelManager::renderQueue entry for the model is generated.
	 * @param[in] filename Filename of the model file to be loaded.
	 * @param[in] modelName Name of ManagedModel. If omitted filename is used.
	 * @param[in] customCenters If true the centers of the objects aren't stored in the
	 * display list but in the renderQueue.
	 * @param[in] customEulers  If true the eulers of the objects aren't stored in the
	 * display list but in the renderQueue.
	 * @param[in] customSizes  If true the sizes of the objects aren't stored in the
	 * display list but in the renderQueue.
	 * @param[in] customColors  If true the colors of the objects aren't stored in the
	 * display list but in the renderQueue.
	 * @return The loaded and bound ManagedModel.
	 * @note If you want to change for example the centerof a model object dynamically
	 * (after the call to this method) you have to pass true to customCenters. ModelAnimations
	 * require this for instance.
	 */
	ManagedModel* createManagedModel(const string &filename, const string &modelName = "",
									 bool customCenters = false, bool customEulers = false,
									 bool customSizes = false, bool customColors = false);

	/**
	 * See AbstractFactory::getNamespace()
	 */
	const string getNamespace() const
	{
		return "vs::managed::gl::model";
	}

private:
	/**
	 * Loads a model file and binds it to the current ModelManager (does the loading work
	 * and the storage in the maps of the ModelManager for createManagedModel()).
	 * If the specified file is already loaded the loaded data is simply copied without
	 * hard disk access.
	 * @param[in] filename Filename of the model file to be loaded.
	 * @param[out] modelIds Model object ids of the loaded model file.
	 * @return The loaded and bound ManagedModel.
	 */
	ManagedModel *loadModelFile(const string &filename);
};

} // model
} // gl
} // managed
} // vs

#endif  // MODELFACTORY_H
