/**
 * @file FontStorage.h
 * @author sizilium
 * @date 28.12.2007
 * @brief This file is part of the Vision Synthesis Easy Framework.\n
 * This file has no copyright; you can change everything.
 * Visit www.vision-synthesis.de or www.easy-framework.de for further informations.\n
 * If there is a bug please send a mail to bug@vision-synthesis.de. No warranty is given!
 */

#ifndef FONT_STORAGE_H
#define FONT_STORAGE_H

// includes
#include <vs/Build.hpp>
#include <FTGL/FTGLTextureFont.h>
//#include <ftgl/FTGLPixmapFont.h>
//#include <ftgl/FTGLBitmapFont.h>
//#include <ftgl/FTGLOutlineFont.h>
//#include <ftgl/FTGLPolygonFont.h>
//#include <ftgl/FTGLExtrdFont.h>

#include <map>
#include <string>

// global defines
#define USING_FTGLFONT	FTGLTextureFont
//#define USING_FTGLFONT	FTGLPixmapFont
//#define USING_FTGLFONT	FTGLBitmapFont
//#define USING_FTGLFONT	FTGLOutlineFont
//#define USING_FTGLFONT	FTGLPolygonFont
//#define USING_FTGLFONT	FTGLExtrdFont

// platform specific font path
#if defined(_WIN32)
 #define FONTPATH	"C:/WINDOWS/Fonts/"
#elif defined(__GNUC__)
 #define FONTPATH	"/usr/share/fonts/truetype/"
#else
 #error define your compiler
#endif

namespace vs
{
namespace core
{
namespace gui
{

/** @class FontStorage
 * This singleton is a global storage for FTGL fonts. If you want to render a font, 
 * first you have to load it in the memory (each with font type and face size). 
 * When you use a font more than one times, its better to use only one instance than create a new
 * everytime. With this font creator and storage you can safe memory and performance!
 * @code // Example
 * try
 * {
 *     FTGLTextureFont *myFont_1 = FontStorage::instance().getFont("arial.ttf", 30);
 *     FTGLTextureFont *myFont_2 = FontStorage::instance().getFont("arial.ttf", 30);
 *     FTGLTextureFont *myFont_3 = FontStorage::instance().getFont("arial.ttf", 50);
 * }
 * catch (GuiFontException &e)
 * {
 *     e.printStackTrace();
 * }
 * 
 * // there will be only one instance of myFont_1 and myFont_2 ...
 * @endcode
 */
class VS_EXPORT FontStorage
{
    public:
    	/**
    	 * Deletes all fonts. You don't have to delete the fonts manually.
    	 */
        ~FontStorage();
        
        /**
         * Gets the FontStorage instance (singleton). Its a global container for all contextes,
         * managers and elements.
         */
        static FontStorage& getInstance();
        
        /**
         * Gets the desired font (returns an old one or creates a new font).
         * @param filename The platform specific folder will be searched for the font (on windows
         * C:/WINDOWS/Fonts). If the font wasn't found, it will searched in the local directory.
         * Use arial.ttf for example.
         * @param size Try a font size of 30 for example.
         * @throw GuiFontException
         * @return By success the method returns the font, else an exception will be thrown.
         */
        FTFont* getFont(std::string fontName, int size);
        
        /**
         * Returns the number of loaded fonts. Useful for debugging and needed memory valuation.
         */
        int size() const;
        
    private:
        // Hide these because this is a singleton.
    	FontStorage()
    	{
    	}
    	
        // Hide these because this is a singleton.
    	FontStorage( const FontStorage&)
    	{
    	}
    	
        // Hide these because this is a singleton.
    	FontStorage& operator = ( const FontStorage&)
    	{ 
    		return *this;
    	}
        
        // container for fonts
    	std::map<std::string, FTFont*> fonts;
};

} // gui
} // core
} // vs

#endif  // FONT_STORAGE_H
