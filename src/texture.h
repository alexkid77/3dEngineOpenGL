/******************************************************************************/
/**	\file texture.h
	\brief Contains the CTexture class

	\author José María Arnau
	\date   11/09/2006
*******************************************************************************/

#ifndef __TEXTURE_H
#define __TEXTURE_H

#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

/******************************************************************************/
/** \class CTexture
	\brief The CTexture class represents a single texture 
		   object in the engine. To load a texture,
		   you only need to call the LoadTexture() function.
*******************************************************************************/
class CTexture
{
public:
	int width;
	int height;
	int bitDepth;
	unsigned int texID;

	SDL_Surface *image;
	GLubyte *data;

	CTexture()  { data = NULL; image = NULL; }
	~CTexture() { Unload(); }

	Uint32 getpixel(SDL_Surface *surface, int x, int y);
	void LoadTexture(char *filename);

	void Unload()
	{
		glDeleteTextures(1, &texID);
			
		if (image)
			SDL_FreeSurface(image);

		if (data)
			delete data;

		image = NULL;
		data  = NULL;
	}
};

#endif
