/**
 * @file SharedLibraryStuff.h
 * @author sizilium
 * @date 03.07.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 * 
 * The dynamic loader stuff based on systemcalls (no ansi c++ standard), so at this time
 * only windows (MinGW compiler) and linux (gnu compiler) are supported.\n
 * You can use both: The wrapper functions or the wrapper class "SharedLibrary". 
 */

#ifndef DYNAMICLOADERSTUFF_H
#define DYNAMICLOADERSTUFF_H

// includes
#include <vs/Build.hpp>
#include <string>
#include <vs/base/util/Exception.h>

namespace vs
{
namespace managed
{
namespace plug
{
using namespace std;

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
#elif defined(__GNUC__)
	#include <dlfcn.h> 
#else
	#error define your compiler
#endif

/**
 * Open mode for shared libraries only for Linux. 
 */
VS_EXPORT enum Mode
{
	lazy = 1,	/**<     */
	now = 2,	/**<     */
	global = 4	/**<     */
};


/** @class LibraryHandle
 * A little helper class wich simply holds a pointer to an shared library opened with
 * specific os calls.
 */
class VS_EXPORT LibraryHandle
{
public:
	LibraryHandle(void *ptr)	{ptrToLibrary = ptr;}
	LibraryHandle()				{ptrToLibrary = NULL;}
	
	/**
	 * Checks if the pointer to the shared library is valid.
	 * @return True if the pointer is not NULL, else false.
	 */
	bool isValid() const
	{
		if (ptrToLibrary)
			return true;
		else
			return false;
	}

private:
	friend class SharedLibrary;
	friend bool closeSharedLibrary(LibraryHandle &libraryHandle);
	friend void* getFunction(const LibraryHandle &libraryHandle, const string &functionName);
	void *ptrToLibrary;
};


// --------------------------------------------------------------------------------


/**
 * Loads a shared library (*.so on on linux or *.dll on windows) and returns a 
 * handle to it.
 * With the handle you can check if an error occured.
 * @param path The path to the shared library without extension (will added automatically
 * depended of plattform).
 * @param mode Only for linux (optional). Use the enum.
 * @see LibraryHandle, Mode
 */
VS_EXPORT LibraryHandle loadSharedLibrary(const string &path, int mode = global);


/**
 * Gets a pointer to a "shared library function" referenced by a symbol name (functionName).
 * @param libraryHandle Pass a valid handle to a library (gets by loadSharedLibrary).
 * @param functionName The symbol name of the function in the shared library.
 * @return A pointer to the external function. NULL if an error occured.
 */
VS_EXPORT void* getFunction(const LibraryHandle &libraryHandle, const string &functionName);


/**
 * Close an opened shared library.
 * @param libraryHandle Pass a valid handle to the library. After this operation the
 * handle will be invalid.
 * @return True if no error occured, else false.
 */
VS_EXPORT bool closeSharedLibrary(LibraryHandle &libraryHandle);


// --------------------------------------------------------------------------------


/** @class SharedLibrary
 * A comfortable wrapper class for shared libraries. The class represents the shared
 * library. Simply pass the path to shared library to the constructor and get the
 * functions. The shared library automatically closed when this class will be destroyed.
 * Important: Catch the exceptions!
 */
class VS_EXPORT SharedLibrary
{
public:
	/**
	 * An empty constructor creates an uninitialized SharedLibrary class! Init it with
	 * open!
	 */
	SharedLibrary();
	/**
	 * Opens a shared library. It will closed automatically by destroying class!
	 * @param path The path to the shared library without extension (will added automatically
	 * depended of plattform).
	 * @param mode Only for linux (optional). Use the enum.
	 * @see Mode
	 */
	SharedLibrary(const string &path, enum Mode mode = global);
	
	/**
	 * Destructor automatically close the shared library.
	 */
	~SharedLibrary();
	
	/**
	 * Opens a shared library. If another shared library already is open it will close
	 * first.
	 * @param path The path to the shared library without extension (will added automatically
	 * depended of plattform).
	 * @param mode Only for linux (optional). Use the enum.
	 * @see Mode, close
	 */
	void open(const string &path, enum Mode mode = global);
	
	/**
	 * Closes the shared library (if no library is open nothing happens).
	 * After this operation the class will be uninitialized.
	 * You can open a shared library again with open.
	 * @see open
	 */
	void close();
	
	/**
	 * Gets a pointer to a function existing in the shared library by the function name
	 * (symbol name). This function in the shared library must be declared with 
	 * extern "C".
	 * @code // Example
	 * ...
	 * // extern function declared in extern.cpp (build as libextern.so / libextern.dll)
	 * extern "C" void myFunc(int param)
	 * {
	 *    cout << "i'm the extern function. you passed me the param: " << param << endl;
	 * }
	 * ...
	 * // get the extern funtion in main.cpp
	 * typedef void (*func)(int);
	 * func myFunc;
	 * 
	 * SharedLibrary library("libextern");
	 * myFunc = (func) library.getFunction("myFunc");
	 * 
	 * myFunc(8);	// output is: i'm the extern function. you passed me the param 8 
	 * 
	 * @endcode
	 */
	void* getFunction(const string &functionName)
	{
		if (path == "")
			throw base::util::Exception(__FILE__, __LINE__,
			                    "The SharedLibrary class isn't initialized! First init it with the open() method.");
		void *ptr = managed::plug::getFunction(handle, functionName);
		if (ptr == NULL)
			throw base::util::Exception(__FILE__, __LINE__,	
			                    "Couldn't get function from shared library \"" + path + 
			                    "\" (symbol \"" + functionName + "\" not found)!");
		return ptr;
	}
	
private:
	string path;
	LibraryHandle handle;
};


} // plug
} // managed
} // vs

#endif  // DYNAMICLOADERSTUFF_H
