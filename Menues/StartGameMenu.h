#ifndef STARTGAMEMENU_H_
#define STARTGAMEMENU_H_

// included
#include <iostream>
#include <vs/base/util/DefaultManagedGroup.h>
#include <vs/base/interfaces/MsgObserver.hpp>
#include <vs/core/gui/ButtonEvent.hpp>
#include <vs/core/gui/VectorButtonSimple.h>

// predeclarations
class Game;

using namespace vs::base::util;
using namespace vs::base::interfaces;
using namespace vs::core::gui;

/**
 * Gui stuff.
 * This class holds the game object.
 */
class StartGameMenu : public MsgObserver<Event>
{
public:
	StartGameMenu();
	~StartGameMenu();
	
	enum Config
	{
		off,
		human,
		ai_0,
		ai_1
	};
	
	void activate()			{menuGroup.activate();}
	void deactivate()		{menuGroup.deactivate();}
	void notify(Event &message);

	Game *getGame() const	{return game;}
	bool isActive() const	{return menuGroup.isActive();}

private:
	void refreshButtons();
	
	Game *game;
	enum Config player_1;
	enum Config player_2;
	enum Config player_3;
	enum Config player_4;

	DefaultManagedGroup menuGroup;
	
	VectorButtonSimple *pl_1_off, *pl_1_human, *pl_1_ai_0, *pl_1_ai_1;
	VectorButtonSimple *pl_2_off, *pl_2_human, *pl_2_ai_0, *pl_2_ai_1;
	VectorButtonSimple *pl_3_off, *pl_3_human, *pl_3_ai_0, *pl_3_ai_1;
	VectorButtonSimple *pl_4_off, *pl_4_human, *pl_4_ai_0, *pl_4_ai_1;
};

#endif /*STARTGAMEMENU_H_*/

