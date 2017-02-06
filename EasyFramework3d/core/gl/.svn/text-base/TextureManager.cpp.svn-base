#include <vs/core/gl/TextureManager.h>
#include <vs/core/gl/ImageLoader.h>
#include <list>
#include <string>
#include <iostream>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{

TextureManager::TextureManager()
: texNames2texIds()
{}

TextureManager::~TextureManager()
{}

void TextureManager::loadTextures(list<string> &textureNames)
{
	list<string> textures;
	int textureNumber = 0;
    // TODO : group textures
    list<string>::iterator strIt;
    for (strIt = textureNames.begin(); strIt != textureNames.end(); ++strIt)
    {
        if (texNames2texIds.count(*strIt) == 0) {
        	textures.push_back(*strIt);
        	textureNumber++;
        }
    }
    GLuint *textureObjects = new unsigned int[textureNumber];
    glGenTextures(textureNumber, textureObjects);
    int i = 0;
    list<string>::iterator loadIt;
    for (loadIt = textures.begin(); loadIt != textures.end(); ++loadIt, i++)
    {
        // TODO : Exceptions
        if (!loadTex(loadIt->c_str(), *(textureObjects + i)))
            return;
        texNames2texIds[*loadIt] = *(textureObjects + i);
    }
    delete [] textureObjects;
    textureObjects = NULL;
}

// TODO : freeTextures()

// the only instance
TextureManager textureManager;

} // namespace gl
} // namespace core
} // namespace vs
