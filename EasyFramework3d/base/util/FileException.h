/**
 * @file FileException.h for spezial exceptions on files, for example
 * 'FILE_NOT_FOUND'
 */

#ifndef VS_FILE_EXCEPTION_H
#define VS_FILE_EXCEPTION_H

// includes
#include <vs/Build.hpp>
#include <vs/base/util/Exception.h>
#include <string>

using namespace std;

namespace vs
{
namespace base
{
namespace util
{

/**
 * FileException for spezial exceptions on files.
 * @see Exception
 */
class VS_EXPORT FileException : public Exception
{
public:
    FileException(string fileOfOccuredError, string placeOfOccuredError,
                string description, string corruptedFile);
    FileException(string fileOfOccuredError, int placeOfOccuredError,
                string description, string corruptedFile);
    ~FileException() throw();

    string getCorruptedFile() const;

private:
    string corruptedFile;
};


} // util
} // base
} // vs

#endif // VS_FILE_EXCEPTION_H
