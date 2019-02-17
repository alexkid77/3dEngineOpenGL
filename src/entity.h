/*******************************************************************************/
/** \file entity.h
	\brief Contains the CEntity class

	\author Kevin Hawkins
	\date   3/29/2001
********************************************************************************/

#ifndef __ENTITY_H
#define __ENTITY_H

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>

#include "md2.h"
#include "object.h"
#include "camera.h"
#include "audiosystem.h"
#include "terrain.h"


/*******************************************************************************/
/** \class CEntity
	\brief Provides the functionality of an entity in the game world

	The CEntity class is derived from CMD2Model and
	provides the functionality of an entity in the
	game world. It holds the current MD2 animation
	state, the entity angle heading, and the entity's
	primary sound.
********************************************************************************/
class CEntity : public CMD2Model
{
protected:
     void OnAnimate(float deltaTime);
     void OnDraw(CCamera *camera);
     void OnCollision(CObject *collisionObject);
     void OnPrepare();

     void PlaySound() { audioSys->Play(entitySound, false); }
public:
	 /** angle the entity is facing (in radians) */
     float direction;        

	 /** the sound the entity makes currently only supports 
		 one sound per entity */
     CAudio *entitySound;    

 	 /** a pointer to the audio system */
     CAudioSystem *audioSys; 

     CEntity();
     ~CEntity();

     int stateStart, stateEnd;     // state keyframe start/end
     float deltaT;
     float animSpeed;

     void LoadAudio(CAudioSystem *audioSystem, char *filename, bool is3DSound);
     void SetAudioSystem(CAudioSystem *asys) { audioSys = asys; }
};

#endif
