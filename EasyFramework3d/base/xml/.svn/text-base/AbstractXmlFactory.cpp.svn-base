#include <vs/base/xml/XmlManager.h>
#include <vs/base/xml/AbstractXmlFactory.h>
#include <vs/base/xml/AbstractXmlEntry.h>
#include <vs/base/cont/JavaStyleIterator.hpp>

namespace vs
{
namespace base
{
namespace xml
{

AbstractXmlFactory::AbstractXmlFactory()
{
	xmlLogging = true;
	manager = XmlManager::getCurrentManager();
}

void AbstractXmlFactory::enableXmlLogging(bool enable)
{
	xmlLogging = enable;
}

bool AbstractXmlFactory::isXmlLogging() const
{
	return xmlLogging;
}

void AbstractXmlFactory::setXmlManager(XmlManager *manager)
{
	this->manager = manager;
}

void AbstractXmlFactory::setCurrentXmlManager()
{
	XmlManager tmp;
	manager = tmp.getCurrentManager();
}

XmlManager* AbstractXmlFactory::getXmlManager() const
{
	return this->manager;
}

void AbstractXmlFactory::addXmlEntry(AbstractXmlEntry *entry)
{
	assert ("Can't add xml entry. There is no current xml manager!" && this->manager != NULL);
	if (xmlLogging)
		this->manager->addXmlEntry(entry);
}


} // xml
} // base
} // vs
