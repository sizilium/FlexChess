#ifndef ABSTRACTAI_H_
#define ABSTRACTAI_H_

// includes
#include "../Core/Board.h"
#include "../Core/Players.h"
#include "../AbstractController.hpp"


/**
 * To integrate new artifical intelligences, subclasses must implement this interface.
 * The processMove method will be called by a game object. All needed informations about the
 * game given by the parameter. So an algorithm can scan the game board with a board pointer,
 * or can scan the players with a players pointer. The move will processed with the controller.
 */
class AbstractAI
{
public:
	/*
	 * A precondition of this method is a move (accurately ONE move) performed by the controller.
	 * The ai of course can look up forward moves: Use the controllers undo method in this case!
	 * At the end only one move should be performed.
	 * @param board A pointer to the current game board. Useful to get some board informations.
	 * Do not change the board manually (note the const specifier).
	 * @param players A pointer to all players in the game. Do not change the players manually
	 * (note the const specifier).
	 * @param controller A pointer to the current controller. Use this to manipulate the board
	 * (with the controllers move method).
	 */
	virtual void processMove(const Board *board, const Players *players, AbstractController *controller) = 0;
	
};

#endif /*ABSTRACTAI_H_*/
