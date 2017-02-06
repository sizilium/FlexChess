#ifndef READFORMATIONXML_H_
#define READFORMATIONXML_H_

// includes
#include <vs/base/xml/XmlParser.h>
#include <vs/base/xml/XmlListener.h>
#include <vs/base/cont/Tree.hpp>
#include <string>

using namespace vs::base::cont;
using namespace vs::base::xml;
using namespace std;

// predeclarations
class Players;
class Player;
class Figures;

/**
 * Reads formation informations from a formation xml file and inits a players and a
 * figures object. The figures object will represent a pool of available figure objects.
 * See online documentation (wiki) for supported xml tags.
 */
class ReadFormationXml : public XmlListener
{
public:
	ReadFormationXml(Players *players, Figures *figures)
	:players(players), figures(figures)
	{
	}
	
	/**
	 * Reads and parses a xml file and inits players and figures object.
	 * @throw If there is a missing xml tag, a FlexChessException will be thrown.
	 */
	void read(const string &path);
	
	void notifyRead(const Tree<XmlTag*> *input);	
	void notifyWrite(Tree<XmlTag*> *fillTreeToWrite) {}
private:

	Players *players;
	Figures *figures;
};

#endif /*READFORMATIONXML_H_*/

