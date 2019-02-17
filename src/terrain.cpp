#include "terrain.h"

/***************************************************************************/
/** \file  terrain.cpp
	\brief The CTerrain class implementation                               */


/***************************************************************************/
/** CTerrain constructor
****************************************************************************/
CTerrain::CTerrain()
{
	width = 256;
	scanDepth = 80.0;
	terrainMul = 50.0;
	textureMul = 0.25;
	widthScale = 5.0;
	heightMul = 175.0;
	fogColor[0] = 0.75f;
	fogColor[1] = 0.9f;
	fogColor[2] = 1.0f;
	fogColor[3] = 1.0f;

	// CObject attributes
	position = CVector(0,0,0);
	velocity = CVector(0,0,0);
	acceleration = CVector(0,0,0);
	size = width*terrainMul*2;

	BuildTerrain(width, 0.5f);
}


/***************************************************************************/
/** CTerrain constructor
	\param w Terrain width
****************************************************************************/
CTerrain::CTerrain(int w, float rFactor)
{
	width = w;
	scanDepth = 80.0;
	terrainMul = 50.0;
	textureMul = 0.25;
	widthScale = 5.0;
	heightMul = 175.0;
	fogColor[0] = 0.75f;
	fogColor[1] = 0.9f;
	fogColor[2] = 1.0f;
	fogColor[3] = 1.0f;

	// CObject attributes
	position = CVector(0,0,0);
	velocity = CVector(0,0,0);
	acceleration = CVector(0,0,0);
	size = width*terrainMul*2;
msg=new CFont("Courier New",40);
	BuildTerrain(width, rFactor);

}


/***************************************************************************/
/** Build the terrain for OpenGL
****************************************************************************/
void CTerrain::BuildTerrain(int w, float rFactor)
{
	width = w;
	heightMap = new float[width*width];
	MakeTerrainPlasma(heightMap, width, rFactor);
	
	// load texture
	terrainTex[0].LoadTexture("textures/ground.tga");
	glGenTextures(1, &terrainTex[0].texID);
	glBindTexture(GL_TEXTURE_2D, terrainTex[0].texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//or GL_CLAMP
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//or GL_CLAMP

	int mode = (terrainTex[0].bitDepth == 24) ? GL_RGB:GL_RGBA;
	gluBuild2DMipmaps(GL_TEXTURE_2D, mode, terrainTex[0].width, terrainTex[0].height,
				      mode, GL_UNSIGNED_BYTE, terrainTex[0].data);
}


/***************************************************************************/
/** The terrain is a static objetc
****************************************************************************/
void CTerrain::OnCollision(CObject *collisionObject)
{}


/***************************************************************************/
/** Renders the terrain
****************************************************************************/
void CTerrain::OnDraw(CCamera *camera)
{
	int z, x;
	msg->SetPos3D(0.5,0,0);
	msg->SetRGB(1,0,0);
	msg->Print("%f",camera->position.y);
	glEnable(GL_DEPTH_TEST);

	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_START, scanDepth * 0.1f);
	glFogf(GL_FOG_END, scanDepth * 2);
	glHint(GL_FOG_HINT, GL_FASTEST);
//	glEnable(GL_FOG);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_ONE_MINUS_SRC_ALPHA);	//GL_SRC_ALPHA
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.0);
	glDisable(GL_ALPHA_TEST);
	// push/pop objects that move with the camera (e.g. a sun, the sky)
	//glTranslatef(camera->x, camera->y, camera->z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, terrainTex[0].texID);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0, 1.0, 1.0);
	//for ( z = 0; z < width-1; z++)
	// use below line for repeating terrain
