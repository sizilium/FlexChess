#ifndef INTERFACE_H_
#define INTERFACE_H_

// includes
#include "MainMenu.h"
#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/core/gui/VectorButtonSimple.h>
#include <vs/core/gl/Color.h>

// predeclarations
class Game;

using namespace vs::base::interfaces;
using namespace vs::core::gui;
using namespace vs::core::gl;

/**
 * Gui stuff.
 */
class Interface : public MsgObserver<Event>
{
public:
	Interface();
	
	void notify(Event &message);

	void addCursor(int x, int y);
	void setCursor(int x, int y);
	void pressCursor();
	pair<int, int> getMarkedCursor() const;
	pair<int, int> getCursor() const;
	
	void drawCursor() const;
	void showWinner();
	
	void reset();
	
	void exit()					{exitFlag = true;}
	Game *getGame() const		{return mainMenu.getGame();}
	bool checkExit() const		{return mainMenu.checkExit() || exitFlag;}
	
private:
	void checkCursor();

	MainMenu mainMenu;
	bool exitFlag;
	
	int cursorX, cursorY, markedCursorX, markedCursorY;
	Color cursorColor;

	bool showWinnerFlag;
	VectorButtonSimple *winnerButton;
};

#endif /*INTERFACE_H_*/
