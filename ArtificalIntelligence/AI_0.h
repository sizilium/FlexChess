#ifndef AI_0_H_
#define AI_0_H_

// includes
#include "AbstractAI.hpp"

/**
 * This is not really an artifical intelligence. It's only a random generator for testing and
 * debuging. It's the least ai. Your algorithm should beat this ai :-)
 */
class AI_0 : public AbstractAI
{
public:
	/**
	 * The constructor shuffles the random generator with a time function.
	 */
	AI_0();
	virtual ~AI_0();
	
	/**
	 * The method picks an active random figure, tries a random position to move and moves if
	 * possible. Else another figure and position will be tried ...
	 */
	void processMove(const Board *board, const Players *players, AbstractController *controller);
};


#endif /*AI_0_H_*/
