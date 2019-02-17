#include "object.h"

/****************************************************************************/
/** \file object.cpp
	\brief The CObject class implementation                                 */


/****************************************************************************/
/** draw object
*****************************************************************************/
void CObject::Draw(CCamera *camera) 
{
	// push modelview matrix on stack
	glPushMatrix();
		OnDraw(camera);		// draw this object
		if (HasChild())		// draw children
			((CObject*)childNode)->Draw(camera);
	glPopMatrix();

	// draw siblings
	if (HasParent() && !IsLastChild())
		((CObject*)nextNode)->Draw(camera);
}


/****************************************************************************/
/** animate object
*****************************************************************************/
void CObject::Animate(scalar_t deltaTime) 
{
	OnAnimate(deltaTime);		// animate this object

	// animate children
	if (HasChild())
		((CObject*)childNode)->Animate(deltaTime);

	// animate siblings
	if (HasParent() && !IsLastChild())
		((CObject*)nextNode)->Animate(deltaTime);

	if (isDead)
		delete this;
}


/****************************************************************************/
/** perform collision detection
*****************************************************************************/
void CObject::ProcessCollisions(CObject *obj) 
{
	// if this object's bounding sphere collides with obj's sphere
	// and obj is not this object
	if (((obj->position - position).Length() <= (obj->size + size)) &&
		(obj != ((CObject*)this)))
	{
		OnCollision(obj);		// perform this object's collision with obj

		// test child collisions with obj
		if (HasChild())
			((CObject*)childNode)->ProcessCollisions(obj);

		// test sibling collisions with obj
		if (HasParent() && !IsLastChild())
			((CObject*)nextNode)->ProcessCollisions(obj);
	}

	// if obj has children, check collisions with these children
	if (obj->HasChild())
		ProcessCollisions((CObject*)(obj->childNode));

	// if obj has siblings, check collisions with these siblings
	if (obj->HasParent() && !obj->IsLastChild())
		ProcessCollisions((CObject*)(obj->nextNode));
}


/****************************************************************************/
/** prepare object
*****************************************************************************/
void CObject::Prepare()
{
	OnPrepare();						// prepare this object

	if (HasChild())					// prepare children
		((CObject*)childNode)->Prepare();

	if (HasParent() && !IsLastChild())		// prepare siblings
		((CObject*)nextNode)->Prepare();
}


/****************************************************************************/
/** find root object of cyclic linked list tree
*****************************************************************************/
CObject * CObject::FindRoot()
{
	// if this object has a parent node, return the root of the parent node
	if (parentNode)
		return ((CObject*)parentNode)->FindRoot();

	return this;
}

