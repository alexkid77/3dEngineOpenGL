#include "audio.h"

/***************************************************************/
/** \file audio.cpp
	\brief The CAudio implementation                           */


/***************************************************************/
/** The CAudio class constructor           
****************************************************************/
CAudio::CAudio() {
	sound = NULL;
	channel = -1;
}


/***************************************************************/
/** The CAudio class destructor           
****************************************************************/
CAudio::~CAudio() {
	if (sound)
		Mix_FreeChunk(sound);
	sound = NULL;
}


/***************************************************************/
/** Set the new buffer for sound data 
	(and free the old buffer if it is not NULL).
	\param s Pointer to the new sound data buffer           
****************************************************************/
void CAudio::SetSound(Mix_Chunk * s) {
	if (sound)
		Mix_FreeChunk(sound);
	sound = s;
}


/***************************************************************/
/** \param volume number between 0 and MIX_MAX_VOLUME (128) 
****************************************************************/
void CAudio::SetVolume(float volume)
{
	int v = int(volume);

	if (sound)
		Mix_VolumeChunk(sound, v);

	if (channel != -1)
		Mix_Volume(channel, v);
}

