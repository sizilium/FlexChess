#include "ReadBoardXml.h"
#include "../FlexChessException.hpp"
#include "../Core/Board.h"
#include "../Core/Players.h"
#include "../Core/Player.h"
#include <vs/managed/gl/model/ModelFactory.h>
#include <vs/managed/gl/model/ManagedModel.h>
#include <vs/base/util/FileException.h>
#include <vs/base/xml/XmlException.h>
#include <vs/base/xml/XmlParser.h>
#include <assert.h>
#include <fstream>
#include <iostream>

using namespace vs::managed::gl::model;
using namespace vs::base::util;
using namespace std;


void ReadBoardXml::read(const string &path)
{
	try
	{
		XmlParser parser(path);
		parser.attach("board", this);
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

void ReadBoardXml::notifyRead(const Tree<XmlTag*> *input)
{
	int sizeX, sizeY;
	XmlTag *xmlTag;
	
	// init board
	if (xmlTag = searchTag("sizeX", input))
		sizeX =  atoi(xmlTag->getValue().c_str());
	else
		throw FlexChessException(__FILE__, __LINE__, "Can't read board xml. \"sizeX\" Tag not found!");
	
	if (xmlTag = searchTag("sizeY", input))
		sizeY = atoi(xmlTag->getValue().c_str());
	else
		throw FlexChessException(__FILE__, __LINE__, "Can't read board xml. \"sizeY\" Tag not found!");
	
	board->init(sizeX, sizeY);
	
	// try to load game board vsm. if not specified, create std vector game board
	if (xmlTag = searchTag("geometryA", input))
	{
		ModelFactory factory;
		unsigned int id;
		ManagedModel *model;

		bool toggle = false;
		int x;
		for (int y = 0; y < sizeY; y++)
		{
			if (toggle)
			{
				toggle = false;
				x = 0;
			}
			else
			{
				toggle = true;
				x = 1;
			}

			for (; x < sizeX; x += 2)
			{
				model = factory.createManagedModel(xmlTag->getValue(), "BoardGeometry", true, true, true);
				try
				{
					id = model->getObjectId("a");
				}
				catch (Exception &e)
				{
					e.printStackTrace();
					e.addPlaceOfError(__FILE__, __LINE__);
					throw e;
				}
				std::list<double>::iterator it = model->getObjCenterIt(id);
				*it++ = x;
				*it++ = y;
				*it = 0;
			}
		}

		if (xmlTag = searchTag("geometryB", input))
		{
			toggle = true;
			for (int y = 0; y < sizeY; y++)
			{
				if (toggle)
				{
					toggle = false;
					x = 0;
				}
				else
				{
					toggle = true;
					x = 1;
				}

				for (; x < sizeX; x += 2)
				{
					model = factory.createManagedModel(xmlTag->getValue(), "BoardGeometry", true, true, true);
					try
					{
						id = model->getObjectId("b");
					}
					catch (Exception &e)
					{
						e.printStackTrace();
						e.addPlaceOfError(__FILE__, __LINE__);
						throw e;
					}
					std::list<double>::iterator it = model->getObjCenterIt(id);
					*it++ = x;
					*it++ = y;
					*it = 0;
				}
			}
		}
		
	}
	else if (xmlTag = searchTag("geometry", input))
	{
		ModelFactory factory;
		try
		{
			factory.createManagedModel(xmlTag->getValue(), "BoardGeometry");
		}
		catch(FileException &e)
		{
			e.addPlaceOfError(__FILE__, __LINE__);
			throw e;
		}
		catch(...)
		{
			assert ("Uncaught Exception!" && false);
		}
	}
	else
	{
		// draw std vector field
		
	}
	
	// try to load environment vsm (optional)
	Tree<XmlTag*>::Const_Iterator it(input);
	string tag;
	do
	{
		if ((*it)->getName() == "environment")
		{
			ModelFactory factory;
			try
			{
				factory.createManagedModel((*it)->getValue(), "EnvironmentGeometry");
			}
			catch(FileException &e)
			{
				e.addPlaceOfError(__FILE__, __LINE__);
				throw e;
			}
			catch(...)
			{
				assert ("Uncaught Exception!" && false);
			}
		}
		// <playerReferenceCoords>
		else if ((*it)->getName() == "playerReferenceCoords")
		{
			if (it.hasChild())
			{
				it.goChild();
				do
				{
					// <<player>>
					if ((*it)->getName() == "player")
					{
						int id = -1, direction = -1, x = -1, y = -1;
						
						if (it.hasChild())
						{
							it.goChild();
							do
							{
								// <playerId>
								if ((*it)->getName() == "playerId")
									id = atoi((*it)->getValue().c_str());
								
								// <x>
								else if ((*it)->getName() == "x")
									x = atoi((*it)->getValue().c_str());
								
								// <y>
								else if ((*it)->getName() == "y")
									y = atoi((*it)->getValue().c_str());
								
								// <direction>
								else if ((*it)->getName() == "direction")
									direction = atoi((*it)->getValue().c_str());								
							
								it.nextSibling();
							}
							while(it.hasNextSibling());
							it.goParent();
							
							
							// setup player
							if (id == -1)
								throw FlexChessException(__FILE__, __LINE__, "Can't read board xml. \"playerId\" Tag not found.");
							if (x == -1)
								throw FlexChessException(__FILE__, __LINE__, "Can't read board xml. \"x\" Tag not found.");
							if (y == -1)
								throw FlexChessException(__FILE__, __LINE__, "Can't read board xml. \"y\" Tag not found.");
							if (direction == -1)
								throw FlexChessException(__FILE__, __LINE__, "Can't read board xml. \"direction\" Tag not found.");				
									
							if (players->getPlayer(id))
							{
								players->getPlayer(id)->setRefXY(x, y);
								players->getPlayer(id)->setDirection(direction);

								if (id == 0)
									players->getPlayer(id)->setColor(Color(1, 1, 1, 1));
								else if (id == 1)
									players->getPlayer(id)->setColor(Color(0.4, 0.4, 0.4, 1));
								else if (id == 2)
									players->getPlayer(id)->setColor(Color(0.3, 1, 0.3, 1));
								else if (id == 3)
									players->getPlayer(id)->setColor(Color(0.3, 0.3, 1, 1));
							}
						}										
					}
					it.nextSibling();
				} 
				while(it.hasNextSibling());
				
				it.goParent();
			}
			
			
		}
	
		it.nextSibling();
	}
	while(it.hasNextSibling());
	
}
