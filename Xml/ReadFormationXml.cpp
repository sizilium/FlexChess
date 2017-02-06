#include "ReadFormationXml.h"
#include "../FlexChessException.hpp"
#include "../Core/Board.h"
#include "../Core/Players.h"
#include "../Core/Player.h"
#include "../Core/Figures.h"
#include "../Core/Rules.h"
#include "../Core/Rule.h"
#include <vs/managed/gl/model/ModelFactory.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/base/util/FileException.h>
#include <vs/base/xml/XmlException.h>
#include <vs/base/xml/XmlParser.h>
#include <assert.h>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;


void ReadFormationXml::read(const string &path)
{
	try
	{
		XmlParser parser(path);
		parser.attach("place", this);
		parser.parse();
	}
	catch(FileException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch(XmlException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch(Exception &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch (...)
	{
		assert("Uncaught Exception!!" && false);
	}
}

void ReadFormationXml::notifyRead(const Tree<XmlTag*> *input)
{
	assert(players && figures);
	XmlTag *xmlTag;
	
	// parameter to fill
	string name;
	int x = -1, y = -1, playerId = -1;
	
	if (xmlTag = searchTag("name", input))
		name =  xmlTag->getValue();
	if (xmlTag = searchTag("playerId", input))
		playerId =  atoi(xmlTag->getValue().c_str());
	if (xmlTag = searchTag("x", input))
		x =  atoi(xmlTag->getValue().c_str());
	if (xmlTag = searchTag("y", input))
		y =  atoi(xmlTag->getValue().c_str());

	// check missing tags
	if (name.empty())
		throw FlexChessException(__FILE__, __LINE__, "Can't read formation xml. \"name\" Tag not found.");
	if (x == -1 || y == -1)
		throw FlexChessException(__FILE__, __LINE__, "Can't read formation xml. \"x\" or \"y\" Tag not found.");

	// search figure
	Figure *figure = figures->getFigure(name);
	if (!figure)
	{
		cerr << "Warning in ReadFormationXml: Figure does not exist in \"figures\" ..." << endl;
		return;
	}
	
	// set figure to all players
	if (playerId == -1)
	{
		vector<Player*> playerList = players->getAllPlayers();
		for (size_t i = 0; i < playerList.size(); i++)
		{
			// copy and update figure
			Figure *newFigure = new Figure(*figure);
			newFigure->setPlayerId(playerList.at(i)->getId());
			newFigure->createModel();
			newFigure->setPos(x, y, false);	// without animation

			// add figure to player
			playerList.at(i)->addFigure(newFigure);
		}
	}
	// set figure to specific player
	else
	{
		Player *player = players->getPlayer(playerId);
		if (player == NULL)
		{
			cerr << "Warning in ReadFormationXml: Player " << playerId << " does not exist. Figure not added." << endl;
			return;
		}
		else
		{
			// copy and update figure
			Figure *newFigure = new Figure(*figure);
			newFigure->setPlayerId(playerId);
			newFigure->createModel();
			newFigure->setPos(x, y, false);	// without animation

			// add figure to player
			player->addFigure(newFigure);
		}
	}
	

}
