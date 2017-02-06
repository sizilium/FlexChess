#include <vs/managed/gl/model/ManagedModelXmlEntry.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/managed/gl/model/ModelFactory.h>

namespace vs
{
namespace managed
{
namespace gl
{
namespace model
{

using namespace base::xml;
using namespace base::interfaces;
using namespace base::cont;


ManagedModelXmlEntry::ManagedModelXmlEntry(const string &name, const string &path, ManagedModel *model)
:AbstractXmlEntry(name), path(path), ptr(model)
{}

AbstractManaged* ManagedModelXmlEntry::read(const Tree<XmlTag*> *input)
{
	Tree<XmlTag*>::Const_Iterator it (input);
	while (it.hasNext())
	{
		if (it.current()->getName() == "vsm path")
			path = it.current()->getValue();
	}
	ModelFactory factory;
	ManagedModel *model = factory.createManagedModel(path);
	return model;
}

void ManagedModelXmlEntry::write(Tree<XmlTag*> *tree)
{
	tree->add(new Value("vsm path", path));
	// TODO save model
}

} // model
} // gl
} // managed
} // vs
