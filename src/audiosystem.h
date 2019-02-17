/******************************************************************************/
/**	\file audiosystem.h
	\brief Contains the CAudioSystem class

	\author Jose Maria Arnau
	\date   01/12/2006
*******************************************************************************/

#ifndef __AUDIOSYSTEM_H
#define __AUDIOSYSTEM_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include "audio.h"


/******************************************************************************/
/**
	\class CAudioSystem
	\brief The CAudioSystem class is the controller for creating and
		   playing CAudio objects.

	The CAudioSystem class has been developed using SDL_mixer. This library
 	provides one channel to play music in any format (WAVE, MOD, MIDI, OGG,
	MP3...) and many other channels to play sounds in WAVE format. 
*******************************************************************************/
class CAudioSystem
{
private:
	/** Number of channels to play sounds */
	int NumChannels;

	/** Pointer to music data buffer */
	Mix_Music *music;

public:
	CAudioSystem(int num_channels = 64);
	~CAudioSystem();

	CAudio *Create(char *filename, bool is3DSound);
	
	void Play(CAudio *audio, bool loop);
	void Stop(CAudio *audio);

	bool IsPlaying(CAudio *audio);

	void PlayMusic(char *filename, int repeat);
	void StopMusic();
	void SetMusicVolume(int volume);
	bool IsMusicPlaying();

	void SetListenerPos(float cameraX, float cameraY, float cameraZ) {}
	void SetListenerOrientation(float forwardX, float forwardY, float forwardZ, float topX, float topY, float topZ) {}
};

#endif
