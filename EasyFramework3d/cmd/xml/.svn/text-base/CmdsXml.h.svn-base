/**
 * @file CmdsXml.h
 * @author sizilium
 * @date 25.09.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef CMDS_XML_H
#define CMDS_XML_H

// includes
#include <vs/Build.hpp>
#include <vs/cmd/Command.hpp>
#include <string>

namespace vs
{
namespace cmd
{
namespace xml
{

class VS_EXPORT CmdClearXmlManager : public Command
{
public:
	CmdClearXmlManager() {}
	void execute();
	void undo();
	const std::string name() const { return "XmlManager cleared"; }
private:
};

class VS_EXPORT CmdDeleteXmlEntry : public Command
{
public:
	CmdDeleteXmlEntry(const std::string &entryName);
	void execute();
	void undo();
	const std::string name() const { return "xml entry deleted"; }
private:
	std::string entryName;
};

class VS_EXPORT CmdDeleteKnownXmlEntry : public Command
{
public:
	CmdDeleteKnownXmlEntry(const std::string &entryName);
	void execute();
	void undo();
	const std::string name() const { return "known xml entry deleted"; }
private:
	std::string entryName;
};

} // xml
} // cmd
} // vs

#endif  // CMDS_XML_H
