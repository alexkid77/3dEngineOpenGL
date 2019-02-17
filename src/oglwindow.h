/***************************************************************************/
/**	\file oglwindow.h
	\brief Contains the COGLWindow class

	\author José María Arnau
	\date   11/09/2006
****************************************************************************/

#ifndef __OGLWINDOW_H__
#define __OGLWINDOW_H__


#include <windows.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "InputSystem.h"


/***************************************************************************/
/** \class COGLWindow
	\brief The COGLWindow class handles system messages and
		   distributes the messages among the engine.
****************************************************************************/
class COGLWindow
{
protected:
	SDL_Surface *screen;
	int flags;

	virtual bool OnCreate() { return true; }
	virtual bool OnClose() { return true; }
	virtual void OnSize() { }
	virtual void OnMouseDownL(float x, float y) { }
	virtual void OnMouseDownR(float x, float y) { }
	virtual void OnMouseUpL() { }
	virtual void OnMouseUpR() { }
	virtual void OnMouseMove(int x, int y, int centerX, int centerY) { }
	virtual void OnMouseMove(int deltaX, int deltaY) { }
	virtual void OnMouseDragL(int x, int y, int dx, int dy) { }
	virtual void OnMouseDragR(int x, int y, int dx, int dy) { }
	virtual void OnKeyUp(SDLKey nVirtKey) { }
	virtual void OnKeyDown(SDLKey nVirtKey) { }
	virtual void OnChar(char c) { }

	int WndProcOGL(SDL_Event event);

private:
	// message handling functions
	void Destroy();				   
	void Size();					
	void MouseMove(int x, int y);	

	float GetNormalizedPosX(int x);	// get normalized mouse coordinates
	float GetNormalizedPosY(int y);	// between (-1.0 and 1.0)


public:
	int width;
	int height;
	int centerX;
	int centerY;
	int bits;
	int aspect;
	int mouseX;
	int mouseY;
	bool fullscreen;

	float mouseSensitivity;

	bool useInput;
	CInputSystem *inputSystem;

	COGLWindow() {}
	COGLWindow(const char *szName, bool fscreen, int w, int h, int b);
	virtual ~COGLWindow();
	
	void BeginFullScreen(int w, int h, int b);
	void EndFullScreen();
};

#endif
