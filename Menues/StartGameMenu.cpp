#include "StartGameMenu.h"
#include "../StdChessController.h"
#include "../ArtificalIntelligence/AI_0.h"
#include "../ArtificalIntelligence/AI_1.h"
#include "../Game.h"

#include <vs/Context.h>
#include <vs/core/gui/AbstractButton.hpp>
#include <vs/core/gui/GuiException.h>
#include <vs/managed/gui/GuiManager.h>
#include <vs/managed/gui/GuiFactory.h>
#include <vs/managed/gl/OpenGlManager.h>
#include <vs/core/gl/Color.h>
#include <vs/core/gl/OpenGlSettings.h>
#include "Interface.h"

using namespace vs;
using namespace vs::core::gl;
using namespace vs::managed::gui;

extern Options options;
extern Interface *interface;

StartGameMenu::StartGameMenu()
:game(NULL), player_1(human), player_2(ai_1), player_3(off), player_4(off)
{
    GuiFactory gui;
	gui.setDefaultFontSize(30);

	VectorButtonSimple *startButton;
	VectorButtonSimple *pl_1, *pl_2, *pl_3, *pl_4;

    try
    {
    	// Start Button
    	menuGroup = startButton = (VectorButtonSimple*) gui.createButton("start", "OK", 500, 300, 500, 100);
    	startButton->setBackgroundColor(Color(0.5, 0.1, 0.1, 0.8));
    	startButton->attachEventHandler(this);
    	
    	// Player 1
    	menuGroup = pl_1 = (VectorButtonSimple*) gui.createButton("player_1", "Player 1:", 50, 900, 300, 70);
    	menuGroup = pl_1_off = (VectorButtonSimple*) gui.createButton("1_off", "Off", 50, 800, 300, 70);
    	menuGroup = pl_1_human = (VectorButtonSimple*) gui.createButton("1_human", "Human", 50, 700, 300, 70);
    	menuGroup = pl_1_ai_0 = (VectorButtonSimple*) gui.createButton("1_ai_0", "AI V 0.1", 50, 600, 300, 70);
    	menuGroup = pl_1_ai_1 = (VectorButtonSimple*) gui.createButton("1_ai_1", "AI V 1.0", 50, 500, 300, 70);
    	
    	pl_1_off->attachEventHandler(this);
    	pl_1_human->attachEventHandler(this);
    	pl_1_ai_0->attachEventHandler(this);
    	pl_1_ai_1->attachEventHandler(this);
    	
    	pl_1->setBackgroundColor(Color(0, 0, 0, 0));
    	pl_1->setBorderColor(Color(0, 0, 0, 0));
    	
    	// Player 2
    	menuGroup = pl_2 = (VectorButtonSimple*) gui.createButton("player_2", "Player 2:", 400, 900, 300, 70);
    	menuGroup = pl_2_off = (VectorButtonSimple*) gui.createButton("2_off", "Off", 400, 800, 300, 70);
    	menuGroup = pl_2_human = (VectorButtonSimple*) gui.createButton("2_human", "Human", 400, 700, 300, 70);
    	menuGroup = pl_2_ai_0 = (VectorButtonSimple*) gui.createButton("2_ai_0", "AI V 0.1", 400, 600, 300, 70);
    	menuGroup = pl_2_ai_1 = (VectorButtonSimple*) gui.createButton("2_ai_1", "AI V 1.0", 400, 500, 300, 70);
    	
    	pl_2_off->attachEventHandler(this);
    	pl_2_human->attachEventHandler(this);
    	pl_2_ai_0->attachEventHandler(this);
    	pl_2_ai_1->attachEventHandler(this);
    	
    	pl_2->setBackgroundColor(Color(0, 0, 0, 0));
    	pl_2->setBorderColor(Color(0, 0, 0, 0));
    	
       	// Player 3
    	menuGroup = pl_3 = (VectorButtonSimple*) gui.createButton("player_3", "Player 3:", 800, 900, 300, 70);
    	menuGroup = pl_3_off = (VectorButtonSimple*) gui.createButton("3_off", "Off", 800, 800, 300, 70);
    	menuGroup = pl_3_human = (VectorButtonSimple*) gui.createButton("3_human", "Human", 800, 700, 300, 70);
    	menuGroup = pl_3_ai_0 = (VectorButtonSimple*) gui.createButton("3_ai_0", "AI V 0.1", 800, 600, 300, 70);
    	menuGroup = pl_3_ai_1 = (VectorButtonSimple*) gui.createButton("3_ai_1", "AI V 1.0", 800, 500, 300, 70);
    	
//    	pl_3_off->attachEventHandler(this);
//    	pl_3_human->attachEventHandler(this);
//    	pl_3_ai_0->attachEventHandler(this);
//    	pl_3_ai_1->attachEventHandler(this);
    	
    	pl_3->setBackgroundColor(Color(0, 0, 0, 0));
    	pl_3->setBorderColor(Color(0, 0, 0, 0));
    
       	// Player 4
    	menuGroup = pl_4 = (VectorButtonSimple*) gui.createButton("player_4", "Player 4:", 1150, 900, 300, 70);
    	menuGroup = pl_4_off = (VectorButtonSimple*) gui.createButton("4_off", "Off", 1150, 800, 300, 70);
    	menuGroup = pl_4_human = (VectorButtonSimple*) gui.createButton("4_human", "Human", 1150, 700, 300, 70);
    	menuGroup = pl_4_ai_0 = (VectorButtonSimple*) gui.createButton("4_ai_0", "AI V 0.1", 1150, 600, 300, 70);
    	menuGroup = pl_4_ai_1 = (VectorButtonSimple*) gui.createButton("4_ai_1", "AI V 1.0", 1150, 500, 300, 70);
    	
//    	pl_4_off->attachEventHandler(this);
//    	pl_4_human->attachEventHandler(this);
//    	pl_4_ai_0->attachEventHandler(this);
//    	pl_4_ai_1->attachEventHandler(this);
    	
    	pl_4->setBackgroundColor(Color(0, 0, 0, 0));
    	pl_4->setBorderColor(Color(0, 0, 0, 0));
    	
    	menuGroup.deactivate();
    }
    catch(GuiException &e)
    {
    	e.printStackTrace();
    }
    
    // apply button colors
    refreshButtons();
}

