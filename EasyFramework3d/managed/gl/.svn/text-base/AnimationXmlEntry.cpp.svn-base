#include <vs/managed/gl/AnimationXmlEntry.h>
#include <vs/managed/gl/ModelAnimation.h>
#include <vs/managed/gl/AnimationFactory.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/managed/gl/model/ModelFactory.h>

namespace vs
{
namespace managed
{
namespace gl
{
using namespace core::gl;
using namespace base::xml;
using namespace base::interfaces;
using namespace base::cont;

AnimationXmlEntry::AnimationXmlEntry(const string &name, const string &path, ModelAnimation *animation)
:AbstractXmlEntry(name), path(path), ptr(animation)
{}

AbstractManaged* AnimationXmlEntry::read(const Tree<XmlTag*> *input)
{
	Tree<XmlTag*>::Const_Iterator it (input);
	while (it.hasNext())
	{
		if (it.current()->getName() == "vsa path")
			path = it.current()->getValue();
	}
	
	// TODO! create model first !!!
//	ManagedModel *model = modelFactory.createManagedModel(...);
	
//	AnimationFactory factory;
//	ModelAnimation *animation = factory.createAnimation(path, model);
//	return animation;
	
	return NULL;
}

void AnimationXmlEntry::write(Tree<XmlTag*> *tree)
{
	tree->add(new Value("vsa path", path));
	// TODO save animation
}

} // gl
} // managed
} // vs
