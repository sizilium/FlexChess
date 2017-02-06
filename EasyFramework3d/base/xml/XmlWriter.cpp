#include <vs/base/xml/XmlWriter.h>

namespace vs
{
namespace base
{
namespace xml
{

XmlWriter::XmlWriter(XmlWriter *xmlWriter, const string &subGroupName, int spacing)
{
	xmlWriter->subMe(this);
	
	int tmp;
	if (spacing != -1)
	{
		tmp = spacing;
		assert("Invalid spacing!" && tmp >= 0);
	}
	else
		tmp = xmlWriter->writer->spacing;
		
	this->writer = new Writer(*xmlWriter->writer->output, subGroupName, xmlWriter->writer->space + tmp, tmp);

	sub = NULL;
	destruction = true;
}

XmlWriter::XmlWriter(ofstream &output, const string &groupName, int space, int spacing)
{
	assert("Invalid space or spacing!" && space >= 0 && spacing >= 0);

	sub = NULL;
	destruction = true;
	writer = new Writer(output, groupName, space, spacing);
}

XmlWriter::~XmlWriter()
{
	if (destruction)
	{
		if (writer != NULL)
		{
			delete writer;
			writer = NULL;
		}
	}
}

void XmlWriter::subMe(XmlWriter *sub)
{
	if (this->sub != NULL)
	{
		delete this->sub->writer;
		this->sub->writer = NULL;
		this->sub->destruction = false;
	}

	this->sub = sub;
}

void XmlWriter::operator<<(const XmlTag *tag)
{
	assert ("The writer is deleted (e.g. by subwriter?)!" &&  writer != NULL);
	*writer << const_cast<XmlTag*> (tag);
}
void XmlWriter::operator<<(const XmlTag &tag)
{
	assert ("The writer is deleted (e.g. by subwriter?)!" &&  writer != NULL);
	*writer << const_cast<XmlTag&> (tag);
}

void XmlWriter::newLine() const
{
	writer->newLine();
}


} // xml
} // base
} // vs
