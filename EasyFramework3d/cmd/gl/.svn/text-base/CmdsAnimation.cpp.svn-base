#include <vs/cmd/gl/CmdsAnimation.h>
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

CmdNewAnimation::CmdNewAnimation(const string &path, ManagedModel *model, const string &name)
:animationPath(path), model(model), animationName(name)
{
}

void CmdNewAnimation::execute()
{
	if (getContext() && getContext()->isAnimationManager())
	{
		AnimationFactory factory;
		factory.createAnimation(animationPath, model, NULL, animationName);
	}
}

void CmdNewAnimation::undo()
{
	if (getContext() && getContext()->isAnimationManager())
	{
		getContext()->getAnimationManager()->removeManaged(animationName);
	}
}


CmdDeleteAnimation::CmdDeleteAnimation(const string &name)
:animationName(name)
{
}

void CmdDeleteAnimation::execute()
{
	if (getContext() && getContext()->isAnimationManager())
	{
		getContext()->getAnimationManager()->removeManaged(animationName);
	}
}

void CmdDeleteAnimation::undo()
{
	// TODO undo vor delete animation
}

void CmdClearAnimationManager::execute()
{
	if (getContext() && getContext()->isAnimationManager())
		getContext()->getAnimationManager()->clear();
}

void CmdClearAnimationManager::undo()
{
	// i don't know if that is possible in an easy way
}


} // gl
} // cmd
} // vs
