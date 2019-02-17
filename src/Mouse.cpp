#include "Mouse.h"

/********************************************************************/
/** \file Mouse.cpp
	\brief Contains the CMouse implementation                       */


/********************************************************************/
/** \return True if 'button' is pressed
	\param button SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, 
                  SDL_BUTTON_RIGHT, SDL_BUTTON_WHEELUP,
                  SDL_BUTTON_WHEELDOWN
*********************************************************************/
bool CMouse::ButtonDown(int button)
{
  return m_state.buttons[button];
}


/********************************************************************/
/** \return False if 'button' is pressed
	\param button SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, 
                  SDL_BUTTON_RIGHT, SDL_BUTTON_WHEELUP,
                  SDL_BUTTON_WHEELDOWN
*********************************************************************/
bool CMouse::ButtonUp(int button)
{
  return !(m_state.buttons[button]);
}	


/********************************************************************/
/** dx and dy are set to the change in the mouse position 
    since the last call
*********************************************************************/
void  CMouse::GetMovement(int &dx, int &dy)
{
  dx = m_state.x;
  dy = m_state.y;
}


/********************************************************************/
/** Update mouse state
*********************************************************************/
bool CMouse::Update()
{
  Uint8 button_mask;
  button_mask = SDL_GetRelativeMouseState(&m_state.x, &m_state.y);
  for(int i=1; i<= N_MOUSE_BUTTONS; i++)
	m_state.buttons[i] = button_mask & SDL_BUTTON(i);

  return true;
}

