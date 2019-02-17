/***********************************************************************/
/**	\file world.h
\brief The CWorld class

\author Kevin Hawkins
\date   3/29/2001
Description:
************************************************************************/

#ifndef __WORLD_H
#define __WORLD_H

#include "entity.h"
#include "md2.h"
#include "object.h"
#include "camera.h"
#include "terrain.h"
#include "audiosystem.h"
#include "tree.h"
#include "q3loader.h"
#include "nivel.h"
#include "HiResTimer.h"
/***********************************************************************/
/** \class CWorld
\brief The CWorld class represents the game world 
of the engine. All objects, the terrain,
audio system, ambient world music and sound,
and the camera are held here.
************************************************************************/
class CWorld
{
protected:
	void OnAnimate(float deltaTime);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:

	CTerrain *terrain;            // the terrain
	CCamera *camera;              // the camera
	CEntity *enemy;               // enemy 1
	CEntity *enemy2;              // enemy 2
	CEntity *enemy3;              // enemy 2
	CAudioSystem *audioSystem;    // the audio system
	CAudio *worldSound;           // the world ambient sound
	CAudio *gameMusic;            // the game's music
	
	CNivel *nivel;
	CFont *msg;
	CFont *frames_por_segundo;
	CHiResTimer * temporizador;
	CWorld();
	CWorld(CCamera *c);
	~CWorld();

	// initialize terrain, load objects and put in container
	void LoadWorld();
	void UnloadWorld();

	// do physics calculations for all objects in the world
	// including collisions
	void Animate(float deltaTime);

	// render all objects in the world
	void Draw(CCamera *camera);

	void Prepare() { OnPrepare(); }
};


#endif