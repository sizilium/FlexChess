/**
 * @file XmlWriter.h
 * @author sizilium
 * @date 15.06.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef XMLWRITER_H
#define XMLWRITER_H

// includes
#include <vs/Build.hpp>
#include <fstream>
#include <vs/base/xml/XmlPrimitives.h>
#include <vs/base/cont/Tree.hpp>

namespace vs
{
namespace base
{
namespace xml
{
using namespace base::cont;
using namespace std;

/** @class XmlWriter
 * 
 */
class VS_EXPORT XmlWriter
{
	class Writer
	{
	public:
		friend class XmlWriter;

		Writer(ofstream &output, const string &groupName, int space, int spacing)
		:groupName(groupName), space(space), spacing(spacing)
		{
			this->output = &output;
			
			// start group
			if (groupName != "")
			{
				writeSpace(space);
				output << '<' << groupName << '>' << endl;
			}
		}
		~Writer()
		{
			// end group
			if (groupName != "")
			{
				writeSpace(space);
				*output << "</" << groupName << '>' << endl;
			}
		}
		
		void newLine() const
		{
			*output << endl;
		}
		void operator<<(XmlTag *tag)
		{
			// tag needs space information whe write in two or more rows
			tag->setSpace(space + spacing);
			writeSpace(space + spacing);
			*output << tag;
		}
		void operator<<(XmlTag &tag)
		{
			// tag needs space information whe write in two or more rows
			tag.setSpace(space + spacing);
			writeSpace(space + spacing);
			*output << &tag;
		}
		void operator<<(Tree<XmlTag*> &tree)
		{
			if (tree.isEmpty())
				return;
			Tree<XmlTag*>::Iterator it(tree);
			XmlWriter writer(*output, "", this->space + this->spacing, this->spacing);
			writeTree(writer, it);
		}
		
	private:
		// recursive
		void writeTree(XmlWriter &writer, Tree<XmlTag*>::Iterator &it)
		{
			if (!it.hasNext())
				return;
			
			if (it.hasChild())
			{
				XmlWriter subWriter(&writer, (*it)->getName(), this->spacing);
				it.next();
				writeTree(subWriter, it);
			}
			else
			{
				//writeSpace(writer.space + writer.spacing);
				writer << *it++;
				writeTree(writer, it);
			}
			
		}
		
		void writeSpace(int spaces)
		{
			for (int i = 0; i < spaces; i++)
				*output << ' ';
		}
		string groupName;
		
		ofstream *output;
		int space;
		int spacing;
	};
	
	XmlWriter *sub;
	Writer *writer;
	bool destruction;
	
public:
	XmlWriter(XmlWriter *xmlWriter, const string &subGroupName, int spacing = -1);
	XmlWriter(ofstream &output, const string &groupName, int space = 0, int spacing = 4);
	~XmlWriter();

	void subMe(XmlWriter *sub);

	void operator<<(const XmlTag *);
	void operator<<(const XmlTag &);
	void operator<<(Tree<XmlTag*> &tree)
	{
		assert ("The writer is deleted (e.g. by subwriter?)!" &&  writer != NULL);	// todo?
		*writer << tree;
	}
	void newLine() const;
};

} // xml
} // base
} // vs

#endif  // XMLWRITER_H
