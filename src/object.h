/********************************************************************************/
/** \file  object.h
	\brief Contains the CObject class

	\author Kevin Hawkins
	\date   3/29/2001
*********************************************************************************/

#ifndef __OBJECT_H
#define __OBJECT_H

#include "tree.h"
#include "vector.h"
#include "camera.h"


/********************************************************************************/
/** \class CObject
	\brief The CObject class is derived from CNode and
		   represents an object in the game world.
*********************************************************************************/
class CObject : public CNode
{
protected:
	/*	bool bDelete; */

	/** perform basic physics on the object */
	virtual void OnAnimate(scalar_t deltaTime) 
	{
		position += velocity * deltaTime;
		velocity += acceleration * deltaTime;
	}

	/** draw the object given the camera position */
	virtual void OnDraw(CCamera *camera) {}	

	/** collide with other objects */
	virtual void OnCollision(CObject *collisionObject) {}

	/** perform collision and other preparations for this object */
	virtual void OnPrepare() 
	{
		ProcessCollisions(FindRoot());	// perform collisions starting with
									    // root world object
	}

public:
	CVector position;		// object position
	CVector velocity;		// velocity of object
	CVector acceleration;	// acceleration
	scalar_t size;			// size of bounding sphere (radius)

	bool isDead;

	CObject() { isDead = false; }
	~CObject() {}

	virtual void Load() {}
	virtual void Unload() {}

	// draw object
	void Draw(CCamera *camera); 

	// animate object
	void Animate(scalar_t deltaTime); 

	// perform collision detection
	void ProcessCollisions(CObject *obj); 

	// prepare object
	void Prepare();

	// find root object of cyclic linked list tree
	CObject *FindRoot();
};


#endif
