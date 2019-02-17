#include "simpengine.h"

/**********************************************************************************/
/**	\file  simpengine.cpp
	\brief The SimpEngine implementation                                          */


/**********************************************************************************/
/** CSimpEngine class constructor
***********************************************************************************/
CSimpEngine::CSimpEngine(const char *szName, bool fscreen, int w, int h, int b) :
		CEngine(szName, fscreen, w, h, b) 
{
	gameCamera = new CCamera;
	gameWorld = new CWorld(gameCamera);
	gameCamera->yaw=45.0;
}


/**********************************************************************************/
/** Setup OpenGL for rendering
***********************************************************************************/
void CSimpEngine::OnPrepare()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//eliminacion caras traseras
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable ( GL_COLOR_MATERIAL ) ;
	// glLoadIdentity();
	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	gluPerspective(54.0f, (float)width/(float)height, 0.1f, 5000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


/**********************************************************************************/
/** Shoots a rocket when left button is pressed
***********************************************************************************/
void CSimpEngine::OnMouseDownL(float x, float y) 
{
//	if (!gameWorld->IsGameDone())
//		gameWorld->player->FireWeapon();
}


/**********************************************************************************/
/** \param nVirtKey Key pressed by user
***********************************************************************************/
void CSimpEngine::OnKeyDown(SDLKey nVirtKey)
{
//    if (!gameWorld->IsGameDone())
//	{
		switch (nVirtKey)
		{
		case SDLK_UP:
				gameCamera->velocity += CVector(0.0,0.0,5.0);
			
			
			break;
		case SDLK_DOWN:
			
			gameCamera->velocity += CVector(0,0,-5.0);
			break;
		case SDLK_RIGHT:
			gameCamera->velocity += CVector(5.0, 0.0, 0.0);
			break;
		case SDLK_LEFT:
			gameCamera->velocity += CVector(-5.0, 0.0, 0.0);
			break;
		case SDLK_f:
			if(fullscreen) EndFullScreen();
			else BeginFullScreen(width,height,bits);
			break;
		case SDLK_g:
			while(!inputSystem->KeyDown(SDLK_h)) inputSystem->Update();
			break;
		case SDLK_ESCAPE:
			SDL_Event event;
			event.type = SDL_QUIT;
			event.quit.type = SDL_QUIT;
			SDL_PushEvent(&event);
			break;
		case SDLK_PLUS:
			mouseSensitivity += 0.05f;
			break;
		case SDLK_MINUS:
			mouseSensitivity -= 0.05f;
			if (mouseSensitivity < 0.05)
				mouseSensitivity = 0.05f;
			break;
		default:
			break;
		}
//	}
//	else
//	{
//		if ((nVirtKey) == SDLK_ESCAPE)
//		{
//			SDL_Event event;
//			event.type = SDL_QUIT;
//			event.quit.type = SDL_QUIT;
//			SDL_PushEvent(&event);
//		}
//	}
}


/**********************************************************************************/
/** Update the camera when user moves the mouse 
	\param deltaX change in x position since last call
	\param deltaY change in y position since last call
***********************************************************************************/
void CSimpEngine::OnMouseMove(int deltaX, int deltaY)
{
//	if (!gameWorld->IsGameDone())
//	{
		gameCamera->yaw += deltaX*mouseSensitivity;
		gameCamera->pitch -= deltaY*mouseSensitivity;
//	}
}


/**********************************************************************************/
/** Update the camera when user moves the mouse
***********************************************************************************/
void CSimpEngine::OnMouseMove(int x, int y, int centerX, int centerY)
{
	static float oldX;
	static float oldY;
	static float yaw = 0.0f;
	static float pitch = 0.0f;

	float mX, mY;

	mX = (float)x;
	mY = (float)y;

	if (mX < centerX/2)
		gameCamera->yaw -= 0.25f*mouseSensitivity;
	if (mX > centerX/2)
		gameCamera->yaw += 0.25f*mouseSensitivity;

	if (mY < centerY/2)
		gameCamera->pitch += 0.25f*mouseSensitivity;
	if (mY > centerY/2)
		gameCamera->pitch -= 0.25f*mouseSensitivity;

	oldX = mX;
	oldY = mY;
}
