/***********************************************************************************/
/**	\file engine.h

	\brief Contains the main engine class

	\author Kevin Hawkins
	\date 3/29/2001
************************************************************************************/

#ifndef __ENGINE_H
#define __ENGINE_H

#include "world.h"
#include "oglwindow.h"
#include "camera.h"
#include "HiResTimer.h"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>


/***********************************************************************************/
/** \class CEngine
	\brief CEngine represents the main engine class.

	CEngine is the main engine class, derived from COGLWindow.
    It holds virtual functions GameCycle, OnPrepare, OnGetCamera,
    and OnGetWorld. CEngine is also the location of the main
    Windows message loop. 
************************************************************************************/
class CEngine : public COGLWindow
{
protected:
	/** high performance timer */
	CHiResTimer *timer;						

	virtual void GameCycle(float deltaTime);

	/** setup OpenGL for frame */
	virtual void OnPrepare() {}	

	/** override in derived engine */
	virtual CCamera *OnGetCamera() { return NULL; }
	virtual CWorld *OnGetWorld() { return NULL; }

	/** Check the input system for new events */
	virtual void CheckInput(float deltaTime);

	void SwapBuffers() { SDL_GL_SwapBuffers(); }

public:
	CEngine() {}
	CEngine(const char *szName, bool fscreen, int w, int h, int b) : 
			COGLWindow(szName, fscreen, w, h, b) {}
	~CEngine() {}
	int EnterMessageLoop();
};

#endif
