#include <vs/core/gui/FontStorage.h>
#include <vs/core/gui/GuiException.h>

namespace vs
{
namespace core
{
namespace gui
{
using namespace std;

FontStorage::~FontStorage()
{
	// delete all fonts
	map<string, FTFont*>::const_iterator font;
    for(font = fonts.begin(); font != fonts.end(); font++)
        delete (*font).second;;

    fonts.clear();
}

FontStorage& FontStorage::getInstance()
{
    static FontStorage storage;
    return storage;
}

FTFont* FontStorage::getFont(string filename, int size)
{
	// generate key
    char buf[256];
    sprintf(buf, "%s%i", filename.c_str(), size);
    string fontKey = string(buf);
    
    // search if font already exists
    map<string, FTFont*>::const_iterator result = fonts.find(fontKey);
    if( result != fonts.end())
        return result->second;	// return existing font (memory safe, more performance)

    // create a new font
    FTFont *font = NULL;
    
    string fullname = string(FONTPATH) + filename;
    
    font = new FTGLTextureFont(fullname.c_str());	// search font in system directory
    if (font->Error())		
    {
    	font = new FTGLTextureFont(filename.c_str());		// search font local
    	
    	if (font->Error())
    	{
    		delete font;
    		throw GuiFontException(__FILE__, __LINE__, 
    		                   "Could not load font. Neither from the system directory nor from the local directory!",
    		                   string(filename));
    	}
    }
    
    if(!font->FaceSize(size))
    {
        delete font;
		throw GuiFontException(__FILE__, __LINE__, 
		                   "Could not set the face size of font. Maybe the value is too high!",
		                   size);
    }

    font->CharMap(ft_encoding_unicode);
    
    // save new font for future
    fonts[fontKey] = font;
    
    return font;
} 

int FontStorage::size() const
{
	return fonts.size();
}


} // gui
} // core
} // vs
