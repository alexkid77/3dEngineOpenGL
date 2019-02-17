#include "md2.h"

/****************************************************************************/
/** \file md2.cpp
	\brief The CMD2Model implementation                                     */


/****************************************************************************/
//  CalculateNormal()
/** given 3 points, calculates the normal to the points
*****************************************************************************/
void CalculateNormal( float *p1, float *p2, float *p3 )
{
   float a[3], b[3], result[3];
   float length;

   a[0] = p1[0] - p2[0];
   a[1] = p1[1] - p2[1];
   a[2] = p1[2] - p2[2];

   b[0] = p1[0] - p3[0];
   b[1] = p1[1] - p3[1];
   b[2] = p1[2] - p3[2];

   result[0] = a[1] * b[2] - b[1] * a[2];
   result[1] = b[0] * a[2] - a[0] * b[2];
   result[2] = a[0] * b[1] - b[0] * a[1];

   // calculate the length of the normal
   length = (float)sqrt(result[0]*result[0] + result[1]*result[1] + result[2]*result[2]);

   // normalize and specify the normal
   glNormal3f(result[0]/length, result[1]/length, result[2]/length);
}


/****************************************************************************/
/** vector subtraction
*****************************************************************************/
vector_t operator-(vector_t a, vector_t b)
{
	vector_t c;

	c.point[0] = a.point[0] - b.point[0];
	c.point[1] = a.point[1] - b.point[1];
	c.point[2] = a.point[2] - b.point[2];

	return c;
}


/****************************************************************************/
/** scalar-vector multiplication
*****************************************************************************/
vector_t operator*(float f, vector_t b)
{
	vector_t c;

	c.point[0] = f * b.point[0];
	c.point[1] = f * b.point[1];
	c.point[2] = f * b.point[2];

	return c;
}


/****************************************************************************/
/** vector division
*****************************************************************************/
vector_t operator/(vector_t a, vector_t b)
{
	vector_t c;

	c.point[0] = a.point[0] / b.point[0];
	c.point[1] = a.point[1] / b.point[1];
	c.point[2] = a.point[2] / b.point[2];

	return c;
}


/****************************************************************************/
/** vector addition
*****************************************************************************/
vector_t operator+(vector_t a, vector_t b)
{
	vector_t c;

	c.point[0] = a.point[0] + b.point[0];
	c.point[1] = a.point[1] + b.point[1];
	c.point[2] = a.point[2] + b.point[2];

	return c;
}


/****************************************************************************/
/** CMD2Model constructor
*****************************************************************************/
CMD2Model::CMD2Model()
{
     numVertices = 0;    // vertices
     numTriangles = 0;   // triangles
     numFrames = 0;      // frames
     numST = 0;          // texture coordinates
     frameSize = 0;      // needed?
     currentFrame = 0;   // current keyframe 
     nextFrame = 1;      // next keyframe
     interpol = 0.0;     // interpolation percent
     triIndex = NULL;    // triangle indices
     st = NULL;          // texture coordinate indices
     vertexList = NULL;  // vertices
     modelTex = new CTexture;    // skin/texture
	modelState = MODEL_IDLE;
}    


/****************************************************************************/
/** CMD2Model destructor
*****************************************************************************/
CMD2Model::~CMD2Model()
{
	Unload();
}


/****************************************************************************/
//  CMD2Model::SetupSkin()
/** sets up the model skin/texture for OpenGL
*****************************************************************************/
void CMD2Model::SetupSkin(CTexture *thisTexture)
{
     // set the proper parameters for an MD2 texture
     glGenTextures(1, &thisTexture->texID);
     glBindTexture(GL_TEXTURE_2D, thisTexture->texID);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
     
	 int mode = (thisTexture->bitDepth == 24) ? GL_RGB:GL_RGBA;
	 gluBuild2DMipmaps(GL_TEXTURE_2D, mode, thisTexture[0].width, thisTexture[0].height,
				       mode, GL_UNSIGNED_BYTE, thisTexture[0].data);
}


