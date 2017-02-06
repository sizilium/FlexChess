#include <vs/managed/al/ALException.h>

namespace vs
{
namespace managed
{
namespace al
{

ALException::ALException(string errFile, string errFunc, string desc, ALenum alErr, Type type)
		: Exception(errFile, errFunc, desc)
{
	errorCode = alErr;
	alType = type;
}

ALException::ALException(string errFile, int errFunc, string desc, ALenum alErr, Type type)
		: Exception(errFile, errFunc, desc)
{
	errorCode = alErr;
	alType = type;
}

ALException::~ALException() throw()
{}


string ALException::getErrorString() const
{
	switch (alType)
	{
	case AL_ERROR:

		switch (errorCode)
		{
		case AL_NO_ERROR:
			return string("AL_NO_ERROR");
			break;

		case AL_INVALID_NAME:
			return string("AL_INVALID_NAME");
			break;

		case AL_INVALID_ENUM:
			return string("AL_INVALID_ENUM");
			break;

		case AL_INVALID_VALUE:
			return string("AL_INVALID_VALUE");
			break;

		case AL_INVALID_OPERATION:
			return string("AL_INVALID_OPERATION");
			break;

		case AL_OUT_OF_MEMORY:
			return string("AL_OUT_OF_MEMORY");
			break;

			break;
		};

	case ALC_ERROR:

		switch (errorCode)
		{
		case ALC_NO_ERROR:
			return string("AL_NO_ERROR");
			break;

		case ALC_INVALID_DEVICE:
			return string("ALC_INVALID_DEVICE");
			break;

		case ALC_INVALID_CONTEXT:
			return string("ALC_INVALID_CONTEXT");
			break;

		case ALC_INVALID_ENUM:
			return string("ALC_INVALID_ENUM");
			break;

		case ALC_INVALID_VALUE:
			return string("ALC_INVALID_VALUE");
			break;

		case ALC_OUT_OF_MEMORY:
			return string("ALC_OUT_OF_MEMORY");
			break;

			break;
		};

	case ALUT_ERROR:

		return alutGetErrorString (errorCode);

		break;

	};

	return "Could not return string in alException.cpp ALException::getErrorString!!\n";
}


} // al
} // managed
} // vs
