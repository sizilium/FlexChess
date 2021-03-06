#include <vs/managed/plug/SharedLibraryStuff.h>
#include <assert.h>

namespace vs
{
namespace managed
{
namespace plug
{
using namespace base::util;

LibraryHandle loadSharedLibrary(const string &path, int mode)
{
#ifdef _WIN32
	string fullPath = path + ".dll";
	return LibraryHandle(static_cast<void*> ( LoadLibrary(fullPath.c_str()) ) );
#else
	string fullPath = path + ".so";
	return LibraryHandle( dlopen(fullPath.c_str(), mode) );
#endif
	
}


void* getFunction(const LibraryHandle &handle, const string &functionName)
{
#ifdef _WIN32
	return (void*) ( GetProcAddress (static_cast<HINSTANCE>(handle.ptrToLibrary),
	                                 functionName.c_str()) );
#else
	// reset errors
	dlerror();
	return dlsym(handle.ptrToLibrary, functionName.c_str());
#endif
}


bool closeSharedLibrary(LibraryHandle &handle)
{
bool retVal;

#ifdef _WIN32
	retVal =  FreeLibrary ( static_cast<HINSTANCE>(handle.ptrToLibrary) );
	handle.ptrToLibrary = NULL;
#else
	retVal = dlclose(handle.ptrToLibrary);
	handle.ptrToLibrary = NULL;
#endif
	
	return retVal;
}


// --------------------------------------------------------------------------------


SharedLibrary::SharedLibrary()
{	
}


SharedLibrary::SharedLibrary(const string &path, enum Mode mode)
{
	open(path, mode);	// throws exception
}


void SharedLibrary::open(const string &path, enum Mode mode)
{ 
	this->handle = loadSharedLibrary(path, mode);
	if (!handle.isValid())
		throw Exception(__FILE__, __LINE__,
		                    "Couldn't open shared library \"" + path + "\" !");
	
	this->path = path;
}


SharedLibrary::~SharedLibrary()
{
	if (handle.isValid())
	{
<<<<<<< .mine
		bool success = closeSharedLibrary(handle);
=======
		// TODO : what is this?
		//bool success = closeSharedLibrary(handle);
>>>>>>> .r442
		//assert("Couldn't close shared library! (check path with debugger)" && success);
	}
}


} // plug
} // managed
} // vs