/****************************************************************************/
//  CMD2Model::Load()
/** loads model and skin
*****************************************************************************/
int CMD2Model::Load(char *modelFile, char *skinFile)
{
     FILE *filePtr;                          // file pointer
     int fileLen;                            // length of model file
     char *buffer;                           // file buffer
     
     modelHeader_t *modelHeader;             // model header
     
     stIndex_t *stPtr;                       // texture data
     frame_t *frame;                         // frame data
     vector_t *vertexListPtr;                // index variable
     mesh_t *bufIndexPtr;                    // index variables
     int i, j;                               // index variables
     
     // open the model file
     filePtr = fopen(modelFile, "rb");
     if (filePtr == NULL)
          return false;
     
     // find length of file
     fseek(filePtr, 0, SEEK_END);
     fileLen = ftell(filePtr);
     fseek(filePtr, 0, SEEK_SET);
     
     // read entire file into buffer
     buffer = new char [fileLen+1];
     fread(buffer, sizeof(char), fileLen, filePtr);
     
     // extract model file header from buffer
     modelHeader = (modelHeader_t*)buffer;
     
     vertexList = new vector_t [modelHeader->numXYZ * modelHeader->numFrames];
     
     numVertices = modelHeader->numXYZ;
     numFrames = modelHeader->numFrames;
     frameSize = modelHeader->framesize;
     
     for (j = 0; j < numFrames; j++)
     {
          frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];
          
          vertexListPtr = (vector_t*)&vertexList[numVertices * j];
          for (i = 0; i < numVertices; i++)
          {
               vertexListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
               vertexListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
               vertexListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
          }
     }
     
     modelTex->LoadTexture(skinFile);// = LoadTexture(skinFile);
     if (modelTex != NULL)
          SetupSkin(modelTex);
     else
          return false;
     
     numST = modelHeader->numST;
     st = new texCoord_t [numST];
     
     stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];
     for (i = 0; i < numST; i++)
     {
          st[i].s = (float)stPtr[i].s / (float)modelTex->width;
          st[i].t = (float)stPtr[i].t / (float)modelTex->height;
     }
     
     numTriangles = modelHeader->numTris;
     triIndex = new mesh_t [numTriangles];
     
     // point to triangle indexes in buffer
     bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];
     
     // create a mesh (triangle) list
     for (j = 0; j < numFrames; j++)         
     {
          // for all triangles in each frame
          for(i = 0; i < numTriangles; i++)
          {
               triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
               triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
               triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
               triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
               triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
               triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
          }
     }
     
     // close file and free memory
     fclose(filePtr);
	delete buffer;
     
     currentFrame = 0;
     nextFrame = 1;
     interpol = 0.0;
     
     return true;
}


/****************************************************************************/
//  CMD2Model::LoadModel()
/** loads model from file
*****************************************************************************/
int CMD2Model::LoadModel(char *modelFile)
{
     FILE *filePtr;                          // file pointer
     int fileLen;                            // length of model file
     char *buffer;                           // file buffer
     
     modelHeader_t *modelHeader;             // model header
     
     stIndex_t *stPtr;                       // texture data
     frame_t *frame;                              // frame data
     vector_t *vertexListPtr;                // index variable
     mesh_t *triIndex, *bufIndexPtr;         // index variables
     int i, j;                               // index variables
     
     // open the model file
     filePtr = fopen(modelFile, "rb");
     if (filePtr == NULL)
          return false;
     
     // find length of file
     fseek(filePtr, 0, SEEK_END);
     fileLen = ftell(filePtr);
     fseek(filePtr, 0, SEEK_SET);
     
     // read entire file into buffer
     buffer = new char [fileLen+1];
     fread(buffer, sizeof(char), fileLen, filePtr);
     
     // extract model file header from buffer
     modelHeader = (modelHeader_t*)buffer;
     
     // allocate vertex list
     vertexList = new vector_t [modelHeader->numXYZ * modelHeader->numFrames];
     
     numVertices = modelHeader->numXYZ;
     numFrames = modelHeader->numFrames;
     frameSize = modelHeader->framesize;
     
     for (j = 0; j < numFrames; j++)
     {
          frame = (frame_t*)&buffer[modelHeader->offsetFrames + frameSize * j];
          
          vertexListPtr = (vector_t*)&vertexList[numVertices * j];
          for (i = 0; i < numVertices; i++)
          {
               vertexListPtr[i].point[0] = frame->scale[0] * frame->fp[i].v[0] + frame->translate[0];
               vertexListPtr[i].point[1] = frame->scale[1] * frame->fp[i].v[1] + frame->translate[1];
               vertexListPtr[i].point[2] = frame->scale[2] * frame->fp[i].v[2] + frame->translate[2];
          }
     }
     
     numST = modelHeader->numST;
     
     st = new texCoord_t [numST];
     
     stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];
     for (i = 0; i < numST; i++)
     {
          st[i].s = 0.0;
          st[i].t = 0.0;
     }
     
     numTriangles = modelHeader->numTris;
     triIndex = new mesh_t [numTriangles];
     
     // point to triangle indexes in buffer
     bufIndexPtr = (mesh_t*)&buffer[modelHeader->offsetTris];
     
     // create a mesh (triangle) list
     for (j = 0; j < numFrames; j++)         
     {
          // for all triangles in each frame
          for(i = 0; i < numTriangles; i++)
          {
               triIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
               triIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
               triIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
               triIndex[i].stIndex[0] = bufIndexPtr[i].stIndex[0];
               triIndex[i].stIndex[1] = bufIndexPtr[i].stIndex[1];
               triIndex[i].stIndex[2] = bufIndexPtr[i].stIndex[2];
          }
     }
     
     // close file and free memory
     fclose(filePtr);
	delete buffer;
     
     modelTex = NULL;
     currentFrame = 0;
     nextFrame = 1;
     interpol = 0.0;
     
     return 0;
}


