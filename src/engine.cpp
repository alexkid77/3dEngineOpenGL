#include <stdlib.h>

#include "engine.h"
#include "HiResTimer.h"
#include "camera.h"
#include "world.h"

/**********************************************************************************/
/**	\file engine.cpp
    \brief Contains the CEngine class implementation                              */


/**********************************************************************************/
/** Check the input system for new events from mouse, keyboard or joysticks
***********************************************************************************/
void CEngine::CheckInput(float deltaTime)
{
	static float buttonDelta = 0.0f;

	int mouseDeltaX, mouseDeltaY;	// changes in the mouse position

	// decrease amount of time until next possible recognized button pressing
	buttonDelta -= deltaTime;

	if (buttonDelta < 0.0f)
		buttonDelta = 0.0f;

	// update devices
	inputSystem->Update();

	// retrieve the latest mouse movements
	inputSystem->GetMouseMovement(mouseDeltaX, mouseDeltaY);
	OnMouseMove(mouseDeltaX, mouseDeltaY);

	if (inputSystem->KeyDown(SDLK_w))
		OnKeyDown(SDLK_UP);
	if (inputSystem->KeyDown(SDLK_s))
		OnKeyDown(SDLK_DOWN);
	if (inputSystem->KeyDown(SDLK_a))
		OnKeyDown(SDLK_LEFT);
	if (inputSystem->KeyDown(SDLK_d))
		OnKeyDown(SDLK_RIGHT);
	if (inputSystem->KeyDown(SDLK_f))
		OnKeyDown(SDLK_f);
	if (inputSystem->KeyDown(SDLK_g))
		OnKeyDown(SDLK_g);
	if (inputSystem->KeyDown(SDLK_PLUS))
		OnKeyDown(SDLK_PLUS);
	if (inputSystem->KeyDown(SDLK_MINUS))
		OnKeyDown(SDLK_MINUS);
	if (inputSystem->KeyDown(SDLK_ESCAPE))
		OnKeyDown(SDLK_ESCAPE);
	if (inputSystem->ButtonDown(SDL_BUTTON_LEFT))
	{
		if (buttonDelta == 0.0f)
		{
			OnMouseDownL(0,0);
			buttonDelta = 0.5f;
		}
	}
}

/**********************************************************************************/
/** The basic game cycle: perform collisions, prepare, animate and draw objects
***********************************************************************************/
void CEngine::GameCycle(float deltaTime)
{
	CCamera *camera = OnGetCamera();	// get the camera
	CWorld *world = OnGetWorld();		// get the world

	if (useInput)
		CheckInput(deltaTime);

	// setup opengl for frame (clear, identity)
	OnPrepare();

	// prepare objects and perform collisions
	world->Prepare();

	// move/orient camera
	camera->Animate(deltaTime);

	// move/orient objects
	world->Animate(deltaTime);

	// draw objects
	world->Draw(camera);

	// swap buffers
	SwapBuffers();
}

/**********************************************************************************/
/** The application message loop 
***********************************************************************************/
int CEngine::EnterMessageLoop()
{
	//	Message loop
	SDL_Event event;
	timer = new CHiResTimer;

	timer->Init();

	for (;;)
	{	
		GameCycle(timer->GetElapsedSeconds(1));
		//timer->LockFPS(50);
		while (SDL_PollEvent(&event))
		{
			WndProcOGL(event);
		}
	}

	delete timer;

	return 0;
}
