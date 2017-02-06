#ifndef AI_1_H_
#define AI_1_H_

// includes
#include "AbstractAI.hpp"


/**
 * 
 */
class AI_1 : public AbstractAI
{
public:
	AI_1();
	virtual ~AI_1();
	
	void processMove(const Board *board, const Players *players, AbstractController *controller);

private:
	double checkBestMove(const Board *board, const Players *players, AbstractController *controller);
};


// ---------------------------------------------------------------------------------------------

/**
 * 
 */
double calcPointsFigures(const Players *players);

/**
 * 
 */
double calcPointsPosition(const Board *board, const Players *players, AbstractController *controller);

#endif	// AI_1_H_
