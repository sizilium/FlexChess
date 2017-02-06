#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

// includes
#include <vs/Build.hpp>
#include <list>
#include <string>
#include <map>
#include <GL/gl.h>

using namespace std;

namespace vs
{
namespace core
{
namespace gl
{

class VS_EXPORT TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	void loadTextures(list<string> &textureNames);

	GLuint getTexId(const string &texName) { return texNames2texIds[texName]; }
	
protected:
	map<string, GLuint> texNames2texIds;

};

// the only instance
extern TextureManager textureManager;

} // gl
} // core
} // vs

#endif /*TEXTUREMANAGER_H_*/
