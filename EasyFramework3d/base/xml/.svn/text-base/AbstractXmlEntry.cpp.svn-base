#include <vs/base/xml/AbstractXmlEntry.h>

namespace vs
{
namespace base
{
namespace xml
{
using namespace base::cont;

AbstractXmlEntry::AbstractXmlEntry(string name)
{
	this->name = name;
}

string AbstractXmlEntry::getName() const
{
	return this->name;
}

void AbstractXmlEntry::setName(string &name)
{
	this->name = name;
}

void AbstractXmlEntry::notifyRead(const Tree<XmlTag*> *input)
{
	read(input);
}

void AbstractXmlEntry::notifyWrite(Tree<XmlTag*> *fillTreeToWrite)
{
	write(fillTreeToWrite);
}

} // xml
} // base
} // vs
