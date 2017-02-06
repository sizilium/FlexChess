#include "vsgli.h"

#include <gl/glu.h>
#include <freeimage.h>
#include <cmath>

void vsglLoadTex(const char *filename, GLuint &uiTexObj)
{
	FreeImage_Initialise(true);
	
	// TODO : Get image type from filename
	FIBITMAP *bitmap = FreeImage_Load(FIF_JPEG, filename, JPEG_ACCURATE);
	
	int iBytePerPixel = FreeImage_GetBPP(bitmap) / (sizeof(char)*8);
	int iRedMask = FreeImage_GetRedMask(bitmap);
	int iGreenMask = FreeImage_GetGreenMask(bitmap);
	int iBlueMask = FreeImage_GetBlueMask(bitmap);
	int iWidth = FreeImage_GetWidth(bitmap);
	int iHeight = FreeImage_GetHeight(bitmap);
	char *cpArray = (char *)FreeImage_GetBits(bitmap);
	
	float *fpPixels = new float[iWidth*iHeight*4];	// float RGBA array used to construct OpenGL texture
	char *cpPixel = new char[iBytePerPixel*iWidth*iHeight];		// current pixel
	cpPixel = cpArray;

	// normalize values
	long lRedOffset = 1;
	int iRedShift = 0;
	while (((iRedMask / lRedOffset) & 1) == 0)
	{
		lRedOffset *= 2;
		iRedShift++;
	}
	iRedShift /= 8;

	long lGreenOffset = 1;
	int iGreenShift = 0;
	while (((iGreenMask / lGreenOffset) & 1) == 0)
	{
		lGreenOffset *= 2;
		iGreenShift++;
	}
	iGreenShift /= 8;

	long lBlueOffset = 1;
	int iBlueShift = 0;
	while (((iBlueMask / lBlueOffset) & 1) == 0)
	{
		lBlueOffset *= 2;
		iBlueShift++;
	}
	iBlueShift /= 8;
	
	// TODO : normalize alpha value
	
	for (long i = 0; i < iWidth*iHeight; i++)
	{
		cpPixel += iBytePerPixel;					// go to next pixel
		
		long lCurrPixel;
		memcpy((void *) &lCurrPixel, (void *) cpPixel, iBytePerPixel);
		
		// extract rgba values
		fpPixels[i*4] = float((lCurrPixel & iRedMask) / lRedOffset) / 255;
		fpPixels[i*4+1] = float((lCurrPixel & iGreenMask) / lGreenOffset) / 255;
		fpPixels[i*4+2] = float((lCurrPixel & iBlueMask) / lBlueOffset) / 255;
		// TODO : alpha values from image
		fpPixels[i*4+3] = 1.0f;
		
		#ifdef WIN32
		float temp = fpPixels[i*4];
		fpPixels[i*4] = fpPixels[i*4+2];
		fpPixels[i*4+2] = temp;
		#endif
	}
	
	// build OpenGL texture
	glBindTexture(GL_TEXTURE_2D, uiTexObj);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, iWidth, iHeight, GL_RGBA, GL_FLOAT, fpPixels);

	FreeImage_DeInitialise();
}