StartGameMenu::~StartGameMenu()
{
	delete game;
}

void StartGameMenu::notify(Event &message)
{
	ButtonEvent *event = message.castTo<ButtonEvent>();
	if (event)
	{
		if (event->getName() == "start")
		{
			if (player_1 == off && player_2 == off && player_3 == off && player_4 == off)
				return;

			if (game)
			{
				delete game;
				Context::getCurrentContext()->getModelManager()->clear();
			}
			game = new Game;
			OpenGlSettings *settings = Context::getCurrentContext()->getOpenGlManager()->getOpenGlSettings();
			settings->setClearColor(Color(0.3, 0.3, 0.6));
			settings->applyToOpenGl();

			interface->reset();
			
			// player 1 (3=direction up)
			if (player_1 == human)
				game->addPlayer("Player 1");	
			else if (player_1 == ai_0)
				game->addPlayer("Player 1", new AI_0);
			else if (player_1 == ai_1)
				game->addPlayer("Player 1", new AI_1);

			// player 2 (1=direction down)
			if (player_2  == human)
				game->addPlayer("Player 2");	
			else if (player_2  == ai_0)
				game->addPlayer("Player 2", new AI_0);	
			else if (player_2 == ai_1)
				game->addPlayer("Player 2", new AI_1);	
			
			// player 3 (2=direction left)
			if (player_3 == human)
				game->addPlayer("Player 3");	
			else if (player_3 == ai_0)
				game->addPlayer("Player 3", new AI_0);	
			else if (player_3 == ai_1)
				game->addPlayer("Player 3", new AI_1);	
			
			// player 4 (0=direction right)
			if (player_4 == human)
				game->addPlayer("Player 4");
			else if (player_4 == ai_0)
				game->addPlayer("Player 4", new AI_0);
			else if (player_4 == ai_1)
				game->addPlayer("Player 4", new AI_1);
			
			game->loadXml("Data/Xml/figures.xml",
			              "Data/Xml/board.xml",
			              "Data/Xml/formation.xml");

			if (options.controllerType == stdChessController)
				game->setController(new StdChessController);
			else if (options.controllerType == controller)
				game->setController(new Controller);
			
			menuGroup.deactivate();
//			game->coutDebugBoard();
//			game->coutDebugFigures();
//			game->coutDebugPlayers();
		}
		else if (event->getName() == "1_off")
		{
			player_1 = off;
			refreshButtons();
		}
		else if (event->getName() == "1_human")
		{
			player_1 = human;
			refreshButtons();
		}
		else if (event->getName() == "1_ai_0")
		{
			player_1 = ai_0;
			refreshButtons();
		}
		else if (event->getName() == "1_ai_1")
		{
			player_1 = ai_1;
			refreshButtons();
		}
		
		else if (event->getName() == "2_off")
		{
			player_2 = off;
			refreshButtons();
		}
		else if (event->getName() == "2_human")
		{
			player_2 = human;
			refreshButtons();
		}
		else if (event->getName() == "2_ai_0")
		{
			player_2 = ai_0;
			refreshButtons();
		}
		else if (event->getName() == "2_ai_1")
		{
			player_2 = ai_1;
			refreshButtons();
		}
		
		else if (event->getName() == "3_off")
		{
			player_3 = off;
			refreshButtons();
		}
		else if (event->getName() == "3_human")
		{
			player_3 = human;
			refreshButtons();
		}
		else if (event->getName() == "3_ai_0")
		{
			player_3 = ai_0;
			refreshButtons();
		}
		else if (event->getName() == "3_ai_1")
		{
			player_3 = ai_1;
			refreshButtons();
		}
		
		else if (event->getName() == "4_off")
		{
			player_4 = off;
			refreshButtons();
		}
		else if (event->getName() == "4_human")
		{
			player_4 = human;
			refreshButtons();
		}
		else if (event->getName() == "4_ai_0")
		{
			player_4 = ai_0;
			refreshButtons();
		}
		else if (event->getName() == "4_ai_1")
		{
			player_4 = ai_1;
			refreshButtons();
		}
	}
}

