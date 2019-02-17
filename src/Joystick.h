/********************************************************/
/** \file   Joystick.h 
	\brief  Contains the CJoystick class

    \author José Maria Arnau
	\date   11/09/2006
*********************************************************/

#ifndef __JOYSTICK_INCLUDED__
#define __JOYSTICK_INCLUDED__


#include <SDL/SDL.h>

/********************************************************/
/** \class CJoystick
	\brief This class controls a joystick or gamepad.
*********************************************************/
class CJoystick
{
public:
  CJoystick();
  ~CJoystick();

  bool  Update();
};

#endif 
