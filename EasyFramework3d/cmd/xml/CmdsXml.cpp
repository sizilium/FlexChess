#include <vs/cmd/xml/CmdsXml.h>
#include <vs/base/xml/XmlManager.h>

namespace vs
{
namespace cmd
{
namespace xml
{
using namespace base::xml;

void CmdClearXmlManager::execute()
{
	if (getContext() && getContext()->isXmlManager())
		getContext()->getXmlManager()->clear();
}

void CmdClearXmlManager::undo()
{
	// possible?
}


CmdDeleteXmlEntry::CmdDeleteXmlEntry(const std::string &entryName)
:entryName(entryName)
{
	// TODO xml commands
}

void CmdDeleteXmlEntry::execute()
{

}

void CmdDeleteXmlEntry::undo()
{

}


CmdDeleteKnownXmlEntry::CmdDeleteKnownXmlEntry(const std::string &entryName)
:entryName(entryName)
{

}

void CmdDeleteKnownXmlEntry::execute()
{

}

void CmdDeleteKnownXmlEntry::undo()
{

}




} // xml
} // cmd
} // vs
