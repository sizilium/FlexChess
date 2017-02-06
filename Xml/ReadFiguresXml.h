#ifndef READFIGURESXML_H_
#define READFIGURESXML_H_

// includes
#include <vs/base/xml/XmlParser.h>
#include <vs/base/xml/XmlListener.h>
#include <vs/base/cont/Tree.hpp>
#include <string>

using namespace vs::base::cont;
using namespace vs::base::xml;
using namespace std;

// predeclarations
class Figures;

/**
 * Reads figures informations from a figures xml file and inits a figures object. The figures
 * object will represent a pool of available figure objects.
 * See online documentation (wiki) for supported xml tags.
 */
class ReadFiguresXml : public XmlListener
{
public:
	ReadFiguresXml(Figures *figures)
	:figures(figures)
	{
	}
	
	/**
	 * Reads and parses a xml file and inits the figures object.
	 * @throw If there is a missing xml tag, a FlexChessException will be thrown.
	 */
	void read(const string &path);
	
	void notifyRead(const Tree<XmlTag*> *input);	
	void notifyWrite(Tree<XmlTag*> *fillTreeToWrite) {}
private:
	Figures *figures;
};

#endif /*READFIGURESXML_H_*/

