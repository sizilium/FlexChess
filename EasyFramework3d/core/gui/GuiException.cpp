#include <vs/core/gui/GuiException.h>

namespace vs
{
namespace core
{
namespace gui
{
using namespace std;

GuiException::GuiException(string errFile, int errLine, string description)
:Exception(errFile, errLine, description)
{
}

GuiException::~GuiException() throw()
{
}

GuiFontException::GuiFontException(string errFile, int errLine, string description, string fontName)
:GuiException(errFile, errLine, description), fontName(fontName)
{
}

GuiFontException::GuiFontException(string errFile, int errLine, string description, int fontSize)
:GuiException(errFile, errLine, description), fontSize(fontSize)
{
}

GuiFontException::~GuiFontException() throw()
{
}

const char* GuiFontException::what() const throw()
{
	return GuiException::what();
}

} // gui
} // core
} // vs