//	for (z = (int)(camera->position.z / terrainMul - scanDepth); (int)(z < camera->position.z / terrainMul + scanDepth); z++)
	for (z = (int)(camera->position.z / terrainMul - scanDepth), z=z<0?0:z; (z < camera->position.z / terrainMul + scanDepth) && z < width-1; z++)
	{
		glBegin(GL_TRIANGLE_STRIP);
	//	glBegin(GL_QUAD_STRIP);
	//	for (x = 0; x < width-1; x++)
//		for (x = (int)(camera->position.x / terrainMul - scanDepth); (int)(x < camera->position.x / terrainMul + scanDepth); x++)
		for (x = (int)(camera->position.x / terrainMul - scanDepth), x=x<0?0:x; (x < camera->position.x / terrainMul + scanDepth) && x < width-1; x++)
		//for(x = (int)(camera->position.x / terrainMul-scanDepth); x<(int)(camera->position.x / terrainMul+scanDepth); x++)
		{
			/*** UNCOMMENT FOR QUADSTRIP
			
			glColor3f(heightMap[x+(z+1)*width], heightMap[x+(z+1)*width], heightMap[x+(z+1)*width]);
			glVertex3f((float)x*terrainMul, (float)heightMap[x + (z+1)*width]*heightMul, (float)(z+1)*terrainMul);

			glColor3f(heightMap[x+z*width], heightMap[x+z*width], heightMap[x+z*width]);
			glVertex3f((float)x*terrainMul, (float)heightMap[x + z*width]*heightMul, (float)z*terrainMul);
*/
		//	glColor3f(heightMap[x+z*width], heightMap[x+z*width], heightMap[x+z*width]);
			glTexCoord2f(textureMul * x, textureMul * z);
			glVertex3f((float)x*terrainMul, (float)heightMap[x + z*width]*heightMul, (float)z*terrainMul);

		//	glColor3f(heightMap[x+1+z*width], heightMap[x+1+z*width], heightMap[x+1+z*width]);
			glTexCoord2f(textureMul * (x+1), textureMul * z);
			glVertex3f((float)(x+1)*terrainMul, (float)heightMap[x+1 + z*width]*heightMul, (float)z*terrainMul);

		//	glColor3f(heightMap[x+(z+1)*width], heightMap[x+(z+1)*width], heightMap[x+(z+1)*width]);
			glTexCoord2f(textureMul * x, textureMul * (z+1));
			glVertex3f((float)x*terrainMul, (float)heightMap[x + (z+1)*width]*heightMul, (float)(z+1)*terrainMul);

		//	glColor3f(heightMap[x+1+(z+1)*width], heightMap[x+1+(z+1)*width], heightMap[x+1+(z+1)*width]);
			glTexCoord2f(textureMul * (x+1), textureMul * (z+1));
			glVertex3f((float)(x+1)*terrainMul, (float)heightMap[x+1 + (z+1)*width]*heightMul, (float)(z+1)*terrainMul);
		}
		glEnd();
	}
	
}


/***************************************************************************/
//  RangedRandom()
/** \return a random number between v1 and v2
****************************************************************************/
float CTerrain::RangedRandom(float v1,float v2)
{
	return v1 + (v2-v1)*((float)rand())/((float)RAND_MAX);
}


/***************************************************************************/
//  NormalizeTerrain()
/** Given a height field, normalize it so that the minimum altitude
    is 0.0 and the maximum altitude is 1.0
****************************************************************************/
void CTerrain::NormalizeTerrain(float field[],int size)
{
	float maxVal,minVal,dh;
	int i;

	/*
	Find the maximum and minimum values in the height field
	*/ 
	maxVal = field[0];
	minVal = field[0];

	for (i=1;i<size*size;i++)
	{
		if (field[i] > maxVal) 
		{
			maxVal = field[i];
		}
		else if (field[i] < minVal) 
		{
			minVal = field[i];
		}
	}

	/*
	Find the altitude range (dh)
	*/
	if (maxVal <= minVal) return;
	dh = maxVal-minVal;

	/*
	Scale all the values so they are in the range 0-1
	*/
	for (i=0;i<size*size;i++)
	{
		field[i] = (field[i]-minVal)/dh;
	}

}


/***************************************************************************/
//  FilterHeightBand()
/** Erosion filter -
    FilterHeightBand applies a FIR filter across a row or column of the 
	height field
****************************************************************************/
void CTerrain::FilterHeightBand(float *band,int stride,int count,float filter)
{
	int i,j=stride;
	float v = band[0];
	for (i=0;i<count-1;i++)
	{
		band[j] = filter*v + (1-filter)*band[j];
		v = band[j];
		j+=stride;
	}
}


