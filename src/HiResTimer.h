/***************************************************************************/
/** \file HiResTimer.h

	\brief Contains the CHiResTimer class 
	\author  Dave Astle
	\date    2/1/2001

 	 Modificado por José María Arnau el 11/09/2006
****************************************************************************/

#ifndef __TIMER_H_INCLUDED__
#define __TIMER_H_INCLUDED__

#include <SDL/SDL.h>

/***************************************************************************/
/** \class CHiResTimer
	
	\brief Wrapper for the high-resolution timer. This class uses the SDL
           high resolution timers.
****************************************************************************/
class CHiResTimer
{
public:
  CHiResTimer() {}
  ~CHiResTimer() {}

  bool Init();
  float GetElapsedSeconds(unsigned long elapsedFrames = 1);
  float GetFPS(unsigned long elapsedFrames = 1);
  float LockFPS(unsigned char targetFPS);

private:
  /** Object creation instant */
  Uint32 m_startTime;
};

#endif // __TIMER_H_INCLUDED_
