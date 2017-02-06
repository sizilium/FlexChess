#include <vs/base/xml/XmlReader.h>
#include <iostream>
#include <stdio.h>

namespace vs
{
namespace base
{
namespace xml
{

XmlReader::XmlReader(ifstream &input)
{
	reset();
	
	this->fileInput = &input;
	isFileInput = true;
}

XmlReader::XmlReader(const string *input)
{
	reset();
	
	this->fileInput = NULL;
	this->stdInput = input->begin();
	this->stdInputEnd = input->end();
	isFileInput = false;
}

XmlReader::~XmlReader()
{
	fileInput = NULL;
}

bool XmlReader::hasNext() const
{
	if (isFileInput)
	{
		if (fileInput->eof())
			return false;
		else
			return true;
	}
	else
	{
		if (stdInput == stdInputEnd)
			return false;
		else
			return true;
	}
}


void XmlReader::init(int setLine, int setChar)
{
	this->currentLine = setLine;
	this->currentChar = setChar;
}

void XmlReader::reset()
{
	this->currentLine = 0;
	this->currentChar = 0;
}

int XmlReader::getCurrentLine() const
{
	return this->currentLine;
}

int XmlReader::getCurrentChar() const
{
	return this->currentChar;
}

XmlTag* XmlReader::readTag(bool &isStartTag, bool &isEndTag)
{
	string read;
	Param param;
	string::const_iterator it;
	
	// read next tag content in read
	readChars(read, ">");
	
	read.erase(--read.end());
	while (*read.begin() == ' ' || *read.begin() == '\t')		// erase whitespace & tab
		read.erase(read.begin());
	
	if (*read.begin() == '<')		// erase start token '<'
		read.erase(read.begin());
	
	// first token -> token
	char *tok;
	string token;
	char *expression = new char[read.size() + 1];
	strcpy(expression, read.c_str());
	expression[read.size()] = '\0';
	token = strtok(expression, " ");
	if (*token.begin() == '<')
		token.erase(token.begin());
	
	// check if header
	it = read.begin();
	
	if (*it == '?')
	{
		vector<Param> params;
		while ((tok = strtok(NULL, " ")))
		{
			param = readParam(tok);
			params.push_back(param);
		}
		
		isStartTag = false;
		isEndTag = false;
		delete expression;
		return new Header(params);
	}
	
	// check if comment
	if (*it == '!' && *(++it) == '-' && *(++it) == '-')
	{
		if (*(--token.end()) != '-' || *(--(--token.end())) != '-')
			throw XmlException(__FILE__, __LINE__, "Invalid xml comment! No \"--\" at end.", currentLine, currentChar);
		read.erase(0, 3);
		read.erase(--read.end());
		read.erase(--read.end());
		isStartTag = false;
		isEndTag = false;
		delete expression;
		return new Comment(read);
	}
	
	// check if single param
	if (*(--read.end()) == '/')
	{
		token.erase(--token.begin());
		
		Param param;
		vector<Param> params;
		
		isEndTag = false;
		isStartTag = false;
		delete expression;
		return new Value(token, params, "");
	}
	
	// check if value
	if (*it == '/')
	{
		token.erase(token.begin());
		
		isStartTag = false;
		isEndTag = true;
		delete expression;
		return new Value(token, ""); 
	}
	else
	{
		isStartTag = true;
		isEndTag = false;
	
		// read all parameters if exist
		vector<Param> params;
		while ((tok = strtok(0, " ")) && read.find("=") != std::string::npos)
		{
			param = readParam(tok);
			params.push_back(param);
		}
		
		read.clear();
		int checkNewLine = currentLine;
		readChars(read, "<");
		if (currentLine > checkNewLine)
			read.clear();
		else
			read.erase(--read.end());
		
		delete expression;
		return new Value(token, params, read);
	}
}

// ---------------------- private helper methods ----------------------------------

Param XmlReader::readParam(const string &readFrom)
{
	string paramName;
	string paramValue;
	
	string::const_iterator it;
	it = readFrom.begin();
	while (it != readFrom.end())
	{
		if (*it == '=')
			break;
		paramName += *it++;
	}
	if (it == readFrom.end())
		throw XmlException(__FILE__, __LINE__, "No = token found.", currentLine, currentChar);
	++it;
	if (*it != '\"')
		throw XmlException(__FILE__, __LINE__, "Expected \" token.", currentLine, currentChar);
	++it;
	while (it != readFrom.end())
	{
		if (*it == '\"')
			break;
		paramValue += *it++;
	}
	if (it == readFrom.end())
		throw XmlException(__FILE__, __LINE__, "No \"=\" token found.", currentLine, currentChar);

	return Param(paramName, paramValue);
}

void  XmlReader::readChars(string &puffer, int num)
{
	char c = '\0';
	for (int i = 0; i < num; i++)
	{
		try
		{
			c = getChar();
		}
		catch(XmlException &e)
		{
			e.addPlaceOfError(__FILE__, __LINE__);
			throw e;
		}
		
		puffer += c;
	}
	
}

void XmlReader::readChars(string &puffer, const string &toChars)
{
	char c = '\0';
	while (puffer.find(toChars) == std::string::npos)
	{
		try
		{
			c = getChar();
		}
		catch(XmlException &e)
		{
			e.addPlaceOfError(__FILE__, __LINE__);
			throw e;
		}
		
		puffer += c;
	}
}


char XmlReader::getChar()
{
	char c = '\0';
	
	if (isFileInput)
	{
		if (fileInput->eof())
		{
			XmlException e(__FILE__, __LINE__, "Invalid getChar operation! End of file.", currentLine, currentChar);
			e.endOfFile = true;
			throw e;
		}

		fileInput->get(c);
		++currentChar;

		if (c == '\n')
		{
			++currentLine;
			currentChar = 0;
			c = getChar();
		}
		
		return c;
	}
	else
	{
		if (stdInput == stdInputEnd)
		{
			XmlException e(__FILE__, __LINE__, "Invalid getChar operation! There is no char anymore.", currentLine, currentChar);
			e.endOfFile = true;
			throw e;
		}
		
		c = *stdInput;
		stdInput++;
		
		if (c == '\n')
		{
			++currentLine;
			currentChar = 0;
			c = getChar();
		}
		
		return c;
	}
}



} // xml
} // base
} // vs