/***************************************************************************/
//  FilterHeightField()
/** Erosion filter -
    Erodes a terrain in all 4 directions
****************************************************************************/
void CTerrain::FilterHeightField(float field[],int size,float filter)
{
	int i;

	// Erode rows left to right
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[size*i],1,size,filter);
	}
	
	// Erode rows right to left
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[size*i+size-1],-1,size,filter);
	}

	// Erode columns top to bottom
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[i],size,size,filter);
	}

	// Erode columns bottom to top
	for (i=0;i<size;i++)
	{
		FilterHeightBand(&field[size*(size-1)+i],-size,size,filter);
	}
}


/***************************************************************************/
//  MakeTerrainPlasma()
/** Genereate terrain using diamond-square (plasma) algorithm
****************************************************************************/
void CTerrain::MakeTerrainPlasma(float field[],int size,float rough)
{
	int i,j,ni,nj,mi,mj,pmi,pmj,rectSize = size;
	float dh = (float)rectSize/2,r = (float)pow(2.0f,(int)-1*rough);

//	Since the terrain wraps, all 4 "corners" are represented by the value at 0,0,
//		so seeding the heightfield is very straightforward
//	Note that it doesn't matter what we use for a seed value, since we're going to
//		renormalize the terrain after we're done
	field[0] = 0;


	while(rectSize > 0)
	{
		
		/*
		Diamond step -

		Find the values at the center of the retangles by averaging the values at 
		the corners and adding a random offset:


		a.....b
		.     .  
		.  e  .
		.     .
		c.....d   

		e  = (a+b+c+d)/4 + random

		In the code below:
		a = (i,j)
		b = (ni,j)
		c = (i,nj)
		d = (ni,nj)
		e = (mi,mj)

		*/
		       
		for (i=0;i<size;i+=rectSize)
		for (j=0;j<size;j+=rectSize)
		{
			
			ni = (i+rectSize)%size;
			nj = (j+rectSize)%size;

			mi = (i+rectSize/2);
			mj = (j+rectSize/2);

			field[mi+mj*size] = (field[i+j*size] + field[ni+j*size] + field[i+nj*size] + field[ni+nj*size])/4 + RangedRandom(-dh/2,dh/2);
		}

		/*
		Square step -

		Find the values on the left and top sides of each rectangle
		The right and bottom sides are the left and top sides of the neighboring rectangles,
		  so we don't need to calculate them

		The height field wraps, so we're never left hanging.  The right side of the last
			rectangle in a row is the left side of the first rectangle in the row.  The bottom
			side of the last rectangle in a column is the top side of the first rectangle in
			the column

              .......
		      .     .
		      .     .
		      .  d  .
		      .     .
		      .     .
		......a..g..b
		.     .     .
		.     .     .
		.  e  h  f  .
		.     .     .
		.     .     .
		......c......

		g = (d+f+a+b)/4 + random
		h = (a+c+e+f)/4 + random
		
		In the code below:
			a = (i,j) 
			b = (ni,j) 
			c = (i,nj) 
			d = (mi,pmj) 
			e = (pmi,mj) 
			f = (mi,mj) 
			g = (mi,j)
			h = (i,mj)

		*/
		for (i=0;i<size;i+=rectSize)
		for (j=0;j<size;j+=rectSize)
		{

			ni = (i+rectSize)%size;
			nj = (j+rectSize)%size;

			mi = (i+rectSize/2);
			mj = (j+rectSize/2);

			pmi = (i-rectSize/2+size)%size;
			pmj = (j-rectSize/2+size)%size;

			// Calculate the square value for the top side of the rectangle
			field[mi+j*size] = (field[i+j*size] + field[ni+j*size] + field[mi+pmj*size] + field[mi+mj*size])/4 + RangedRandom(-dh/2,dh/2);

			// Calculate the square value for the left side of the rectangle
			field[i+mj*size] = (field[i+j*size] + field[i+nj*size] + field[pmi+mj*size] + field[mi+mj*size])/4 + RangedRandom(-dh/2,dh/2);

		}

		// Setup values for next iteration
		// At this point, the height field has valid values at each of the coordinates that fall on a rectSize/2 boundary

		rectSize /= 2;
		dh *= r;
	}
	
	// Normalize terrain so minimum value is 0 and maximum value is 1
	NormalizeTerrain(field,size);
}
