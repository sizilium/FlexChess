#ifndef READBOARDXML_H_
#define READBOARDXML_H_

// includes
#include <vs/base/xml/XmlParser.h>
#include <vs/base/xml/XmlListener.h>
#include <vs/base/cont/Tree.hpp>
#include <string>

using namespace vs::base::cont;
using namespace vs::base::xml;
using namespace std;

// predeclarations
class Board;
class Players;

/**
 * Reads board informations from a board xml file and inits a board and a players object.
 * See online documentation (wiki) for supported xml tags.
 */
class ReadBoardXml : public XmlListener
{
public:
	/**
	 * Pass a valid board and a players pointer to the constructor for initialisation.
	 */
	ReadBoardXml(Board *board, Players *players)
	:board(board), players(players)
	{
	}
	
	/**
	 * Reads and parses a xml file and inits the board and players object.
	 * @throw If there is a missing xml tag, a FlexChessException will be thrown.
	 */
	void read(const string &path);

	void notifyRead(const Tree<XmlTag*> *input);	
	void notifyWrite(Tree<XmlTag*> *fillTreeToWrite) {}
private:
	Board *board;
	Players *players;
};

#endif /*READBOARDXML_H_*/

