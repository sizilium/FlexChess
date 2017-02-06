#include <vs/managed/gl/model/ModelFactory.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/managed/gl/model/ManagedModelXmlEntry.h>
#include <vs/base/util/FileException.h>
#include <vs/base/util/Exception.h>
#include <vs/core/gl/GLException.h>
#include <memory>
#include <vs/core/gl/model/ModelData.h>
#include <vs/core/gl/model/TexNamesExtractor.h>
#include <vs/core/gl/model/ModelLoader.h>
#include <sstream>
#include <vs/managed/gl/model/ManagedModelBinder.h>
#include <vs/core/gl/TextureManager.h>

using namespace vs::core::gl::model;

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{
using namespace core::gl;
using namespace base::util;

ModelFactory::ModelFactory()
{
}

ModelFactory::~ModelFactory()
{
}

ManagedModel *ModelFactory::loadModelFile(const string &filename)
{
	assert("Filenames must not contain backslashes. Use slashed instead. " && filename.find('\\') > filename.length());

	ManagedModel *model = new ManagedModel;

	try
	{
		ModelManager *modelManager = ModelManager::getCurrentManager();
		model->manager = modelManager;
		if (modelManager->filenames2models.count(filename) == 0)
		{
			// TODO : optimize: create these objects only once per loading period
			// (maybe there will be a loading manager)
			ModelLoader modelLoader;
			TexNamesExtractor texNamesExtractor;

			ModelData modelData;
			modelLoader.load(filename, modelData);

			// TODO : optimize this
			set<string> textures = texNamesExtractor.extractTexNames(modelData);
			list<string> texturePaths;
			// prefix every texture with the model path => textures have the same root directory
			// as model
			for (set<string>::iterator it = textures.begin(); it != textures.end(); ++it)
			{
				ostringstream s;
				if (modelData.path != "")
				s << modelData.path << '/';
				s << *it;

				texturePaths.push_back(s.str());
			}

			// TODO : Optimize model that are often drawn together (by learning system)
			core::gl::textureManager.loadTextures(texturePaths);

			ManagedModelBinder modelBinder;
			modelBinder.bind(modelData);
		}
	}
	catch (base::util::FileException &e)
	{
		delete model;
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch(...)
	{
		assert ("Uncaught Exception!" && false);
	}

	return model;
}

ManagedModel* ModelFactory::createManagedModel(const string &filename, const string &modelName,
											   bool customCenters, bool customRotations,
											   bool customSizes, bool customColors)
{
	ManagedModel *model = NULL;

	// TODO : take custom... Variables into account

	try
	{
		model = loadModelFile(filename);
	}
	catch (base::util::Exception &e)
	{
		delete model;
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}

#ifndef NDEBUG
	model->customCenters = customCenters;
	model->customRotations = customRotations;
	model->customSizes = customSizes;
	model->customColors = customColors;
#endif
	// TODO? : Use filename always as name? If so remove get/setName etc from ManagedModel as well.
	model->filename = filename;
	if (modelName == "")
		model->name = filename;
	else
		model->name = modelName;
	
	ModelManager *modelManager = ModelManager::getCurrentManager();
	vector<unsigned int> &modelIds = modelManager->filenames2models[filename];
	list<double>::iterator drawingModes;
	for (unsigned int i = 0; i < modelIds.size(); i++)
	{
		modelManager->enqueuePush();

		model->objectIds2iterators[modelIds[i]] = modelManager->renderQueue.end();
		--(model->objectIds2iterators[modelIds[i]]);

		modelManager->enqueueTranslation(modelManager->getModelCenter(modelIds[i]));
		modelManager->enqueueEuler(modelManager->getModelEuler(modelIds[i]));
		modelManager->enqueueScalation(modelManager->getModelSize(modelIds[i]));
		modelManager->enqueueColor(modelManager->getModelColor(modelIds[i]));
		drawingModes = modelManager->renderQueue.end();
		--(drawingModes);
		modelManager->enqueueDraw(modelIds[i]);
		modelManager->enqueuePop();
		++++(drawingModes);
		model->objectIds2drawingModes[modelIds[i]] = drawingModes;
	}

	model->renderQueueStart = model->objectIds2iterators[modelIds[0]];
	model->renderQueueEnd = ModelManager::getCurrentManager()->renderQueue.end();
	--(model->renderQueueEnd);

	ModelManager::getCurrentManager()->addManaged(model);

	// from AbstractXmlFactory
	this->addXmlEntry(new ManagedModelXmlEntry(modelName, filename, model));

	return model;
}

} // model
} // gl
} // managed
} // vs
