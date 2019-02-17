/**************************************************************************************/
/**	\file  simpengine.h
	\brief Contains the SimpEngine class

	\author Kevin Hawkins
	\date   3/29/2001
***************************************************************************************/

#ifndef __SIMPENGINE
#define __SIMPENGINE

#include <windows.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "engine.h"
#include "object.h"
#include "camera.h"
#include "terrain.h"
#include "world.h"
#include "font.h"
#include <iostream>
using namespace std;


/**************************************************************************************/
/** \class CSimpEngine
	\brief The SimpEngine class is the main interface for SimpEngine. 
		   Derived from CEngine, tt provides the camera and world objects.
***************************************************************************************/
class CSimpEngine : public CEngine
{
private:
	CCamera *gameCamera;
	CWorld *gameWorld;

protected:
	CCamera *OnGetCamera() { return gameCamera; }
	CWorld *OnGetWorld() { return gameWorld; }

	void OnPrepare();
	void OnMouseDownL(float x, float y);
	void OnMouseMove(int deltaX, int deltaY);
	void OnMouseMove(int x, int y, int centerX, int centerY);
	void OnKeyDown(SDLKey nVirtKey);

public:
	CSimpEngine() 
	{
		gameCamera = new CCamera;
		gameWorld = new CWorld;
	}

	CSimpEngine(const char *szName, bool fscreen, int w, int h, int b);

	~CSimpEngine() 
	{
		delete gameWorld;
		delete gameCamera;
		gameWorld = NULL;
		gameCamera = NULL;
	}
};


#endif
