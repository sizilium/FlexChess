#include <vs/core/gl/GLException.h>
#include <sstream>
#include <GL/glu.h>

namespace vs
{
namespace core
{
namespace gl
{

using namespace std;

GLException::GLException(string errFile, string errFunc, GLenum errorCode) 
:Exception(errFile, errFunc, "OpenGL Errors detected:")
{
	genErrorDescription(errorCode);
}

GLException::GLException(string errFile, int errFunc, GLenum errorCode) 
:Exception(errFile, errFunc, "OpenGL Errors detected:")
{
	genErrorDescription(errorCode);
}

GLException::~GLException() throw()
{
}

void GLException::genErrorDescription(GLenum errorCode)
{
	int i = 0;
	ostringstream temp;
	while (errorCode != GL_NO_ERROR)
	{
		if (i == 10)
		{
			temp << endl << "More than "<< i << " OpenGL Errors detected!"<<endl
					<< "\tOnly the first "<< i << " were printed.";
		}
		temp << endl << "\t"<< gluErrorString(errorCode);

		errorCode = glGetError();
		i++;
	}
	errorDescription += temp.str();
}

} // gl
} // core
} // vs
