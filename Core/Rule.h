#ifndef RULE_H_
#define RULE_H_

/**
 * Warning: This is a flexchess core object. Do not call manipulating methods at runtime. 
 * Use the controller instead to keep internal data structures (pointers etc.).\n
 * 
 * The struct stores all information for a single rule, specified by the figures xml file. 
 * Each figure hold a set of rules (normal move rules and attack move rules). A rule describes
 * how much field in what direction the figure can move (relativ values, depends on the players
 * reference position and direction).\n
 * Note: Because this is a struct all values are public.
 */
struct Rule
{
	/**
	 * Constructor to init the rule values.
	 */
	Rule(short up, short down, short left, short right, bool jump = false, bool hover = false);

	/**
	 * Number of fields a figure can move to. By the std chess rules for example the king can
	 * move 1 field in each direction (up, up/left, left, left/down, down, down/right, right,
	 * right/up). The king also stores 8 rule structs (in particular 2 * 8 for move and attack).
	 */
	short up, down, left, right;
	
	/**
	 * Flag for jump ability of this rule. By the std chess rules for example only the knight
	 * has this ability (can jump over other figures!).
	 */
	bool jump;
	
	/**
	 * TODO
	 * Will be implemented in future...
	 */
	bool hover;
};

#endif /*RULE_H_*/
