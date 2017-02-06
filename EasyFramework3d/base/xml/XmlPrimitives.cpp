#include <vs/base/xml/XmlPrimitives.h>
#include <vs/base/math/Math.h>
#include <sstream>

namespace vs
{
namespace base
{
namespace xml
{
using namespace base::math;
using namespace base::cont;

// little help function
std::string newSpacedLine(int space)
{
	string retVal("\n");
	for (int i = 0; i < space; i++)
		retVal += " ";
	return retVal;
}

bool getXmlTag(const string &name, const Tree<XmlTag*> *tree, XmlTag &tag)
{
	Tree<XmlTag*>::Const_Iterator it (tree);

	while (it.hasNext())
	{
		// search for name
		if (it.current()->getName() == name)
		{
			tag = *it.current();
			return true;
		}
		it.next();
	}
	return false;
}


Param::Param() {}
Param::Param (const string &tagName, const string &paramName, const string &paramValue)
:name(tagName), paramName(paramName), value(paramValue)
{}

Param::Param (const string &paramName, const string &paramValue)
:name(""), paramName(paramName), value(paramValue)
{}

const string Param::getName() const
{
	return name;
}

const string Param::getParamName() const
{
	return paramName;
}

const string Param::getValue() const
{
	return value;
}

void Param::coutShort(ostream &os) const
{
	os << "" << getParamName() << "=\"" << getValue() << "\"";
}

void Param::coutShort(ofstream &os) const
{
	os << "" << getParamName() << "=\"" << getValue() << "\"";
}

void Param::cout(ostream &os) const
{
	assert("Wrong XML syntax! Param must have a tag name here" && getName() != "");
	os << '<' << getName() << ' ';
	coutShort(os);
	os << " />";
}

void Param::cout(ofstream &os) const
{
	assert("Wrong XML syntax! Param must have a tag name here" && getName() != "");
	os << '<' << getName() << ' ';
	coutShort(os);
	os << " />";
}

Value::Value() {}
Value::Value (const string &valueName, const string &value)
:name(valueName), value(value)
{}

Value::Value(const string &valueName, const int value)
:name(valueName)
{
	stringstream stream;
	stream << value;
	this->value = stream.str();
}

Value::Value(const string &valueName, const double value)
:name(valueName)
{
	this->value = doubleToString(value, 20);
}

//Value::Value(const string &valueName, const bool value)
//:name(valueName)
//{
//	if (value)
//		this->value = string("1");
//	else
//		this->value = string("0");	
//}

Value::Value (const string &valueName, const Param &param, const string &value)
:name(valueName),value(value)
{
	params.push_back(param);
}

Value::Value (const string &valueName, const vector<Param> params, const string &value)
:name(valueName), value(value)
{
	this->params = params;
}

const string Value::getName() const
{
	return name;
}

const string Value::getValue() const
{
	return value;
}

const Param* Value::getParam(const string &paramName) const
{
	for (size_t i = 0; i < params.size(); i++)
	{
		if (params.at(i).getParamName() == paramName)
			return &params.at(i);
	}
	return NULL;
}

const vector<Param>* Value::getParams() const
{
	return &params;
}

void Value::cout(ostream &os) const
{
	os << '<' << getName();
	
	// write params
	vector<Param>::const_iterator it;
	it = getParams()->begin();
	while (it != getParams()->end())
	{
		os << ' ';
		(*it++).coutShort(os);
	}
	
	os << '>' << getValue() << "</" << getName() << '>';
}

void Value::cout(ofstream &os) const
{
	os << '<' << getName();
	
	// write params
	vector<Param>::const_iterator it;
	it = getParams()->begin();
	while (it != getParams()->end())
	{
		os << ' ';
		(*it++).coutShort(os);
	}
	
	os << '>' << getValue() << "</" << getName() << '>';
}

Comment::Comment() {}
Comment::Comment (const string &comment)
:comment(comment)
{}

const string Comment::getComment() const
{
	return comment;
}

void Comment::cout(ostream &os) const
{
	os << "<!-- " << getComment() << " -->";
}

void Comment::cout(ofstream &os) const
{
	os << "<!-- " << getComment() << " -->";
}

Header::Header() {}
Header::Header (const string &encoding, const string &version)
{
	Param tmp_1("encoding", encoding);
	params.push_back(tmp_1);
	Param tmp_2("version", version);
	params.push_back(tmp_2);
	
}

Header::Header(const vector<Param> params)
{
	this->params = params;
}

const string Header::getEncoding() const
{
	vector<Param>::const_iterator it;
	it = params.begin();
	while (it != params.end())
	{
		if ((*it).getParamName() == "encoding")
			return (*it).getValue();
		++it;
	}
	return "";
}

const string Header::getVersion() const
{
	vector<Param>::const_iterator it;
	it = params.begin();
	while (it != params.end())
	{
		if ((*it).getParamName() == "version")
			return (*it).getValue();
		++it;
	}
	return "";
}

void Header::cout(ostream &os) const
{
	os << "<?xml version=\"" << getVersion() << "\" encoding=\"" << getEncoding() << "\"?>";
}

void Header::cout(ofstream &os) const
{
	os << "<?xml version=\"" << getVersion() << "\" encoding=\"" << getEncoding() << "\"?>";
}

// ----------------------------------------------------------------------------------


ofstream& operator<<(ofstream &os, const Param &param)
{
	param.cout(os);
	os << endl;
	return os;
}

ofstream& operator<<(ofstream &os, const Value &value)
{
	value.cout(os);
	os << endl;
	return os;
}

ofstream& operator<<(ofstream &os, const Comment &comment)
{
	comment.cout(os);
	os << endl;
	return os;
}

ofstream& operator<<(ofstream &os, const Header &header)
{
	header.cout(os);
	os << endl;
	return os;
}


ostream& operator<<(ostream &os, const Param &param)
{
	param.cout(os);
	os << endl;
	return os;
}

ostream& operator<<(ostream &os, const Value &value)
{
	value.cout(os);
	os << endl;
	return os;
}

ostream& operator<<(ostream &os, const Comment &comment)
{
	comment.cout(os);
	os << endl;
	return os;
}

ostream& operator<<(ostream &os, const Header &header)
{
	header.cout(os);
	os << endl;
	return os;
}


ostream& operator<<(ostream &os, const XmlTag *tag)
{
	tag->cout(os);
	os << endl;
	return os;
}


} // xml
} // base
} // vs
