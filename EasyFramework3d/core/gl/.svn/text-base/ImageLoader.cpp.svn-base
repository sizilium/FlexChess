#include <vs/core/gl/ImageLoader.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <FreeImage.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>

namespace vs
{
namespace core
{
namespace gl
{
using namespace std;

string getFileExtension(const char *filename)
{
	char *ext = strrchr(filename, '.');
	ext++;
	for (unsigned int i = 0; i < strlen(ext); i++)
		ext[i] = tolower(ext[i]);
	string s = ext;
	return s;
}

/**
*	Load the image from filename as OpenGL Texture Object
*
*	@param filename	Filename of the image to be loaded.
*	@param texObj	Handle of the Texture Object where the texture is stored in.
*
*	@return VSGL_ALPHA if texture has alpha channel otherwise return VSGL_NO_ALPHA. If an error occurred return 0;
*/
int loadTex(const char *filename, GLuint &texObj)
{
	glPushMatrix();
	glPopMatrix();
	if (glGetError() != GL_NO_ERROR)
	{
		cerr << "loadTex(): OpenGL isn't ready to use. Initialize first." << endl;
		return 0;
	}

	FreeImage_Initialise(true);

	string ext = getFileExtension(filename);

	FIBITMAP *tempBitmap = 0;
	if ((ext == "jpg") || (ext == "jpeg"))
	{
		tempBitmap = FreeImage_Load(FIF_JPEG, filename, JPEG_ACCURATE);

	}
	else if (ext == "png")
	{
		tempBitmap = FreeImage_Load(FIF_PNG, filename, PNG_DEFAULT);
	}
	else
	{
		cerr << "loadTex(): Image type (" << ext << ") of file " << filename <<
				" is not supported yet. Currently supported are .jpg and .png" << endl;
		return 0;
	}
	// TODO : consider other file types

	if (!tempBitmap) {
		cerr << "loadTex(): Couldn't load image " << filename << "." << endl;
		return 0;
	}

	int alpha = VSGL_NO_ALPHA;
	int bytePerPixel = 3;

	// assure that bitmap has 8 bits per pixel
	int bpp = FreeImage_GetBPP(tempBitmap);
	FIBITMAP *bitmap;
	if (FreeImage_IsTransparent(tempBitmap))
	{
		if (bpp < 8)
		{
			bitmap = FreeImage_ConvertTo32Bits(tempBitmap);
			FreeImage_Unload(tempBitmap);
			tempBitmap = NULL;
		}
		else
		{
			bitmap = tempBitmap;
		}
		alpha = VSGL_ALPHA;
		bytePerPixel = 4;
	}
	else
	{
		if (bpp < 8)
		{
			bitmap = FreeImage_ConvertTo24Bits(tempBitmap);
			FreeImage_Unload(tempBitmap);
			tempBitmap = NULL;
		}
		else
		{
			bitmap = tempBitmap;
		}
	}


	int iWidth = FreeImage_GetWidth(bitmap);
	int iHeight = FreeImage_GetHeight(bitmap);
	unsigned char *cpArray;
	cpArray = (unsigned char *)FreeImage_GetBits(bitmap);

	for (long i = 0; i < iWidth*iHeight; i++)
	{
//		#ifdef WIN32
		// swap red and blue
		char temp = cpArray[i*bytePerPixel];
		cpArray[i*bytePerPixel] = cpArray[i*bytePerPixel+2];
		cpArray[i*bytePerPixel+2] = temp;
//		#endif
	}

	// build OpenGL texture
	glBindTexture(GL_TEXTURE_2D, texObj);
	if (alpha == VSGL_ALPHA)
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, iWidth, iHeight, GL_RGBA, GL_UNSIGNED_BYTE, cpArray);
	else
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, iWidth, iHeight, GL_RGB, GL_UNSIGNED_BYTE, cpArray);

	int i = 0;
	GLenum errorCode = glGetError();
	while (errorCode != GL_NO_ERROR)
	{
		if (i == 10)
		{
			cerr << "loadTex(): More than " << i << " OpenGL Errors detected." << endl
			<< "\tOnly the first " << i << " were printed." << endl;
			break;
		}
		alpha = 0;
		cerr << "loadTex(): OpenGL error: " << gluErrorString(errorCode) << endl;
		errorCode = glGetError();
		i++;
	}

	FreeImage_Unload(bitmap);
	bitmap = NULL;

	FreeImage_DeInitialise();

	return alpha;
}

} // gl
} // core
} // vs
