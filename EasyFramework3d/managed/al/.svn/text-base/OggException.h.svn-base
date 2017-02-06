/**
 * @file OggException.h contains a special ALException class for ogg vorbis
 * errors.
 */

#ifndef OGG_EXCEPTION_H
#define OGG_EXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>
#include <ogg/ogg.h>
#include <vorbis/vorbisfile.h>

namespace vs
{
namespace managed
{
namespace al
{
using namespace std;

/**
 * special ALException class for exceptions in vs::al namespace.
 * Contains additionally a error code
 * @see Exception
 */
class VS_EXPORT OggException : public base::util::Exception
{
public:
    /**
     * @param fileOfOccuredError see Exception
     * @param placeOfOccuredError see Exception
     * @param description see Exception
     * @param error a al error code, for example 'OV_EREAD'...
     * @see Exception
     */
    OggException(string fileOfOccuredError, string placeOfOccuredError,
                string description, int error);
    OggException(string fileOfOccuredError, int placeOfOccuredError,
                string description, int error);
    ~OggException() throw();

    /**
     * @return error description based on the errorCode and the type variable
     */
    string getErrorString() const;

    /**
     *@return ogg error codes for example: 'OV_ENOTVORBIS' or 'OV_EBADHEADER'
     */
    int getErrorCode() const	{return errorCode;}

private:
    int errorCode;
};


} // al
} // managed
} // vs

#endif // OGG_EXCEPTION_H
