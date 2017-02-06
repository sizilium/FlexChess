#include <vs/cmd/CommandExecutor.h>
#include <vs/Context.h>
#include <algorithm>

namespace vs
{
namespace cmd
{
using namespace base::cont;
using namespace base::interfaces;
using namespace std;

CommandExecutor::CommandExecutor()
{
	blockCmds = false;
	executeImmediately = false;
	this->context = Context::getCurrentContext();
	bufferSize = 10;
	historySize = 20; 
}

CommandExecutor::~CommandExecutor()
{
	clear();
}

void CommandExecutor::setContext(Context *context)
{
	this->context = context;
}

void CommandExecutor::setCurrentContext()
{
	this->context = Context::getCurrentContext();
}

Context* CommandExecutor::getContext() const
{
	return this->context;
}

void CommandExecutor::execute()
{
	if (!context)
		return;
	
	// clear all redo commands
	while (!redoCommands.empty())
	{
		delete redoCommands.front();
		redoCommands.pop_front();
	}
	
	// execute next command
	if (!bufferCommands.empty())
	{
		// get next command from buffer
		Command *cmd = bufferCommands.front();
		bufferCommands.pop_front();
		
		// execute
		cmd->execute();

		// safe for undo and check historySize
		undoCommands.push_front(cmd);
		checkHistorySize();
		
		// notify Observer's
		notify();
	}
}

void CommandExecutor::executeAll()
{
	while (!bufferCommands.empty())
		execute();
}

bool CommandExecutor::enableExecuteImmediately(bool enable)
{
	bool retVal = executeImmediately;
	executeImmediately = enable;
	return retVal;
}

void CommandExecutor::addCommand(Command *newCommand)
{
	assert("You must set a context before adding commands!" && context != NULL);
	newCommand->setContext(context);
	
	if (!blockCmds)
	{
		bufferCommands.push_back(newCommand);
		
		if (executeImmediately)
			execute();
	}
}

namespace
{
	void deleteFromHeap(Command *cmd)
	{
		// Command is a Heap Tracked Object, so here we can check if the delete
		// operator is allowed or not.
		if (cmd->isOnHeap())
		{
			delete cmd;
			cmd = NULL;
		}
		// else: The command will be deleted automatically from the stack.
	}
}

void CommandExecutor::clear()
{
	for_each(bufferCommands.begin(), bufferCommands.end(), deleteFromHeap);
	bufferCommands.clear();
	for_each(undoCommands.begin(), undoCommands.end(), deleteFromHeap);
	undoCommands.clear();
	for_each(redoCommands.begin(), redoCommands.end(), deleteFromHeap);
	redoCommands.clear();
}

bool CommandExecutor::blockCommands(bool block)
{
	bool retVal = blockCmds;
	blockCmds = block;
	return retVal;
}

void CommandExecutor::setHistorySize(int historySize)
{
	assert("The history size must be greater than 0!" && historySize >= 0);
	this->historySize = historySize;
}

void CommandExecutor::setBufferSize(int bufferSize)
{
	assert("The buffer size must be greater than 0!" && bufferSize >= 0);
	this->bufferSize = bufferSize;
}

void CommandExecutor::undo()
{
	if (!undoCommands.empty())
	{
		// get last command
		Command *cmd = undoCommands.front();
		undoCommands.pop_front();
		
		// undo last command
		cmd->undo();
		
		// safe for redo
		redoCommands.push_front(cmd);
	}
}

void CommandExecutor::redo()
{
	if (!redoCommands.empty())
	{
		// get last redo command
		Command *cmd = redoCommands.front();
		redoCommands.pop_front();
	
		// execute over again
		cmd->execute();
		
		// safe for undo over again
		undoCommands.push_front(cmd);
		checkHistorySize();
	}
}

void CommandExecutor::checkHistorySize()
{
	if (undoCommands.size() > historySize)
	{
		delete undoCommands.back();
		undoCommands.pop_back();
	}
}

void CommandExecutor::getHistory(list<string> *historyList) const
{
	List<Command *>::Const_Iterator it(undoCommands);
	while (it.hasNext())
		historyList->push_back(it.next()->name());
}

} // cmd
} // vs
