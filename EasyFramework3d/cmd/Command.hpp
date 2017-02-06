/**
 * @file Command.hpp
 * @author sizilium
 * @date 25.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_COMMAND_HPP
#define VS_COMMAND_HPP

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/Context.h>
#include <vs/base/util/HeapStuff.hpp>

namespace vs
{
namespace cmd
{

/** @class Command
 * Common interfaces for all commands. Commands can used by cmd's to perform action to
 * the EasyFramework (model). Each command must support an undo method(), so the commands
 * capsulates the undo informations.\n
 * All commands represents the controller in the mvc pattern.
 */
class VS_EXPORT Command : public base::util::HeapTracked<Command>
{
public:
	Command() { context = NULL; }
	virtual ~Command() {}
	
	/**
	 * Executes a command now.
	 */
	virtual void execute() = 0;
	
	/**
	 * Returns the name of the command. Usefull for cmd who list all actions (commands)
	 * in a history list for example.
	 */
	virtual const std::string name() const = 0;
	
	/**
	 * Undo the last command.
	 */
	virtual void undo() = 0;

	void setContext(Context *context) 	{ this->context = context; }
	Context* getContext() const			{ return context; }

private:
	Context *context;
};

} // cmd
} // vs

#endif  // VS_COMMAND_HPP
