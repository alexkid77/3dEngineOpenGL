#include "HiResTimer.h"

/****************************************************************************/
/** \file HiResTimer.cpp
    \brief Contains the CHiResTimer implementation                          */


/****************************************************************************/
/**
 If the hi-res timer is present, the tick rate is stored and the function
 returns true. Otherwise, the function returns false, and the timer should
 not be used.
*****************************************************************************/
bool CHiResTimer::Init()
{
  m_startTime = SDL_GetTicks();
  return true;
} // end Init()


/****************************************************************************/
/** \return Number of seconds since the last call to GetElapsedSeconds
	\param elapsedFrames Number of frames since last call
*****************************************************************************/
float CHiResTimer::GetElapsedSeconds(unsigned long elapsedFrames)
{
  static Uint32 s_lastTime = m_startTime;
  Uint32 currentTime;

  currentTime = SDL_GetTicks();
  float seconds = ((float)currentTime - (float)s_lastTime) / 1000.0;

  s_lastTime = currentTime;

  return seconds;
} // end GetElapsedSeconds()


/**************************************************************************/
/**
 Returns the average frames per second over elapsedFrames, which defaults to
 one. If this is not called every frame, the client should track the number
 of frames itself, and reset the value after this is called.
***************************************************************************/
float CHiResTimer::GetFPS(unsigned long elapsedFrames)
{
  static Uint32 s_lastTime = m_startTime;
  Uint32 currentTime;

  currentTime = SDL_GetTicks();
  float fps = (float)elapsedFrames * 1000.0 / ((float)currentTime - (float)s_lastTime);

  s_lastTime = currentTime;

  return fps;
} // end GetFPS


/**************************************************************************/
/**
 Used to lock the frame rate to a set amount. This will block until enough
 time has passed to ensure that the fps won't go over the requested amount.
 Note that this can only keep the fps from going above the specified level;
 it can still drop below it. It is assumed that if used, this function will
 be called every frame. The value returned is the instantaneous fps, which
 will be <= targetFPS.
***************************************************************************/
float CHiResTimer::LockFPS(unsigned char targetFPS)
{
  if (targetFPS == 0)
    targetFPS = 1;

  static Uint32 s_lastTime = m_startTime;
  Uint32 currentTime;
  float fps;

  do{
    currentTime = SDL_GetTicks();
    fps = 1000.0 / ((float)(currentTime - s_lastTime));
  }while(fps > (float)targetFPS);

  s_lastTime = currentTime;

  return fps;
} // end LockFPS()

