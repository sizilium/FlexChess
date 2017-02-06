#include <vs/base/util/FileException.h>

namespace vs
{
namespace base
{
namespace util
{

FileException::FileException(string fileOfOccuredError, string placeOfOccuredError,
							 string description, string badFile)
:Exception(fileOfOccuredError, placeOfOccuredError, description), corruptedFile(badFile)
{}
							 
FileException::FileException(string fileOfOccuredError, int placeOfOccuredError,
							 string description, string badFile)
:Exception(fileOfOccuredError, placeOfOccuredError, description), corruptedFile(badFile)
{}


FileException::~FileException() throw()
{
}

string FileException::getCorruptedFile() const
{
	return corruptedFile;
}


} // util
} // base
} // vs
