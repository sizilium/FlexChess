#include <vs/managed/al/OggException.h>

namespace vs
{
namespace managed
{
namespace al
{

OggException::OggException(string errFile, string errFunc, string desc, int err)
		: Exception(errFile, errFunc, desc)
{
	errorCode = err;
}

OggException::OggException(string errFile, int errFunc, string desc, int err)
		: Exception(errFile, errFunc, desc)
{
	errorCode = err;
}

OggException::~OggException() throw()
{}


string OggException::getErrorString() const
{
	switch (errorCode)
	{
	case OV_EREAD:
		return string("Read from media.");
	case OV_ENOTVORBIS:
		return string("Not Vorbis data.");
	case OV_EVERSION:
		return string("Vorbis version mismatch.");
	case OV_EBADHEADER:
		return string("Invalid Vorbis header.");
	case OV_EFAULT:
		return string("Internal logic fault (bug or heap/stack corruption.");
	default:
		return string("Unknown Ogg error.");
	}
}

} // al
} // managed
} // vs
