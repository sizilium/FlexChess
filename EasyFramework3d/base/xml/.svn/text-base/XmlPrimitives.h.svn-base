/**
 * @file XmlPrimitives.h
 * @author sizilium
 * @date 18.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XML_PRIMITIVES_H
#define XML_PRIMITIVES_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <vs/base/cont/Tree.hpp>

namespace vs
{
namespace base
{
namespace xml
{
// predeclaraions
class XmlTag;
class Value;
class Param;
class Comment;
class Header;
using namespace std;

VS_EXPORT ofstream& operator<<(ofstream &os, const Param &param);
VS_EXPORT ofstream& operator<<(ofstream &os, const Comment &comment);
VS_EXPORT ofstream& operator<<(ofstream &os, const Header &header);
VS_EXPORT ofstream& operator<<(ofstream &os, const Value &value);

VS_EXPORT ostream& operator<<(ostream &os, const Param &param);
VS_EXPORT ostream& operator<<(ostream &os, const Comment &comment);
VS_EXPORT ostream& operator<<(ostream &os, const Header &header);
VS_EXPORT ostream& operator<<(ostream &os, const Value &value);

VS_EXPORT ostream& operator<<(ostream &os, const XmlTag *tag);

/**
 * Little helper function. Simply returns a string beings with \n and ends with
 * n whitespaces.
 * @param space Number of whitespaces in the new line.
 * @return The new line string (useful for custom xml tags with more than one row).
 */
VS_EXPORT string newSpacedLine(int space);


//class XmlPrimitive
//{};

/** @class XmlTag
 * 
 */
class VS_EXPORT XmlTag
{
public:

	XmlTag()
	:space(0)
	{}
	virtual ~XmlTag()	{}
	
	// if Value
	virtual const string getName() const		{return "";}
	virtual const string getValue() const		{return "";}

	// if Param
	virtual const string getParamName() const	{return "";}	// if single param
	virtual const Param* getParam(const string &paramName) const	{return NULL;}
	virtual const vector<Param>* getParams() const			{return NULL;}
	
	// if Comment
	virtual const string getComment() const		{return "";}
	
	// if Header
	virtual const string getEncoding() const	{return "";}
	virtual const string getVersion() const		{return "";}
	
	// all custom XmlTag's must implements this!
	virtual void cout(ofstream &os) const = 0;
	virtual void cout(ostream &os) const = 0;
	
	// optional information when tag write in more than one row
	void setSpace(int space)	{this->space = space;}
	int getSpace() const		{return this->space;}
	
private:
	int space;
};

/**
 * 
 */
VS_EXPORT bool getXmlTag(const string &name, const base::cont::Tree<XmlTag*> *tree, XmlTag &tag);

// TODO getTagFromTree, first implement Variant
//ut::Variant getTagFromTree(ut::Tree<XmlTag*> *tree, const string &tagName);

/** @class Param
 * 
 */
class VS_EXPORT Param : public XmlTag
{
public:
	Param ();
	Param (const string &tagName, const string &paramName, const string &paramValue);
	Param (const string &paramName, const string &paramValue);

	const string getName() const;
	const string getParamName() const;
	const string getValue() const;
	
private:
	friend ofstream& operator<<(ofstream &os, const Param &param);
	friend ostream& operator<<(ostream &os, const Param &param);
	friend class Value;
	void cout(ofstream &os) const;	// if single tag
	void cout(ostream &os) const;	// ""
	void coutShort(ofstream &os) const;
	void coutShort(ostream &os) const;
	
	string name;	// if single param tag
	string paramName;
	string value;
};

class VS_EXPORT Value : public XmlTag
{
public:
	explicit Value ();
	explicit Value (const string &valueName, const string &value);
	Value (const string &valueName, const int value);
	explicit Value (const string &valueName, const double value);
	//explicit Value (const string &valueName, const bool value);
	explicit Value (const string &valueName, const Param &param, const string &value);
	explicit Value (const string &valueName, const vector<Param> params, const string &value);

	const string getName() const;
	const string getValue() const;
	const Param* getParam(const string &paramName) const;
	const vector<Param>* getParams() const;
	
private:
	friend ofstream& operator<<(ofstream &os, const Value &value);
	friend ostream& operator<<(ostream &os, const Value &value);
	void cout(ofstream &os) const;
	void cout(ostream &os) const;
	
	string name;
	vector<Param> params;
	string value;
};

class VS_EXPORT Comment : public XmlTag
{
public:
	Comment ();
	Comment (const string &comment);

	const string getComment() const;
	
private:
	friend ofstream& operator<<(ofstream &os, const Comment &comment);
	friend ostream& operator<<(ostream &os, const Comment &comment);
	void cout(ofstream &os) const;
	void cout(ostream &os) const;
	
	string comment;
};

class VS_EXPORT Header : public XmlTag
{
public:
	Header ();
	Header (const string &encoding, const string &version = "1.0");
	Header (const vector<Param> params);
	
	const string getEncoding() const;
	const string getVersion() const;
	
private:
	friend ofstream& operator<<(ofstream &os, const Header &header);
	friend ostream& operator<<(ostream &os, const Header &header);
	void cout(ofstream &os) const;
	void cout(ostream &os) const;
	
	vector<Param> params;
};

} // xml
} // base
} // vs

#endif  // XML_PRIMITIVES_H
