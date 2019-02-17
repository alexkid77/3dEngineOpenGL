#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN

/*********************************************************************/
/** \file font.cpp
	\brief The CFont class implementation                            */

#include "font.h"

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <gl/gl.h>

/*********************************************************************/
/** CFont class constructor
**********************************************************************/
CFont::CFont()
{
	screenX = 0;
	screenY = 0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
}


/*********************************************************************/
/** CFont class constructor
	\param name Font name
	\param size Font size
**********************************************************************/
CFont::CFont(char *name, int size)
{
	screenX = 0;
	screenY = 0;
	xpos = 0.0;
	ypos = 0.0;
	zpos = 0.0;
	Build(name, size);
}


/*********************************************************************/
/** CFont class destructor
**********************************************************************/
CFont::~CFont()
{
	glDeleteLists(callList, 96);
}


/*********************************************************************/
/** Creates the font.
	Characters are stored in a display list
**********************************************************************/
void CFont::Build(char *name, int size)
{
	HFONT hFont;	// font ID
	HDC hDC;		// device context

	hDC = wglGetCurrentDC();
	callList = glGenLists(96);

	if (stricmp(name, "symbol") == 0)
	{
		hFont = CreateFont(-size, 0,0,0,FW_BOLD, FALSE, FALSE, FALSE, SYMBOL_CHARSET,
						OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
						FF_DONTCARE | DEFAULT_PITCH, (LPCTSTR)name);
	}
	else
	{
		hFont = CreateFont(-size, 0,0,0,FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 
					FF_DONTCARE | DEFAULT_PITCH, (LPCTSTR)name);
	}

	SelectObject(hDC, hFont);
	wglUseFontBitmaps(hDC, 32, 96, callList);
}


/*********************************************************************/
/** Renders a string in the screen
	\param str Text to be displayed
**********************************************************************/
void CFont::Print(const char *str, ...)
{
	char text[256];
	va_list args;

	if (str == NULL)
		return;

	va_start(args, str);
		vsprintf(text, str, args);
	va_end(args);

	glPushMatrix();
	glColor4f(r, g, b, a);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.0f);	// translate one unit into the screen
	if (xpos == 0.0 && ypos == 0.0 && zpos == 0.0)
		glRasterPos2i(screenX, screenY);
	else
		glRasterPos3f(xpos, ypos, zpos);

	glPushAttrib(GL_LIST_BIT);
		glListBase(callList - 32);
		glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
	glPopMatrix();
}


/*********************************************************************/
/** Free the display list
**********************************************************************/
void CFont::ClearFont()
{
	glDeleteLists(callList, 96);
}
