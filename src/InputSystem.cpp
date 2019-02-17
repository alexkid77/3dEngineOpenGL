#include "InputSystem.h"

/*********************************************************************************************/
/** \file InputSystem.cpp
	\brief The CInputSystem class implementation                                             */


/*********************************************************************************************/
/** CInputSystem class constructor
	\param flags valid flags: IS_USEKEYBOARD, IS_USEMOUSE and IS_USEJOYSTICK.

	Use (IS_USEKEYBOARD | IS_USEMOUSE) to get keyboard and mouse control. 
	Joystick control is not yet implemented.
**********************************************************************************************/
CInputSystem::CInputSystem(int flags): m_pKeyboard(NULL), m_pMouse(NULL), m_pJoystick(NULL)
{
  if (flags & IS_USEKEYBOARD)
  {
    m_pKeyboard = new CKeyboard;
  }
  if (flags & IS_USEMOUSE)
  {
    m_pMouse = new CMouse;
  }
  if (flags & IS_USEJOYSTICK)
  {
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    m_pJoystick = new CJoystick;
  }
}


/*********************************************************************************************/
/** CInputSystem class desstructor
**********************************************************************************************/
CInputSystem::~CInputSystem()
{
  delete m_pKeyboard;
  delete m_pMouse;

  if (m_pJoystick)
  {
    delete m_pJoystick;
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
  }
}


/*********************************************************************************************/
/** Check input events to update keyboard and mouse state.
**********************************************************************************************/
bool CInputSystem::Update()
{
  /* Pumps the event loop, gathering events from the input devices */
  SDL_PumpEvents();

  if (m_pKeyboard)
    m_pKeyboard->Update();
  if (m_pMouse)
    m_pMouse->Update();
  if (m_pJoystick)
    m_pJoystick->Update();

  return true;
}