/****************************************************************************/
//  CMD2Model::LoadSkin()
/** loads a skin for the model
*****************************************************************************/
int CMD2Model::LoadSkin(char *skinFile)
{
     int i;
     
     modelTex->LoadTexture(skinFile);
     
     if (modelTex != NULL)
          SetupSkin(modelTex);
     else
          return -1;
     
     for (i = 0; i < numST; i++)
     {
          st[i].s /= (float)modelTex->width;
          st[i].t /= (float)modelTex->height;
     }
     
     return 0;
}


/****************************************************************************/
//  CMD2Model::SetTexture()
/** sets a new texture object 
*****************************************************************************/
int CMD2Model::SetTexture(CTexture *texture)
{
     int i;
     
     if (texture != NULL)
	{
		free(modelTex);
          modelTex = texture;
	}
     else
          return -1;
     
     SetupSkin(modelTex);
     
     for (i = 0; i < numST; i++)
     {
          st[i].s /= (float)modelTex->width;
          st[i].t /= (float)modelTex->height;
     }
     
     return 0;
}


/****************************************************************************/
//  CMD2Model::Animate()
/** animates the model between the keyframes startFrame and endFrame
*****************************************************************************/
int CMD2Model::AnimateModel(int startFrame, int endFrame, float percent)
{
     vector_t *vList;              // current frame vertices
     vector_t *nextVList;          // next frame vertices
     int i;                                  // index counter
     float x1, y1, z1;                  // current frame point values
     float x2, y2, z2;                  // next frame point values
     
     vector_t vertex[3]; 
     
     if ((startFrame > currentFrame))
          currentFrame = startFrame;
     
     if ((startFrame < 0) || (endFrame < 0))
          return -1;
     
     if ((startFrame >= numFrames) || (endFrame >= numFrames))
          return -1;
     
     if (interpol >= 1.0)
     {
          interpol = 0.0f;
          currentFrame++;
          if (currentFrame >= endFrame)
               currentFrame = startFrame;
          
          nextFrame = currentFrame + 1;
          
          if (nextFrame >= endFrame)
               nextFrame = startFrame;
          
     }
     
     vList = &vertexList[numVertices*currentFrame];
     nextVList = &vertexList[numVertices*nextFrame];
     
     glColor4f(1.0, 1.0, 1.0, 1.0);
     glBindTexture(GL_TEXTURE_2D, modelTex->texID);
     glBegin(GL_TRIANGLES);
     for (i = 0; i < numTriangles; i++)
     {
          // get first points of each frame
          x1 = vList[triIndex[i].meshIndex[0]].point[0];
          y1 = vList[triIndex[i].meshIndex[0]].point[1];
          z1 = vList[triIndex[i].meshIndex[0]].point[2];
          x2 = nextVList[triIndex[i].meshIndex[0]].point[0];
          y2 = nextVList[triIndex[i].meshIndex[0]].point[1];
          z2 = nextVList[triIndex[i].meshIndex[0]].point[2];
          
          // store first interpolated vertex of triangle
          vertex[0].point[0] = x1 + interpol * (x2 - x1);
          vertex[0].point[1] = y1 + interpol * (y2 - y1);
          vertex[0].point[2] = z1 + interpol * (z2 - z1);
          
          // get second points of each frame
          x1 = vList[triIndex[i].meshIndex[2]].point[0];
          y1 = vList[triIndex[i].meshIndex[2]].point[1];
          z1 = vList[triIndex[i].meshIndex[2]].point[2];
          x2 = nextVList[triIndex[i].meshIndex[2]].point[0];
          y2 = nextVList[triIndex[i].meshIndex[2]].point[1];
          z2 = nextVList[triIndex[i].meshIndex[2]].point[2];
          
          // store second interpolated vertex of triangle
          vertex[2].point[0] = x1 + interpol * (x2 - x1);
          vertex[2].point[1] = y1 + interpol * (y2 - y1);
          vertex[2].point[2] = z1 + interpol * (z2 - z1);   
          
          // get third points of each frame
          x1 = vList[triIndex[i].meshIndex[1]].point[0];
          y1 = vList[triIndex[i].meshIndex[1]].point[1];
          z1 = vList[triIndex[i].meshIndex[1]].point[2];
          x2 = nextVList[triIndex[i].meshIndex[1]].point[0];
          y2 = nextVList[triIndex[i].meshIndex[1]].point[1];
          z2 = nextVList[triIndex[i].meshIndex[1]].point[2];
          
          // store third interpolated vertex of triangle
          vertex[1].point[0] = x1 + interpol * (x2 - x1);
          vertex[1].point[1] = y1 + interpol * (y2 - y1);
          vertex[1].point[2] = z1 + interpol * (z2 - z1);
          
          // calculate the normal of the triangle
          CalculateNormal(vertex[0].point, vertex[2].point, vertex[1].point);
          
          // render properly textured triangle
          glTexCoord2f(st[triIndex[i].stIndex[0]].s,
               st[triIndex[i].stIndex[0]].t);
          glVertex3fv(vertex[0].point);
          
          glTexCoord2f(st[triIndex[i].stIndex[2]].s ,
               st[triIndex[i].stIndex[2]].t);
          glVertex3fv(vertex[2].point);
          
          glTexCoord2f(st[triIndex[i].stIndex[1]].s,
               st[triIndex[i].stIndex[1]].t);
          glVertex3fv(vertex[1].point);
     }
     glEnd();
     
     interpol += percent;  // increase percentage of interpolation between frames
     
     return 0;
}


