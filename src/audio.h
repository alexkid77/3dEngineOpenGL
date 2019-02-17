/***********************************************************************************/
/** \file  audio.h
	\brief Contains the CAudio class

	\author Jose Maria Arnau
	\date   01/12/2006
************************************************************************************/

#ifndef __AUDIO_H
#define __AUDIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>


/***********************************************************************************/
/**	\class CAudio

	\brief The CAudio class represents a single sound object, such as a song, 
		   ambient sound, an object's sound, etc.
************************************************************************************/
class CAudio
{
private:
	/** Pointer to the sound data buffer */
	Mix_Chunk *sound;   

	/** Channel number where the sound will be played. 
        If this sound has no assigned channel, channel = -1 */
	int channel;

public:
	CAudio();
	~CAudio();

	void SetSound(Mix_Chunk * s);
	Mix_Chunk* GetSound() { return sound; }

	int GetChannel() { return channel; }
    void SetChannel(int channel) { channel = channel; }

	void SetVolume(float volume);

	void Set3DPos(float x, float y, float z) {}
};

#endif
