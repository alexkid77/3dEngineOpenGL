/*******************************************************************************/
/**	\file camera.h

	\brief The interface for CCamera - the camera system

	\author: Kevin Hawkins
	\date: 3/29/2001

********************************************************************************/

#ifndef __CAMERA_H
#define __CAMERA_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "vector.h"

class CObject;

/*******************************************************************************/
/** \class CCamera

	\brief The CCamera class is the camera system
********************************************************************************/
class CCamera
{
private:
	// these are used for moving and changing camera orientation
	// through the MoveTo/LookTo methods
	CVector initPosition, finalPosition;
	CVector initLookAt, finalLookAt;

	/** velocity for looking at objects */
	CVector lookAtVel;			

	/** acceleration for looking at objects */
	CVector lookAtAccel;	

	void UpdateLookAt();
	void UpdateMoveTo();

public:
	CVector position;			// position of camera
	
	CVector velocity;			// velocity of camera
	CVector acceleration;		// acceleration of camera
	CVector lookAt;			    // lookat vector

	// up, forward, right vectors
	CVector up;
	CVector forward;
	CVector right;

	// yaw and pitch angles
	float yaw;
	float pitch;

	int screenWidth, screenHeight;
	int centerX, centerY;
CVector posicion_antigua;
	CCamera();
	CCamera(int width, int height) {}
	CCamera(CVector *look);
	CCamera(CVector *pos, CVector *look);
	~CCamera();

	void LookAt(CObject *object);
	void LookAtNow(CObject *object);
	void MoveTo(CObject *object);
	void MoveToNow(CObject *object);
	void MoveToNow(scalar_t x, scalar_t y, scalar_t z);

	// right rotation along y-axis (yaw)
	void RotateYaw(scalar_t radians);
	void RotatePitch(scalar_t radians);
	void RotateRoll(scalar_t radians);

	/** do physics calculations */
	void Animate(scalar_t deltaTime);
};

#endif
