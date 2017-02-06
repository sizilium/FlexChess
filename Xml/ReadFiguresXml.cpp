#include "ReadFiguresXml.h"
#include "../FlexChessException.hpp"
#include "../Core/Players.h"
#include "../Core/Player.h"
#include "../Core/Figures.h"
#include "../Core/Rules.h"
#include "../Core/Rule.h"
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/base/util/FileException.h>
#include <vs/base/xml/XmlException.h>
#include <vs/base/xml/XmlParser.h>
#include <assert.h>
#include <fstream>
#include <iostream>

void ReadFiguresXml::read(const string &path)
{
	try
	{
		XmlParser parser(path);
		parser.attach("figure", this);	// read all figures
		parser.parse();
	}
	catch(FileException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch(XmlException &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch(Exception &e)
	{
		e.addPlaceOfError(__FILE__, __LINE__);
		throw e;
	}
	catch (...)
	{
		assert("Uncaught Exception!!" && false);
	}
}


void ReadFiguresXml::notifyRead(const Tree<XmlTag*> *input)
{
	assert(figures);
	
	// definitions
	Tree<XmlTag*>::Const_Iterator it(input);
	string tag;
	string param;

	// figure parameter (to fill)
	short id = -1;
	string name;
	string geometry;
	double weight = -1;
	Rules rules;
	
	// <figure>
	do
	{
		tag = (*it)->getName();
		
		// <name>
		if (tag == "name")
			name = (*it)->getValue();
		
		// <id>
		else if (tag == "id")
			id = atoi((*it)->getValue().c_str());
		
		// <geometry>
		else if (tag == "geometry")
			geometry = (*it)->getValue();
		
		// <weight>
		else if (tag == "weight")
			weight = atof((*it)->getValue().c_str());
		
		// <rules>
		else if (tag == "rules")
		{
			if (!it.hasChild())
				throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. No rule Tags not found!");

			it.goChild();
			do
			{
				bool jump = false, hover = false;
				short up = 0, down = 0, left = 0, right = 0;
				
				tag = (*it)->getName();
				
				// check parameter jump
				const Param *paramPtr = (*it)->getParam("jump");
				if (!paramPtr)
					throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. No parameter \"jump\" in Tag found!");
				param = paramPtr->getValue();
				if (param == "true")
					jump = true;

				// <move>
				if (tag == "move")
				{
					// check parameter hover (only for move)
					paramPtr = (*it)->getParam("hover");
					if (!paramPtr)
						throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. No parameter \"hover\" in move Tag found!");
					param = paramPtr->getValue();
					if (param == "true")
						hover = true;

					
					if (!it.hasChild())
						throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. No Tags for move rule found!");
					it.goChild();
					do
					{				
						tag = (*it)->getName();
						
						// read up
						if (tag == "up")
							up = atoi((*it)->getValue().c_str());

						// read down
						if (tag == "down")
							down = atoi((*it)->getValue().c_str());
						
						// read left
						if (tag == "left")
							left = atoi((*it)->getValue().c_str());
						
						// read right
						if (tag == "right")
							right = atoi((*it)->getValue().c_str());
										
						it.nextSibling();
					}
					while (it.hasNextSibling());
					
					rules.addMoveRule(Rule(up, down, left, right, jump, hover));
					
					it.goParent();
				} // </move>
				
				// <attackMove>
				else if (tag == "attackMove")
				{
					if (!it.hasChild())
						throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. No Tags for attack move rule found!");
					it.goChild();
					do
					{
						tag = (*it)->getName();
						
						// read up
						if (tag == "up")
							up = atoi((*it)->getValue().c_str());

						// read down
						if (tag == "down")
							down = atoi((*it)->getValue().c_str());
						
						// read left
						if (tag == "left")
							left = atoi((*it)->getValue().c_str());
						
						// read right
						if (tag == "right")
							right = atoi((*it)->getValue().c_str());
						
						it.nextSibling();
					}
					while (it.hasNextSibling());
					
					rules.addAttackRule(Rule(up, down, left, right, jump, hover));
					
					it.goParent();
				} // </attackMove>
									
				it.nextSibling();
			}
			while (it.hasNextSibling());
			it.goParent();
		} // </rules>

		it.nextSibling();
	} // </figure>
	while (it.hasNextSibling());

	
	// check missing tags
	if (name.empty())
		throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. \"name\" Tag not found!");
	if (geometry.empty())
		throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. \"geometry\" Tag not found!");
	if (weight == -1)
		throw FlexChessException(__FILE__, __LINE__, "Can't read figures xml. \"weight\" Tag not found!");			

	// create figure
	figures->addFigure(new Figure(name, geometry, weight, rules, id));
	
	
	//figures->coutDebug();	
}
