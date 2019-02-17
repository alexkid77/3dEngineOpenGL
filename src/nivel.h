#ifndef __NIVEL_H
#define __NIVEL_H
#include <windows.h>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "camera.h"
#include "object.h"
#include "texture.h"
#include "vector.h"
#include "font.h"

#include "Q3loader.h"
#include "frustum.h"


/////añadido operadores + y * en TVertex para operaciones de tesselacion
class CNivel :public CObject
{
private:
	TMapQ3 mapa;
	std::vector<CTexture> vlightmaps;
	std::vector<CTexture> vtexturas;
	void ConversionEjes();///conversion de ejes los mapas de quake utiliza Y como Z
	void DibujaTriangulo(int cara);//dibuja triangulos del nivel sin utilizar vertex array
	void DibujaTriangulo2(int ncara);//dibuja triangulos del nivel utilizando vertex array
	void DibujaTrianguloMesh(int ncara);//dibuja triangulos de los Mesh utilizando vertex array
	//falta dibujar curvas de bezier

	///funciones BSP/////
	int EncuentraHoja(const CVector &camarapos);//salida indice hoja entrada posiciones de la camara
	bool ClusterVisible(int actual,int hojacluster);
	void GeneraLightmaps();
	void GeneraTexturas();

	//funciones y variables colision
	int tipo_trazado;
	float radioEsfera;
	void ComprobarNodo(int nodo_indice,float fraccion_ini,float fraccion_final,CVector Pinicial,CVector Pfinal);
	void ComprobarBrush(TBrush *brush,CVector vInicio,CVector vFinal);
	CVector cajaMin,cajaMax;

protected:
void OnAnimate(scalar_t deltaTime) {}

	void OnDraw(CCamera *camera);
	void OnCollision(CObject *collisionObject);
public:
	//punteros a funciones para multitextura
	PFNGLACTIVETEXTUREARBPROC		glActiveTextureARB; 
	PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;
	///////////////////

	int triangulos;
	CFrustum elfrustum;//clase para el frustum culling
	CNivel(void);
	CNivel(char *nombre);

	//funciones para las colisiones
	CVector Trazar(CVector inicio,CVector fin);
	CVector TrazaRayo(CVector inicio,CVector fin);
	CVector TrazaEsfera(CVector inicio,CVector fin,float radio);
	CVector TrazaCaja(CVector inicio,CVector fin,CVector min,CVector max);
	float outputFraction;
	bool colision;
	///////////////////////////////
	~CNivel(void);
};
#endif
