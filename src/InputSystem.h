/**************************************************************************/
/** \file InputSystem.h
	\brief Contains the CInputSystem class

    \author José Mª Arnau
	\date   11/09/2006
***************************************************************************/

#ifndef __INPUT_SYSTEM_INCLUDED__
#define __INPUT_SYSTEM_INCLUDED__

#include <SDL/SDL.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "Joystick.h"

#define IS_USEKEYBOARD  1
#define IS_USEMOUSE     2
#define IS_USEJOYSTICK  4

/**************************************************************************/
/** \class CInputSystem
	\brief This class controls input events: keyboard, mouse and
           joysticks events.
***************************************************************************/
class CInputSystem
{
public:
  CInputSystem(int flags);
  ~CInputSystem();

  CKeyboard  *GetKeyboard() { return m_pKeyboard; }
  CMouse     *GetMouse()    { return m_pMouse; }
  CJoystick  *GetJoystick() { return m_pJoystick; }

  bool  Update();

  bool  KeyDown(SDLKey key) { return (m_pKeyboard && m_pKeyboard->KeyDown(key)); }
  bool  KeyUp(SDLKey key)   { return (m_pKeyboard && m_pKeyboard->KeyUp(key)); }

  bool  ButtonDown(int button) { return (m_pMouse && m_pMouse->ButtonDown(button)); }
  bool  ButtonUp(int button) { return (m_pMouse && m_pMouse->ButtonUp(button)); }

  /** dx and dy are set to the change in the mouse position since the last call  */
  void  GetMouseMovement(int &dx, int &dy) { if (m_pMouse) m_pMouse->GetMovement(dx, dy); }

private:
  CKeyboard  *m_pKeyboard;
  CMouse     *m_pMouse;
  CJoystick  *m_pJoystick;
};

/***************************************************************************
	SDL mouse constants:
		SDL_BUTTON_LEFT      
		SDL_BUTTON_MIDDLE   
		SDL_BUTTON_RIGHT     
		SDL_BUTTON_WHEELUP    
		SDL_BUTTON_WHEELDOWN  
			
	Some SDL keyboard constants:
 
        *** SDLKey ***    *** Common name ***
        SDLK_BACKSPACE    backspace
        SDLK_TAB          tab
        SDLK_CLEAR        clear
        SDLK_RETURN       return
        SDLK_ESCAPE       escape
        SDLK_SPACE        space
        SDLK_DOLLAR       dollar
        SDLK_AMPERSAND    ampersand
        SDLK_ASTERISK     asterisk
        SDLK_PLUS         plus sign
        SDLK_COMMA        comma
        SDLK_MINUS 	      minus sign
        SDLK_PERIOD       period / full stop
        SDLK_0            0
		SDLK_1            1
		SDLK_2            2
		SDLK_3 	    	  3
		SDLK_4 	    	  4
		SDLK_5 	    	  5
		SDLK_6 	    	  6
		SDLK_7 	 	      7
		SDLK_8 		      8
		SDLK_9 	 	      9
		SDLK_a 	 	      a
		SDLK_b 	 	      b
		SDLK_c 	 	      c
		SDLK_d 	 	      d
		SDLK_e 	 	      e
		SDLK_f 		      f
		SDLK_g 	 	      g
		SDLK_h 	 	      h
		SDLK_i 	 	      i
		SDLK_j 	 	      j
		SDLK_k 	 	      k
		SDLK_l 	 	      l
		SDLK_m 	 	      m
		SDLK_n 	 	      n
		SDLK_o 	 	      o
		SDLK_p 	 	      p   
		SDLK_q 	 	      q
		SDLK_r 	 	      r
		SDLK_s 	 	      s
		SDLK_t 	 	      t
		SDLK_u 	 	      u
		SDLK_v 	 	      v
		SDLK_w 	 	      w
		SDLK_x 	 	      x
		SDLK_y 	 	      y
		SDLK_z 	 	      z
		SDLK_DELETE 	  delete
		SDLK_KP0 		  keypad 0
		SDLK_KP1 		  keypad 1
		SDLK_KP2 		  keypad 2
		SDLK_KP3 		  keypad 3
		SDLK_KP4 		  keypad 4
		SDLK_KP5 		  keypad 5
		SDLK_KP6 		  keypad 6
		SDLK_KP7 		  keypad 7
		SDLK_KP8 		  keypad 8
		SDLK_KP9 		  keypad 9
		SDLK_UP 		  up arrow
		SDLK_DOWN 		  down arrow
		SDLK_RIGHT 		  right arrow
		SDLK_LEFT 		  left arrow
		SDLK_INSERT 	  insert
		SDLK_HOME 		  home
		SDLK_END 		  end
		SDLK_PAGEUP 	  page up
		SDLK_PAGEDOWN 	  page down
		SDLK_F1 		  F1
		SDLK_F2 		  F2
		SDLK_F3 		  F3
		SDLK_F4 		  F4
		SDLK_F5 		  F5
		SDLK_F6 		  F6
		SDLK_F7 		  F7
		SDLK_F8 		  F8
		SDLK_F9 		  F9
		SDLK_F10 		  F10
		SDLK_F11 		  F11
		SDLK_F12 		  F12
		SDLK_F13 		  F13
		SDLK_F14 		  F14
		SDLK_F15 		  F15
		SDLK_RSHIFT 	  right shift
		SDLK_LSHIFT 	  left shift
		SDLK_RCTRL 		  right ctrl
		SDLK_LCTRL 		  left ctrl
		SDLK_RALT 		  right alt / alt gr
		SDLK_LALT 		  left alt
		SDLK_RMETA 		  right meta
		SDLK_LMETA 		  left meta
		SDLK_PRINT 		  print-screen
		SDLK_UNDO 		  undo

***************************************************************************/

#endif 
