#include "oglwindow.h"
#include <cstdlib>

/**************************************************************************/
/**	\file  oglwindow.cpp
	\brief COGLWindow implementation                                      */

bool bLMB = false;		// left mouse button
bool bRMB = false;		// right mouse button
bool Drag = false;		// mouse drag


/**************************************************************************/
//  Destroy()
/** destroy the window
***************************************************************************/
void COGLWindow::Destroy()
{
	delete inputSystem;

	EndFullScreen();

	SDL_ShowCursor(SDL_ENABLE);
	SDL_FreeSurface(screen);

	SDL_Quit();
	exit(0);
}


/**************************************************************************/
//  Size()
/** window resizing
***************************************************************************/
void COGLWindow::Size()
{
	if (width > height)
		aspect = width;
	else
		aspect = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(54.0f, (float)width/(float)height, 0.1f, 5000.0f);

	//gluPerspective(54.0f, (float)width/(float)height, 8, 512);
//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	OnSize();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/**************************************************************************/
//  GetPosX()
/** get mouse X normalized position
***************************************************************************/
float COGLWindow::GetNormalizedPosX(int x)
{	
	return mouseSensitivity * (float)(x - width/2) / aspect;
}


/**************************************************************************/
//  GetPosY()
/** get mouse Y normalized position
***************************************************************************/
float COGLWindow::GetNormalizedPosY(int y)
{
	return mouseSensitivity * (float)(y - height/2) / aspect;
}


/**************************************************************************/
//  WndProcOGL()
/** the WndProc for the OpenGL window
***************************************************************************/
int COGLWindow::WndProcOGL(SDL_Event event)
{
	// dispatch messages
	switch (event.type)
	{	
		case SDL_QUIT:				// window close
			Destroy();
			return 0;

		case SDL_ACTIVEEVENT:		// activate app
			if (event.active.gain)
			{	
				if (fullscreen)
					BeginFullScreen(width, height, bits);
			}
			else
			{	
				if (fullscreen)
					EndFullScreen();
			}
			return 0;

		case SDL_VIDEORESIZE:		// window size
			width  = event.resize.w;
			height = event.resize.h;
			Size();
			return 0;

		case SDL_MOUSEBUTTONDOWN:
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:		// left mouse button
					if (!useInput)
					{
						Drag = true;
						bLMB = true;
						OnMouseDownL(GetNormalizedPosX(event.button.x), GetNormalizedPosY(event.button.y));
					}
					break;

				case SDL_BUTTON_RIGHT:		// right mouse button
					if (!useInput)
					{
						Drag = true;
						bRMB = true;
						OnMouseDownR(GetNormalizedPosX(event.button.x), GetNormalizedPosY(event.button.y));
					}
					break;

				default:
					break;
			}
			break;

		case SDL_MOUSEMOTION:		// mouse movement
		{	
			if (!useInput)
			{
				int x  = mouseX = event.motion.x; 
				int y  = mouseY = event.motion.y;
				int dx = event.motion.xrel;
				int dy = event.motion.yrel;

				OnMouseMove(x,y, width, height);

				if (Drag)
				{
					// left mouse button
					if (bLMB)
					{
						OnMouseDragL(x,y, dx,dy);
					}
					
					// right mouse button
					if (bRMB)
					{	
						OnMouseDragR(x,y, dx,dy);
					}
				}
			}
			break;
		}

		case SDL_MOUSEBUTTONUP:
			switch(event.button.button)
			{
				case SDL_BUTTON_LEFT:			// left button release
					if (!useInput)
					{
						if (Drag && !bRMB)
						{
							Drag = false;
						}
						bLMB = false;
						OnMouseUpL();
					}
					break;
			
				case SDL_BUTTON_RIGHT:  		// right button release
					if (!useInput)
					{
						if (Drag && !bLMB)
						{
							Drag = false;
						}
						bRMB = false;
						OnMouseUpR();
					}
					break;
				
				default:
					break;
			}
			break;

		case SDL_KEYUP:
			if (!useInput)
			{
				OnKeyUp(event.key.keysym.sym);
			}
			return 0;

		case SDL_KEYDOWN:
			if (!useInput)
			{
				OnKeyDown(event.key.keysym.sym);
			}
			return 0;

		default:
			break;
	}
	return 0;
}


/**************************************************************************/
//  BeginFullScreen()
/** go to full screen widthXheight resolution
    and save original state
***************************************************************************/
void COGLWindow::BeginFullScreen(int width, int height, int bits)
{
	if(!fullscreen)
	{
		SDL_WM_ToggleFullScreen(screen);
		fullscreen = true;
	}
}


/**************************************************************************/
//  EndFullScreen()
/** return to desktop at original resolution
***************************************************************************/
void COGLWindow::EndFullScreen()
{
	if(fullscreen)
	{
		SDL_WM_ToggleFullScreen(screen);
		fullscreen = false;
	}
}


/**************************************************************************/
/** COGLWindow constructor
***************************************************************************/
COGLWindow::COGLWindow(const char *szName, bool fscreen, int w, int h, int b)
{
	fullscreen = fscreen;
	width = w;
	height = h;
	bits = b;

	/* start SDL library with video support */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError( ) );
        exit( 1 );
    }

	/* with the flag SDL_OPENGL the window is created with a opengl render context */
	flags = SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF | ((fscreen) ? SDL_FULLSCREEN : SDL_RESIZABLE);	

	/* create the window */
    SDL_WM_SetCaption(szName,NULL);
    if( (screen = SDL_SetVideoMode( width, height, bits, flags )) == 0 ) {
        fprintf( stderr, "Video mode set failed: %s\n", SDL_GetError( ) );
        exit( 1 );
    }

	if (fullscreen)
	{
		SDL_WM_ToggleFullScreen(screen);
		
	}
	
	mouseSensitivity = 1.0f;

	inputSystem = new CInputSystem(IS_USEKEYBOARD | IS_USEMOUSE);
	useInput = true;

	if (useInput)
		inputSystem->Update();

	SDL_ShowCursor(SDL_DISABLE);
}


/**************************************************************************/
/** COGLWindow destructor
***************************************************************************/
COGLWindow::~COGLWindow()
{
	Destroy();
}
