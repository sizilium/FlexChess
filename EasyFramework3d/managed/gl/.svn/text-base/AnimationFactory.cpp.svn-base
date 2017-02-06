#include <vs/managed/gl/AnimationFactory.h>
#include <vs/managed/gl/ModelAnimation.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/managed/gl/AnimationXmlEntry.h>
#include <memory>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace std;
using namespace model;
using namespace base::util;

AnimationFactory::AnimationFactory()
{
}

AnimationFactory::~AnimationFactory()
{
}

ModelAnimation* AnimationFactory::createAnimation (const string &vsa_path, 
                                                   ManagedModel *model,
                                                   const map<string, string> *objNameAdapter,
                                                   const string &name)
{
	ModelAnimation *animation = new ModelAnimation;
	try
	{
		animation->load(vsa_path, *model);
	} 
	catch (base::util::FileException &e)
	{
		delete animation;
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch (base::util::Exception &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	
	// TODO : if name == "" use vsa_path. See ManagedModel.
	animation->setName(name);

	// from AbstractAnimationFactory
	this->addAnimation(animation);
	
	// from AbstractXmlFactory
	this->addXmlEntry(new AnimationXmlEntry(name, vsa_path, animation));

	return animation;
}

} // gl
} // managed
} // vs
