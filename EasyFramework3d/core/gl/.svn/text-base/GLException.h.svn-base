#ifndef GLEXCEPTION_H
#define GLEXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>
#include <GL/glu.h>
#include <GL/gl.h>

namespace vs
{
namespace core
{
namespace gl
{

class VS_EXPORT GLException : public base::util::Exception
{
public:
	GLException(std::string fileOfOccuredError, std::string placeOfOccuredError, GLenum errorCode);
	GLException(std::string fileOfOccuredError, int placeOfOccuredError, GLenum errorCode);
	virtual ~GLException() throw();
private:
	void genErrorDescription(GLenum errorCode);

};

} // gl
} // core
} // vs

#endif // GLEXCEPTION_H
