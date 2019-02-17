#define WIN32_MEAN_AND_LEAN
#define WIN32_EXTRA_LEAN

/*
	WINMAIN.CPP

	Contains WinMain, the main windows function

	Author: Kevin Hawkins
	Date: 3/19/2001
	Description:

*/


#include <windows.h>

#include "oglwindow.h"		// the OpenGL window class
#include "vector.h"
#include "engine.h"			// the engine's main class
#include "simpengine.h"


int WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	int loopRet;
	bool fscreen;
	CSimpEngine *engine = NULL;

	try
	{	
		fscreen = (MessageBox(NULL, "Deseas ejecutarlo en modo a pantalla completa?", "Fullscreen?", MB_YESNO) == IDYES);	
	
		engine = new CSimpEngine("OpenGL Game", fscreen, 800, 600, 32);

		loopRet = engine->EnterMessageLoop();

		delete engine;

		return loopRet;
	}
	catch(char *sz)
	{	
		MessageBox(NULL, sz, 0, 0);
		delete engine;
	}

	return -1;
}