/**
 * @file Build.hpp
 * @author sizilium
 * @date 31.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef VS_BUILD_HPP
#define VS_BUILD_HPP

namespace vs
{


// Definition of the VS_EXPORT makro.
//
// The define makros indicate whether you are building a dll, building client code that will 
// link to the dll, or merely building/linking to a static library.
//
// There are three options:
// #define VS_EXPORT
// #define VS_EXPORT __declspec(dllimport)
// #define VS_EXPORT __declspec(dllexport)
//
// To build a shared library (dll) use define the VS_BUILD_DLL makro in your IDE.
// To use a shared library you don't have to define anything.
//
#if (defined(_WIN32) || defined(__CYGWIN__)) && !defined(VS_BUILD_STATIC)

	#ifdef VS_BUILD_DLL
		#define VS_EXPORT __declspec(dllexport)				// __attribute__ ((dllexport))
	#else
		#ifdef __MINGW32__
			#define VS_EXPORT
		#else
			#define VS_EXPORT __declspec(dllimport)
		#endif
	#endif

#else // Linux, Mac, OSX etc. 
	#define VS_EXPORT
#endif

} // vs

#endif  // VS_BUILD_HPP