/****************************************************************************/
//  RenderFrame()
/** renders a single key frame
*****************************************************************************/
int CMD2Model::RenderFrame(int keyFrame)
{
     vector_t *vList;
     int i;
     
     // create a pointer to the frame we want to show
     vList = &vertexList[numVertices * keyFrame];
     
	if (modelTex != NULL)
		// set the texture
		glBindTexture(GL_TEXTURE_2D, modelTex->texID);
     
     // display the textured model with proper lighting normals
     glBegin(GL_TRIANGLES);
     for(i = 0; i < numTriangles; i++)
     {
          CalculateNormal(vList[triIndex[i].meshIndex[0]].point,
               vList[triIndex[i].meshIndex[2]].point,
               vList[triIndex[i].meshIndex[1]].point);

		if (modelTex != NULL)
			glTexCoord2f(st[triIndex[i].stIndex[0]].s,
				st[triIndex[i].stIndex[0]].t);

          glVertex3fv(vList[triIndex[i].meshIndex[0]].point);
          
		if (modelTex != NULL)
			glTexCoord2f(st[triIndex[i].stIndex[2]].s ,
				st[triIndex[i].stIndex[2]].t);

          glVertex3fv(vList[triIndex[i].meshIndex[2]].point);
          
		if (modelTex != NULL)
			glTexCoord2f(st[triIndex[i].stIndex[1]].s,
				st[triIndex[i].stIndex[1]].t);

          glVertex3fv(vList[triIndex[i].meshIndex[1]].point);
     }
     glEnd();
     
     return 0;
}


/****************************************************************************/
//  Unload()
/** unloads model data from memory
*****************************************************************************/
void CMD2Model::Unload()
{
     if (triIndex != NULL)
          delete [] triIndex;//free(triIndex);
     if (vertexList != NULL)
          delete [] vertexList;//free(vertexList);
     if (st != NULL)
          delete [] st; //free(st);

	if (modelTex != NULL)
		delete modelTex;
}


/****************************************************************************/
//  SetState()
/** set the model state
*****************************************************************************/
void CMD2Model::SetState(modelState_t state)
{
	modelState = state;
}


/****************************************************************************/
//  GetState()
/** retrieve the model state
*****************************************************************************/
modelState_t CMD2Model::GetState()
{
	return modelState;
}
