/******************************************************************************/
/** \file font.h

	\brief Contains the CFont class

	\author Kevin Hawkins
	\date   3/29/2001
*******************************************************************************/

#ifndef __FONT_H
#define __FONT_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

/******************************************************************************/
/** \class CFont
	\brief The CFont class. Currently only supports Bitmap fonts.
*******************************************************************************/
class CFont
{
private:
	unsigned int texID;		// font texture id
	unsigned int callList;	// font display list
	float r, g, b, a;		// RGBA
	int screenX, screenY;	// screen coordinates
	float xpos, ypos, zpos;	// 3d coordinates

	void LoadTexture();		// loads the TGA font texture
	void CreateCallLists();	// creates the font display list

public:
	CFont();
	CFont(char *name, int size);
	~CFont();

	void Build(char *name, int size);
	void ClearFont();

	void Print(const char *str, ...);

	void SetPos2D(int x, int y) { screenX = x; screenY = y; }
	void SetPos3D(float x, float y, float z) { xpos = x; ypos = y; zpos = z; }

	void SetRGB(float red, float green, float blue) { r = red; g = green; b = blue; a = 1.0; }
	void SetRGBA(float red, float green, float blue, float alpha) { r = red; g = green; b = blue; a = alpha; }
};

#endif
