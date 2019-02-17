/*******************************************************/
/** \file Keyboard.h 
	\brief Contains the CKeyboard class

    \author José Mª Arnau
	\date   11/09/2006
********************************************************/

#ifndef __KEYBOARD_INCLUDED__
#define __KEYBOARD_INCLUDED__


#include <SDL/SDL.h>

/*******************************************************/
/** \class CKeyboard
	\brief This class controls the keyboard
********************************************************/
class CKeyboard
{
public:
  bool  KeyDown(SDLKey key); 
  bool  KeyUp(SDLKey key);

  bool  Update();

private:
  Uint8 *m_keys;
};

#endif
