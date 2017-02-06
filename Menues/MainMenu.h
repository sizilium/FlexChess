#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "StartGameMenu.h"
#include <vs/base/interfaces/MsgObserver.hpp>
#include "OptionsMenu.h"
using namespace vs::base::interfaces;
using namespace vs::core::gui;
using namespace std;


/**
 * Gui stuff.
 */
class MainMenu : public MsgObserver<Event>
{
public:
	MainMenu();
	
	void activate()				{startGameMenu.deactivate(); menuGroup.activate();}
	void deactivate()			{menuGroup.deactivate(); optionsMenu.deactivate();}
	void notify(Event &message);

	bool isActive() const		{return menuGroup.isActive() || optionsMenu.isActive();}

	Game *getGame() const		{return startGameMenu.getGame();}
	bool checkExit() const		{return exitButtonClicked;}
private:
	StartGameMenu startGameMenu;
	OptionsMenu optionsMenu;
	bool exitButtonClicked;
	DefaultManagedGroup menuGroup;
};


#endif /*MAINMENU_H_*/
