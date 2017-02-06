/**
 * @file
 * Functions to load Images and Textures.
 */
#ifndef VS_IMAGE_H
#define VS_IMAGE_H

// includes
#include <GL/gl.h>

namespace vs
{
namespace core
{
namespace gl
{

/**
 * Return value for loadTex() when the texture contains an alpha channel.
 */
const int VSGL_ALPHA = 1;
/**
 * Return value for loadTex() when the texture contains no alpha channel.
 */
const int VSGL_NO_ALPHA = 2;

/**
 * Load an image file and bind it as OpenGL texture object.
 * This function generates mipmaps with 24bit RGB / 32 bit RGBA format, depending on
 * the image having an alpha channel. The memory format is GL_UNSIGNED_BYTE.
 * OpenGL hast to be initialized before you can use this function.
 * 
 * @param filename
 * The name of the image file to be loaded.
 * 
 * @param texObj
 * Reference to the OpenGL texture object where the image is to be stored in.
 * Has to be initialized first.
 * 
 * @return
 * VSGL_ALPHA if the image has an alpha channel.
 * VSGL_NO_ALPHA if the image has no alpha channel.
 * 0 if the was an error.
 * 
 * @see
 * bindModel()
 */
int loadTex(const char *filename, GLuint &texObj);

} // gl
} // core
} // vs

#endif // VS_IMAGE_H
