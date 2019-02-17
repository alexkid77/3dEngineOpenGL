/********************************************************/
/** \file Mouse.h
	\brief Contains the CMouse class

    \author José Mª Arnau
	\date   11/09/2006
	              
*********************************************************/

#ifndef __MOUSE_INCLUDED__
#define __MOUSE_INCLUDED__

#include <SDL/SDL.h>

#define N_MOUSE_BUTTONS 5

/*
SDL_BUTTON_LEFT       = 1
SDL_BUTTON_MIDDLE     = 2
SDL_BUTTON_RIGHT      = 3
SDL_BUTTON_WHEELUP    = 4
SDL_BUTTON_WHEELDOWN  = 5
*/

struct MouseState
{
  int x,y;
  bool buttons[N_MOUSE_BUTTONS+1];
};


/********************************************************/
/** \class CMouse
	\brief This class controls the mouse
*********************************************************/
class CMouse
{
public:
  bool  ButtonDown(int button);
  bool  ButtonUp(int button);
  void  GetMovement(int &dx, int &dy); 

  bool  Update();

private:
  MouseState m_state;
};


#endif