void StartGameMenu::refreshButtons()
{
	// player 1
	player_1 == off ? 	pl_1_off->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_1_off->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_1 == human ? pl_1_human->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_1_human->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_1 == ai_0 ?	pl_1_ai_0->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_1_ai_0->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_1 == ai_1 ?	pl_1_ai_1->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_1_ai_1->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	
	// player 2
	player_2 == off ? 	pl_2_off->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_2_off->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_2 == human ? pl_2_human->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_2_human->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_2 == ai_0 ?	pl_2_ai_0->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_2_ai_0->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_2 == ai_1 ?	pl_2_ai_1->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_2_ai_1->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	
	// player 3
	player_3 == off ? 	pl_3_off->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_3_off->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_3 == human ? pl_3_human->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_3_human->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_3 == ai_0 ?	pl_3_ai_0->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_3_ai_0->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_3 == ai_1 ?	pl_3_ai_1->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_3_ai_1->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	
	// player 4
	player_4 == off ? 	pl_4_off->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_4_off->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_4 == human ? pl_4_human->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_4_human->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_4 == ai_0 ?	pl_4_ai_0->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_4_ai_0->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	player_4 == ai_1 ?	pl_4_ai_1->setBackgroundColor(Color(0.1, 0.1, 0.6, 0.8)) :
						pl_4_ai_1->setBackgroundColor(Color(0.3, 0.3, 0.3, 0.8));
	
	
}
