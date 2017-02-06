#include "Players.h"
#include "Player.h"
#include <iostream>

Players::Players()
:currentPlayerId(0)
{
}

Players::~Players()
{
	vector<Player*>::iterator it = players.begin();
	while (it != players.end())
		delete *it++;
}

Player* Players::getPlayer(int playerId) const
{
	vector<Player*>::const_iterator it = players.begin();
	while (it != players.end())
	{
		if ((*it)->getId() == playerId)
			return *it;
		++it;
	}
	return NULL;
}

void Players::killPlayer(int playerId)
{
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players.at(i)->getId() == playerId)
		{
			players.at(i)->markAsKilled();
			return;
		}
	}
	cerr << "Warning: Can't kill player with id " << playerId << "! No player found with this id." << endl;
}

vector<Player*> Players::getAllEnemyPlayers() const
{
	vector<Player*> retVector;
	for (size_t i = 0; i < players.size(); i++)
	{
		if (players.at(i)->getId() != currentPlayerId)
			retVector.push_back(players.at(i));
	}
	return retVector;
}

Player* Players::getCurrentPlayer() const
{
	if (players.empty())
		return NULL;
	else
		return players.at(currentPlayerId);
}

void Players::nextPlayer()
{
	// set next activ player (not killed)
	do
	{
		++currentPlayerId;
		if (currentPlayerId >= (int)players.size())
			currentPlayerId = 0;
	}
	while (players.at(currentPlayerId)->isKilled());
}

void Players::previousPlayer()
{
	// set previous activ player (not killed)
	do
	{
		--currentPlayerId;
		if (currentPlayerId < 0)
			currentPlayerId = players.size() - 1;
	}
	while (players.at(currentPlayerId)->isKilled());
}

bool Players::checkWinner() const
{
	int activPlayerCount = 0;
	for (size_t i = 0; i < players.size(); i++)
	{
		if (!players.at(i)->isKilled())
			activPlayerCount++;
	}
	
	if (activPlayerCount == 1)
		return true;
	else
		return false;
}

Player* Players::getWinner() const
{
	if (checkWinner())
	{
		for (size_t i = 0; i < players.size(); i++)
		{
			if (!players.at(i)->isKilled())
				return players.at(i);
		}
	}
	return NULL;
}

void Players::coutDebug() const
{
	cout << "currentPlayerId = " << currentPlayerId << endl;
	cout << "number of players = " << players.size() << endl;
}
