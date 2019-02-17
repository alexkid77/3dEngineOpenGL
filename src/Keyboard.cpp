#include "Keyboard.h"

/****************************************************/
/** \file Keyboard.cpp
	\brief The CKeyboard class implementation       */


/****************************************************/
/** \return True if 'key' is pressed
*****************************************************/
bool CKeyboard::KeyDown(SDLKey key)
{
  return m_keys[key];
}


/****************************************************/
/** \return False if 'key' is pressed
*****************************************************/
bool CKeyboard::KeyUp(SDLKey key)
{
  return !(m_keys[key]);
}


/****************************************************/
/** Update keyboard state
*****************************************************/
bool CKeyboard::Update()
{
  m_keys = SDL_GetKeyState(NULL);		
  return true;
}
