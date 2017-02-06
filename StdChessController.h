#ifndef STDCHESSCONTROLLER_H_
#define STDCHESSCONTROLLER_H_

// includes
#include "Controller.h"

// predeclarations
class Figure;

/**
 * This is a spezialized controller for the standard chess rules. The controller reimplements
 * the checkLooserId (king is important), checkMove and move method. The checkMove method
 * accounts special moves like king check, pawn's first move, castling kings side, castling
 * queens side and en passant. The move method calls the standard implementation and checks in a
 * post check if a pawn has reached the end of the board (in this case it will be replaced with
 * a queen figure).\n
 * The controller assumes that the figures named "king" (with id 1), "pawn" etc. are given.
 * The controller doesn't works well with other, user defined rules (given by xml files) or
 * other board size than 8 x 8. It's optimized for the normal standard chess rules.
 * @see Controller
 */
class StdChessController : public Controller
{
public:
	StdChessController();
	virtual ~StdChessController();
	
	/**
	 * Checks if the current player can perform any move. All active figures will be checked for
	 * any move. Remember that a king musn't be in check, the checkMove method will return false
	 * if the king is still in check.
	 * @return If a player can't move, the player id will returned, else -1.
	 */
	int checkLooserId() const;
	
	/**
	 * This method first verifies special chess rules like king check, pawn's first move, 
	 * castling kings side, castling queens side and en passant. Then the standart implementation
	 * will be called.
	 * @see Controller
	 */
	bool checkMove(int fromX, int fromY, int toX, int toY) const;
	
	/** 
	 * Calls the standard implementation and additional a post check:
	 * -# If a pawn is at the end of the board after the move, it will be replaced with a queen
	 * figure.
	 * -# If a king has made a castling, the rook will be placed aside the king.
	 */
	void move(int fromX, int fromY, int toX, int toY, bool noGraphic = false);
	
private:
	
	// verify king check
	bool checkKing(int fromX, int fromY, int toX, int toY) const;
	
	// check pawn first move
	bool checkPawn(Figure *figure, int fromX, int fromY, int toX, int toY) const;
	
	// check castling queen's side
	bool checkCastlingQueensSide(Figure *figure, int toX, int toY) const;
	
	// check castling king's side
	bool checkCastlingKingsSide(Figure *figure, int toX, int toY) const;
	
	// check en passant
	bool checkEnPassant(Figure *figure) const;
	
	// state changed after move? (for example pawn -> queen displacement)
	int postCheck(Figure *figure, int fromX, int fromY, int toX, int toY, bool noGraphic = false) const;

};

#endif /*STDCHESSCONTROLLER_H_*/
