#include "audiosystem.h"
#include <iostream>
#include <cstdlib>
using namespace std;

/********************************************************************/
/**	\file audiosystem.cpp
    \brief The CAudioSystem implementation                         */


/********************************************************************/
/** CAudioSystem class Constructor.

	Start SDL_mixer library.
	\param num_channels Number of channels to play sounds           
*********************************************************************/
CAudioSystem::CAudioSystem(int num_channels)
{
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		cerr << "Mix_OpenAudio: " << Mix_GetError() << endl;
		exit(-1);
	}

	NumChannels = num_channels;
	Mix_AllocateChannels(NumChannels);
	music = NULL;
}


/********************************************************************/
/** CAudioSystem class destructor 
	Close SDL_mixer library
*********************************************************************/
CAudioSystem::~CAudioSystem()
{
    Mix_CloseAudio();
	if (music)
		Mix_FreeMusic(music);
}


/********************************************************************/
/** \brief Play a CAudio object 
	\param audio Pointer to the CAudio object 
	\param loop True for infinite loops, False to play only one time 
*********************************************************************/
void CAudioSystem::Play(CAudio *audio, bool loop)
{
	int repeat = loop ? -1:0;
	int channel = Mix_PlayChannel(-1, audio->GetSound(), repeat);	
	audio->SetChannel(channel);
}


/********************************************************************/
/** \brief Stop a CAudio object from playing 
*********************************************************************/
void CAudioSystem::Stop(CAudio *audio)
{
	Mix_HaltChannel(audio->GetChannel());
}


/********************************************************************/
/** \return True if the source is playing, False otherwise 
*********************************************************************/
bool CAudioSystem::IsPlaying(CAudio *audio)
{
	return Mix_Playing(audio->GetChannel());
}


/********************************************************************/
/** \brief Create a CAudio object 
	\param filename File with sound data (WAVE format only) 
	\param Is3DSound True to apply 3D effects
*********************************************************************/
CAudio *CAudioSystem::Create(char *filename, bool Is3DSound)
{
	CAudio *audio = new CAudio;
	Mix_Chunk *sample = Mix_LoadWAV(filename);

	audio->SetSound(sample);
	return audio;
}


/********************************************************************/
/**	\brief Play an audio file in any format
	\param filename File with sound data
	\param repeat Number of times to play through the music, 
           -1 plays the music forever
*********************************************************************/
void CAudioSystem::PlayMusic(char *filename, int repeat) {
	music = Mix_LoadMUS(filename);
	Mix_PlayMusic(music,repeat);
}


/********************************************************************/
/**	\brief Stop music from playing 
*********************************************************************/
void CAudioSystem::StopMusic() {
	Mix_HaltMusic();
}


/********************************************************************/
/**	\brief Change music volume
    \param volume Number between 0 and MIX_MAX_VOLUME (128)
*********************************************************************/
void CAudioSystem::SetMusicVolume(int volume) {
	Mix_VolumeMusic(volume);
}


/********************************************************************/
/** \return True if music channel is playing now
*********************************************************************/
bool CAudioSystem::IsMusicPlaying() {
	return Mix_PlayingMusic();
}

