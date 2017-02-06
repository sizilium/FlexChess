#ifndef RULES_H_
#define RULES_H_

// includes
#include "Rule.h"
#include<vector>
using namespace std;


/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * This class is a container for Rule objects. There are two sets of rules: move rules and 
 * attack move rules. There are getter and setter for both.\n
 * The class also provides the importants checkMove and checkAttackMove methods for checking
 * several moves.
 */
class Rules
{
public:
	Rules();
	virtual ~Rules();
	
	/**
	 * Adds a new move rule to the container.
	 * @param rule The new rule to add. Init first!
	 */
	void addMoveRule(Rule rule)		{moves.push_back(rule);}
	
	/**
	 * Adds a new attack move rule to the container.
	 * @param rule The new rule to add. Init first!
	 */
	void addAttackRule(Rule rule)	{attackMoves.push_back(rule);}
	
	/**
	 * Checks if there is a rule for given up, down, left, right distance. 
	 * @param up The number of fields the figure wants to go backward.
	 * @param down The number of fields the figure wants to go forward.
	 * @param left The number of fields the figure wants to go sideward.
	 * @param right The number of fields the figure wants to go sideward.
	 * @param withJump True if a move needed a jump ability (special figure ability).
	 * @param withHover TODO: not implemented yet.
	 */
	bool checkMove(short up, short down, short left, short right, bool withJump = false, bool withHover = false) const;
	
	/**
	 * Checks if there is a attack rule for given up, down, left, right distance. 
	 * @param up The number of fields the figure wants to go backward.
	 * @param down The number of fields the figure wants to go forward.
	 * @param left The number of fields the figure wants to go sideward.
	 * @param right The number of fields the figure wants to go sideward.
	 * @param withJump True if a move needed a jump ability (special figure ability).
	 * @param withHover TODO: not implemented yet.
	 */
	bool checkAttackMove(short up, short down, short left, short right, bool withJump = false, bool withHover = false) const;
	
	/**
	 * Gets a reference to the vector stored with move rules. Don't call the delete operator
	 * to the return pointer (note the const specifier). 
	 */
	const vector<Rule>* getMoves() const		{return &moves;}
	
	/**
	 * Gets a reference to the vector stored with attack move rules. Don't call the delete operator
	 * to the return pointer (note the const specifier). 
	 */
	const vector<Rule>* getAttackMoves() const	{return &attackMoves;}
	
	/**
	 * Print some informations to the std console (cout).
	 */
	void coutDebug() const;
	
private:
	bool check(const vector<Rule> &searchHere, short up, short down, short left, short right, bool withJump, bool withHover) const;
	
	vector<Rule> moves;
	vector<Rule> attackMoves;
};

#endif /*RULES_H_*/
