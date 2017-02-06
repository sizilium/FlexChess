/**
 * @file CommandExecutor.h
 * @author sizilium
 * @date 26.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

// includes
#include <vs/Build.hpp>
#include <vs/base/cont/List.hpp>
#include <vs/cmd/Command.hpp>
#include <vs/base/interfaces/Observable.hpp>
#include <list>
#include <string>

namespace vs
{
// predeclarations
class Context;

/**
 * The cmd namespace supports several cmd stuff like commands.
 * Because there should be a separation between the EasyFramework (model) and the cmd's
 * (view) you can use a lot of commands (controller) to perform all kind of actions.
 */
namespace cmd
{
using namespace std;
using namespace base::interfaces;

/** @class CommandExecutor
 * The command executor for cmd support provides a comfortable functionality for the
 * command pattern. By using a cmd (like Qt) there are three way's to manipulating the
 * model (the EasyFramework):
 * - You can change the model directly by using the vs factories to produce some stuff,
 * or manipulating the objects (model, sounds, constraints) by pointers etc.
 * - You can use the vs commands (unexceptional) and execute them manually
 * - You can use the vs commands with the CommandExecutor to get undo/redo functionality,
 * (see CmdHistoryWidget for Qt) and command buffering.
 * 
 * @code // Example
 * ... // set Context etc.
 * CommandExecutor cmdExecutor;    // automatically setted to the actual context
 * 
 * // add several commands
 * cmdExecutor->addCommand(new CmdEnableCullFace());
 * cmdExecutor->addCommand(new CmdEnableDepthTest());
 * cmdExecutor->addCommand(new CmdNewLight("light_1"));
 * 
 * cmdExecutor->execute();     // execute one
 * cmdExecutor->executeAll();  // execute all
 * 
 * // undo the last command
 * cmdExecutor->undo();
 * ...
 * 
 * @endcode
 * 
 * @see qt::CmdHistoryWidget
 */
class VS_EXPORT CommandExecutor : public base::interfaces::Observable
{
public:
	/**
	 * The constructor sets several default values:
	 * - History size: 20
	 * - Buffer size: 10
	 * - Immediately executing: false
	 * - Command blocking: false
	 * - Context: current context (if exists)
	 * 
	 */
	CommandExecutor();
	virtual ~CommandExecutor();
	
	/**
	 * Sets the context. All future commands adding to the CommandExecutor will get 
	 * the setted context!
	 */
	void setContext(vs::Context *context);
	
	/**
	 * Sets the current context. All future commands adding to the CommandExecutor will get 
	 * the setted context!
	 */
	void setCurrentContext();
	
	/**
	 * @return Gets the setted context. NULL if there is no context.
	 */
	Context* getContext() const;
	
	/**
	 * Executes the next command.
	 */
	void execute();
	
	/**
	 * Executes all commands in the command buffer.
	 */
	void executeAll();
	
	/**
	 * If this option is true (default is false) all commands will execute immediately
	 * Afer each addCommand() method. In this case the command buffer is unimportand.
	 * @param enable Pass true to enable the immediately executing functionality.
	 * @return The previous setted value.
	 */
	bool enableExecuteImmediately(bool enable);
	
	/**
	 * Adds a command to the CommandExecutor. Don't forget to execute it. Optionally
	 * you can use immediately executing functionality.
	 * @param newCommand Add a new command with new! It will be deleted automatically
	 * by the CommandExecutor.
	 * @see enableExecuteImmediately, execute, executeAll
	 */
	void addCommand(Command *newCommand);
	
	/**
	 * Clears all commands from buffer, history and internal redo list. You should call this
	 * method at times to prevent history or buffer overflow.
	 */
	void clear();
	
	/**
	 * If this option is true (default is false) the addCommand() method will be ignore.
	 * This might be useful for cmd in special cases.
	 * @param block Pass true to enable the command blocking.
	 * @return The previous setted value.
	 */
	bool blockCommands(bool block);
	
	/**
	 * Sets the number of commands saved in the history list. Note that a great list
	 * might allocate a lot of memory (dependent of the commands).
	 * @param historySize A value greater than 0. Default is 20.
	 */
	void setHistorySize(int historySize);
	
	/**
	 * Getter for history size (not actual filling).
	 * @return Maximum number of commands in history.
	 */
	int getHistorySize() const { return historySize; }
	
	/**
	 * Getter for actual command history count.
	 * @return Number of commands actually in history.
	 */
	int getNumHistory() const { return undoCommands.size(); }
	
	/**
	 * Sets the number of commands can buffered in the command buffer before executing. 
	 * Note that added commands will lost if the buffer is full. After an executing the buffer
	 * is already empty.
	 * @param bufferSize A value greater than 0.
	 */
	void setBufferSize(int bufferSize);
	
	/**
	 * Getter for buffer size (not actual fililng).
	 * @return Maximum number of commands in buffer.
	 */
	int getBufferSize() const	{ return bufferSize; }
	
	/**
	 * Undo the last command. If there are no more commands in the history, nothing
	 * happens.
	 */
	void undo();
	
	/**
	 * Redo the last undo command. If there are no more commands in the redo list,
	 * nothing happens.
	 */
	void redo();
	
	/**
	 * A getter method for the history. Each command are named! So you can get a list
	 * of strings representing the commands.
	 */
	void getHistory(list<string> *historyList) const;
	
private:
	bool blockCmds;
	bool executeImmediately;
	
	vs::Context *context;
	int bufferSize;
	int historySize;
	base::cont::List <Command *> bufferCommands;
	base::cont::List <Command *> undoCommands;
	base::cont::List <Command *> redoCommands;
	
	void checkHistorySize();
};

} // cmd
} // vs

#endif  // COMMAND_EXECUTOR_H
