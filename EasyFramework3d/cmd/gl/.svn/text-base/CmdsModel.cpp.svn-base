#include <vs/cmd/gl/CmdsModel.h>
#include <vs/Context.h>
#include <vs/managed/gl/model/ModelFactory.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/managed/gl/AnimationFactory.h>
#include <vs/managed/gl/AnimationManager.h>

namespace vs
{
namespace cmd
{
namespace gl
{
using namespace std;
using namespace managed::gl;
using namespace managed::gl::model;

CmdNewModel::CmdNewModel(const string &modelPath, const string &modelName)
{
	this->modelPath = modelPath;
	this->modelName = modelName;
}

void CmdNewModel::execute()
{
	if (getContext() && getContext()->isModelManager())
	{
		ModelFactory factory;
		factory.createManagedModel(modelPath, modelName);
	}
}

void CmdNewModel::undo()
{
	if (getContext() && getContext()->isModelManager())
	{
		getContext()->getModelManager()->removeManaged(modelName);
	}
}

CmdDeleteModel::CmdDeleteModel(const string &modelName)
{
	this->modelName = modelName;
}

void CmdDeleteModel::execute()
{
	if (getContext() && getContext()->isModelManager())
	{
		getContext()->getModelManager()->removeManaged(modelName);
	}
}

void CmdDeleteModel::undo()
{
	if (getContext() && getContext()->isModelManager())
	{
		ModelFactory factory;
		
		// TODO find path for vsm model
		string modelPath = "";
		
		factory.createManagedModel(modelPath, modelName);
	}
}


CmdNewModelWithAnimation::CmdNewModelWithAnimation(	const string &modelPath, 
                      	                         	const string &modelName,
                      	                         	const string &animationPath,
                      	                         	const string &animationName)
{
	this->modelPath = modelPath;
	this->modelName = modelName;
	this->animationPath = animationPath;
	this->animationName = animationName;
	
}

void CmdNewModelWithAnimation::execute()
{
	if (getContext() && getContext()->isModelManager() && getContext()->isAnimationManager())
	{
		ModelFactory factory;
		ManagedModel *model = factory.createManagedModel(modelPath, modelName, true, true, true, true);
		AnimationFactory animFactory;
		animFactory.createAnimation(animationPath, model, NULL, animationName);
	}
}

void CmdNewModelWithAnimation::undo()
{
	if (getContext() && getContext()->isModelManager())
	{
		getContext()->getModelManager()->removeManaged(modelName);
		getContext()->getAnimationManager()->removeManaged(animationName);
	}
}

void CmdClearModelManager::execute()
{
	if (getContext() && getContext()->isModelManager())
		getContext()->getModelManager()->clear();
}

void CmdClearModelManager::undo()
{
	// possible?
}



} // gl
} // cmd
} // vs
