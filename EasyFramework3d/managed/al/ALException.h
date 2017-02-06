/**
 * @file ALException.h
 * Contains a special ALException class for al, alc, alut and
 * errors. The 'Type' enums specifies the kind of the error
 */

#ifndef AL_EXCEPTION_H
#define AL_EXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;

/**
 * al, alc, alut, oggVorbis error are possible types of ALException class
 */
VS_EXPORT enum Type
{
    AL_ERROR, ALC_ERROR, ALUT_ERROR
};

/**
 * special ALException class for exceptions in vs::al namespace.
 * Contains additionally a ALenum error code
 * @see Exception
 */
class VS_EXPORT ALException : public base::util::Exception
{
public:
    /**
     * @param fileOfOccuredError see Exception
     * @param placeOfOccuredError see Exception
     * @param description see Exception
     * @param error a al error code, for example 'AL_INVALID_NAME'...
     * @param type valid types are AL_ERROR, ALC_ERROR or ALUT_ERROR
     * @see Exception
     */
    ALException(string fileOfOccuredError, string placeOfOccuredError,
                string description, ALenum error, Type type);
    ALException(string fileOfOccuredError, int placeOfOccuredError,
                string description, ALenum error, Type type);
    ~ALException() throw();

    /**
     * @return error description based on the errorCode and the type variable
     */
    string getErrorString() const;

    /**
     *@return al error code for example: 'AL_INVALID_NAME' or 'AL_OUT_OF_MEMORY'
     * important: the error code depends on the type variable! alut for example
     * include other error code definitions
     */
    ALenum getErrorCode() const     {return errorCode;}

    /**
     *@return possible values are AL_ERROR | ALC_ERROR | ALUT_ERROR
     */
    Type getErrorType() const       {return alType;}

private:
    ALenum errorCode;
    Type alType;
};


} // al
} // managed
} // vs
#endif // AL_EXCEPTION_H
