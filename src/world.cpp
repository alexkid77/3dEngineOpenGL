#include "world.h"

/**********************************************************************/
/** \file  world.cpp
	\brief The CWorld class implementation                            */


/**********************************************************************/
/** CWorld constructor
***********************************************************************/
CWorld::CWorld()
{
	terrain = new CTerrain(256, 0.5);
}


/**********************************************************************/
/** CWorld destructor
***********************************************************************/
CWorld::~CWorld()
{
	delete terrain;
	delete audioSystem;
	delete worldSound;
}


/**********************************************************************/
/** CWorld constructor
***********************************************************************/
CWorld::CWorld(CCamera *c)
{
	camera = c;
	terrain = new CTerrain(256, 0.6f);
	enemy = new CEntity;
	enemy2 = new CEntity;
	enemy3 = new CEntity;
	//nivel= new CNivel("models\\final3.bsp");
	nivel= new CNivel("models\\final3.bsp");
	msg=new CFont("Arial", 16);
	frames_por_segundo=new CFont("Arial", 16);
	temporizador=new CHiResTimer;
	audioSystem = new CAudioSystem;
	temporizador->Init();
	enemy->AttachTo(terrain);
	enemy2->AttachTo(terrain);

	worldSound = audioSystem->Create("sounds\\musica.ogg", false);
	
	audioSystem->Play(worldSound, true);
	
	enemy->Load("models\\sodf8\\tris.md2", "models\\sodf8\\abarlith.pcx");
	enemy->SetState(MODEL_RUN);
	enemy->direction = 45.0;

	enemy2->Load("models\\ogro\\tris.md2", "models\\ogro\\ogrobase.pcx");
	enemy2->SetState(MODEL_RUN);
	enemy2->direction = 225.0;
		enemy2->position = CVector(200.0, 0.0, 200.0);
	
	
    	
	enemy3->Load("models\\ogro\\tris.md2", "models\\ogro\\ogrobase.pcx");
enemy3->position = CVector(0.0, 0.0, 0.0);
camera->position.y=100;
camera->position.x=0;
camera->position.z=00;
}


/**********************************************************************/
/** Animetes the camera and all objects in the scene
***********************************************************************/
void CWorld::Animate(float deltaTime)
{
	CVector nueva_posicion;
	// set camera height based on position on terrain
//	camera->position.y = terrain->GetHeight(camera->position.x, camera->position.z) + 10.0f;
nueva_posicion=nivel->TrazaEsfera(camera->posicion_antigua,camera->position,15.0f);
//if(nivel->colision)	
 //camera->position=camera->posicion_antigua;
 

	camera->position=nueva_posicion;
   

terrain->Animate(deltaTime);

}


/**********************************************************************/
/** Draw the scene
***********************************************************************/
void CWorld::Draw(CCamera *camera)
{
	
	msg->SetPos3D(0.25,0.25,0);
frames_por_segundo->SetPos3D(0.15,0.35,0);
	msg->SetRGB(0,1,0);
	frames_por_segundo->SetRGB(0,1,0);
	msg->Print("triangulos dibujados:%d",nivel->triangulos);
	frames_por_segundo->Print("X:%f Y:%f Z:%f",camera->position.x,camera->position.y,camera->position.z);
	//terrain->Draw(camera);
	enemy3->Draw(camera);
	//glTranslatef(100,158,100);
	
	
	/*   glPushMatrix();
    glLoadIdentity();
    glEnable(GL_BLEND);
     glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
    glDisable(GL_TEXTURE_2D);
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-5, -5, -3.0);
    glVertex3f(5, -5, -3.0);
    glVertex3f(5, 5, -3.0);
    glVertex3f(-5, 5, -3.0);
    glEnd();
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glPopMatrix();*/
	 
/*	glEnable(GL_BLEND);
    glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);*/
		glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3ub(255,0,0);
	glVertex3f(0,0,0);

	glColor3ub(0,255,0);
	glVertex3f(0,10,0);

	glColor3ub(255,255,255);
	glVertex3f(0,0,10);
	glEnd();
	glPopMatrix();

	nivel->Draw(camera);

 //glDisable(GL_BLEND);
}


/**********************************************************************/
/** Prepare all objects 
***********************************************************************/
void CWorld::OnPrepare()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//nivel->ComprobarNodo(0,1
//camera->position.y=100;
//camera->position.x=1050;
//camera->position.z=1050;
	//terrain->Prepare();
	
	
}
