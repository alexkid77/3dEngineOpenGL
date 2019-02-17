#include "nivel.h"
#define EPSILON 0.03125f
#define TT_RAYO 0
#define TT_ESFERA 1
#define TT_CAJA 2
CNivel::CNivel(void)
{
	if(readMap("models\\T8dm6.bsp",mapa)==true){

		printf("mapa cargado\n");
		ConversionEjes();
		GeneraLightmaps();
	}
	else{
		printf("error cargar mapa\n");
	}
}
CNivel::CNivel(char *nombre)
{


	if(readMap(nombre,mapa)==true){
		printf("mapa cargado\n");
		ConversionEjes();
		GeneraLightmaps();
		this->GeneraTexturas();
		//asignar direccion de mem donde se encuentra la funcion glClientActiveTextureARB
		glClientActiveTextureARB=(PFNGLCLIENTACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress("glClientActiveTextureARB");
//asignar direccion de mem a glActiveTextureARB
		glActiveTextureARB=(PFNGLACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress("glActiveTextureARB");
	

	}
	
	else{
		printf("error cargar mapa\n");
	}
}

CNivel::~CNivel(void)
{
	freeMap(mapa);
}

void CNivel::ConversionEjes(void)
{
	float x;
	int c;
	//conversion vertices
	for(unsigned int i=0;i<mapa.mVertices.size();i++){
		//pasar la coordenada Y a Z y viceversa
		x=mapa.mVertices[i].mPosition[1];
		mapa.mVertices[i].mPosition[1]=mapa.mVertices[i].mPosition[2];
		mapa.mVertices[i].mPosition[2]=-x;

		x=mapa.mVertices[i].mNormal[1];
		mapa.mVertices[i].mNormal[1]=mapa.mVertices[i].mNormal[2];
		mapa.mVertices[i].mNormal[2]=-x;
		
		x=mapa.mVertices[i].mTexCoord[1][0];
		mapa.mVertices[i].mTexCoord[1][0]=mapa.mVertices[i].mTexCoord[1][1];
		mapa.mVertices[i].mTexCoord[1][1]=x;

	}
	//conversion planos
	for(unsigned int i=0;i<mapa.mPlanes.size();i++){
		x=mapa.mPlanes[i].mNormal[1];
		mapa.mPlanes[i].mNormal[1]=mapa.mPlanes[i].mNormal[2];
		mapa.mPlanes[i].mNormal[2]=-x;
	}

	for(unsigned int i=0;i<mapa.mFaces.size();i++){
		x=mapa.mFaces[i].mNormal[1];
		mapa.mFaces[i].mNormal[1]=mapa.mFaces[i].mNormal[2];
		mapa.mFaces[i].mNormal[2]=-x;
	}

	//cajas para el frustum culling
	for(unsigned int i=0;i<mapa.mLeaves.size();i++)
	{
	
		c=mapa.mLeaves[i].mMins[1];
		mapa.mLeaves[i].mMins[1]=mapa.mLeaves[i].mMins[2];
		mapa.mLeaves[i].mMins[2]=-c;
		c=mapa.mLeaves[i].mMaxs[1];
		mapa.mLeaves[i].mMaxs[1]=mapa.mLeaves[i].mMaxs[2];
		mapa.mLeaves[i].mMaxs[2]=-c;
	}
	

	
}

void CNivel::OnCollision(CObject *collisionObject)
{}

void CNivel::OnDraw(CCamera *camera){
	int indiceHoja;
	int cluster;
	int n_hojas=mapa.mLeaves.size();
	
	//problemas en fullscreen con zbuffer solucion aqui http://www.gamedev.net/community/forums/topic.asp?topic_id=457423 
 glDisable(GL_COLOR_MATERIAL);
	glEnableClientState(GL_VERTEX_ARRAY);//activar todos los buffers
	glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   //glEnable(GL_TEXTURE_2D);
	indiceHoja=EncuentraHoja(camera->position);//situa el indice en la hoja donde se encuentra la camara
	cluster=mapa.mLeaves[indiceHoja].mCluster;

	elfrustum.CalculateFrustum();//esta clase se a tomado prestada
	triangulos=0;
	while(n_hojas--)//hasta que no haya hojas por procesar
	{
		TLeaf *hoja=& mapa.mLeaves[n_hojas];
		if(!ClusterVisible(cluster,hoja->mCluster ))//recorre toda las hojas y mira si se pueden ver desde la hoja donde se encuentra la camara
			continue;
		///mira si la hoja esta dentro del frustrum con la caja definidad en cada hoja
		if(!elfrustum.BoxInFrustum((float)hoja->mMins[0],(float)hoja->mMins[1],(float)hoja->mMins[2],(float)hoja->mMaxs[0],(float)hoja->mMaxs[1],(float)hoja->mMaxs[2]))
			continue;
		int n_caras=hoja->mNbLeafFaces;//numero de caras de la hoja

		while(n_caras--){//hasta que no haya caras por procesar
			int indice_cara=mapa.mLeafFaces[hoja->mLeafFace+n_caras].mFaceIndex;
			if(mapa.mFaces[indice_cara].mType==1)
			{
				DibujaTriangulo2(indice_cara);
			}
			if(mapa.mFaces[indice_cara].mType==3){
				DibujaTrianguloMesh(indice_cara);
			}
			triangulos++;
		}
		
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	

}
///////////version antigua para dibujar triangulos////////
void CNivel::DibujaTriangulo(int cara){

if(mapa.mFaces[cara].mLightmapIndex>=0)
	{
	 glBindTexture(GL_TEXTURE_2D, vlightmaps[mapa.mFaces[cara].mLightmapIndex].texID);
	 glEnable(GL_TEXTURE_2D);
	}
	glBegin(GL_TRIANGLE_FAN);//usado por los mapas de quake 3 para renderizar las caras del nivel
	glNormal3f(mapa.mFaces[cara].mNormal[0],mapa.mFaces[cara].mNormal[1],mapa.mFaces[cara].mNormal[2]); //normal de cada cara

	for(int j=mapa.mFaces[cara].mVertex;j<(mapa.mFaces[cara].mVertex+mapa.mFaces[cara].mNbVertices);j++){
	glTexCoord2f(mapa.mVertices[j].mTexCoord[1][0],mapa.mVertices[j].mTexCoord[1][1]);
		glColor3ubv(mapa.mVertices[j].mColor);
		glNormal3fv(mapa.mVertices[j].mNormal);
		glVertex3fv(mapa.mVertices[j].mPosition);	 //vertice (cambiar por array de vertices)
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
//////////nueva version para dibujar triangulos por vertex buffer/////
void CNivel::DibujaTriangulo2(int ncara){
	if(mapa.mFaces[ncara].mTextureIndex>=0)
	{

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glTexCoordPointer(2, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mTexCoord[0]));//coordenadas lightmaps
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, vtexturas[mapa.mFaces[ncara].mTextureIndex].texID);

		

	}
	if(mapa.mFaces[ncara].mLightmapIndex>=0)
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glTexCoordPointer(2, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mTexCoord[1]));
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, vlightmaps[mapa.mFaces[ncara].mLightmapIndex].texID);
		
		
		
	}

	/*if(mapa.mFaces[ncara].mLightmapIndex>=0)
	{
	 glBindTexture(GL_TEXTURE_2D, vlightmaps[mapa.mFaces[ncara].mLightmapIndex].texID);
	 glEnable(GL_TEXTURE_2D);
	}*/
	//falta meter las coordenadas de texturas (multitextura)
	
	glVertexPointer(3, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mPosition));//puntero al conjuto de vertices
	glNormalPointer(GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mNormal));//puntero a las normales por vertice
	//glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(TVertex), &(mapa.mVertices[0].mColor));//puntero a los colores de cada vertice
	
	glDrawArrays(GL_TRIANGLE_FAN, mapa.mFaces[ncara].mVertex,mapa.mFaces[ncara].mNbVertices);//dibuja la cara
glDisable(GL_TEXTURE_2D);
}
void CNivel::DibujaTrianguloMesh(int cara){
	//esta mierda de funcion me ha costado un huevo... POR FIN!!!
	
	if(mapa.mFaces[cara].mTextureIndex>=0)
	{

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glTexCoordPointer(2, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mTexCoord[0]));//coordenadas lightmaps
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glClientActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, vtexturas[mapa.mFaces[cara].mTextureIndex].texID);

		

	}
	if(mapa.mFaces[cara].mLightmapIndex>=0)
	{
		glActiveTextureARB(GL_TEXTURE1_ARB);
		glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glTexCoordPointer(2, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mTexCoord[1]));
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		//glClientActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, vlightmaps[mapa.mFaces[cara].mLightmapIndex].texID);
		
		
		
	}

	glVertexPointer(3, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[mapa.mFaces[cara].mVertex].mPosition));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(TVertex), &(mapa.mVertices[0].mColor));
	glTexCoordPointer(2, GL_FLOAT, sizeof(TVertex), &(mapa.mVertices[0].mTexCoord[1]));
	glDrawElements(	GL_TRIANGLES, mapa.mFaces[cara].mNbMeshVertices,GL_UNSIGNED_INT,&mapa.mMeshVertices[mapa.mFaces[cara].mMeshVertex]);
glDisable(GL_TEXTURE_2D);
}

///encuentra la hoja donde se encuentra la camara///
int CNivel::EncuentraHoja(const CVector &camarapos)
{

	//CVector temp;
	double distancia;
	int indice=0;
	while(indice>=0){
		const TNode& nodo=mapa.mNodes[indice];
		const TPlane & plano=mapa.mPlanes[nodo.mPlane];
		//	temp.x=plano.mNormal[0];
		//	temp.y=plano.mNormal[1];
		//	temp.z=plano.mNormal[2];
		//eliminado por que fallaba muxo la precision y habia errores de visualizacion
		//distancia=temp.DotProduct(camarapos)-plano.mDistance;//posible fallo de precision por usar float en vez de double
		distancia=plano.mNormal[0]*camarapos.x+plano.mNormal[1]*camarapos.y+plano.mNormal[2]*camarapos.z-plano.mDistance;
		if(distancia>=0){//si es mayor o igual que 0 la camara esta delante del plano si es menor detras
			indice=nodo.mChildren[0];
		}
		else{
			indice=nodo.mChildren[1];
		}
	}

	return -indice-1;
}
///devuelve verdadero si la "habitación" u hoja se puede ver desde la hoja actual del arbol bsp///
bool CNivel::ClusterVisible(int actual,int hojacluster)
{
	//calcular las habitaciones visibles
	//mas info en http://graphics.cs.brown.edu/games/quake/quake3.html seccion Visible Face Determination
	if(!mapa.mVisData.mBuffer || actual <0) return 1;

	unsigned char visSet= mapa.mVisData.mBuffer[(actual*mapa.mVisData.mBytesPerCluster)+(hojacluster>>3)];
	bool resultado=(visSet & (1<<((hojacluster)& 7)))!=0;
	return (resultado);

}
///carga los lightmaps y los guarda en vector vlightmaps 
//la variable brillo aumenta o disminuye la luminusidad del lightmap
void CNivel::GeneraLightmaps(void)
{

	float r,g,b,temp,brillo,escala;
	int c=0;
	brillo=5;
	
	vlightmaps.resize(mapa.mLightMaps.size());
	for(int i=0;i<vlightmaps.size();i++){
		vlightmaps[i].data=new GLubyte[128*128*3];
		vlightmaps[i].height=128;
		vlightmaps[i].width=128;
		c=0;
		//memcpy(vlightmaps[i].data,mapa.mLightMaps[i].mMapData,128*128*3);
		//vlightmaps[i].data=(GLubyte *)mapa.mLightMaps[i].mMapData;
		for(int y=0;y<128;y++){
			for(int x=0;x<128;x++){

				temp=0;
				
				escala=1.0f;
				r=0.0;
				g=0.0;
				b=0.0;
				r=(float)mapa.mLightMaps[i].mMapData[x][y][0];
				g=(float)mapa.mLightMaps[i].mMapData[x][y][1];
				b=(float)mapa.mLightMaps[i].mMapData[x][y][2];
				r=r*brillo/255.0;
				g=g*brillo/255.0;
				b=b*brillo/255.0;
				if(r > 1.0f && (temp = (1.0f/r)) < escala) escala=temp;
				if(g > 1.0f && (temp = (1.0f/g)) < escala) escala=temp;	
				if(b > 1.0f && (temp = (1.0f/b)) < escala) escala=temp;

				escala*=255.0f; 
				r*=escala;
				g*=escala;
				b*=escala;
				vlightmaps[i].data[c]=(unsigned char)r;
				vlightmaps[i].data[c+1]=(unsigned char)g;
				vlightmaps[i].data[c+2]=(unsigned char)b;

				c+=3;
			}
		}
		glGenTextures(1, &vlightmaps[i].texID);
		glBindTexture(GL_TEXTURE_2D, vlightmaps[i].texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, vlightmaps[i].width, vlightmaps[i].height,
				      GL_RGB, GL_UNSIGNED_BYTE, vlightmaps[i].data);
	}

}
void CNivel::GeneraTexturas(void)
{
	
	std::string temp;
	std::string temp2,temp3;
		char *ruta;

	int c=0;
	vtexturas.resize(mapa.mTextures.size());
	for(int i=0;i<vtexturas.size();i++){
		c=0;

		while(mapa.mTextures[i].mName[c]!=0){//convertir la ruta al formato adecuado
			if(mapa.mTextures[i].mName[c]=='/'){
				temp.push_back('/');
				temp.push_back('/');
			}
			else
				temp.push_back( mapa.mTextures[i].mName[c]);
			c++;
		}
		temp2=temp+".tga";
		temp3=temp+".jpg";
		

		if(fopen(temp2.data(),"r"))//mirar que extension es
		{
			ruta=new char[temp2.size()+1];
			strcpy(ruta,temp2.c_str());
			vtexturas[i].LoadTexture(ruta);
			delete [] ruta;
		}
		if(fopen(temp3.data(),"r"))
		{
			ruta=new char[temp3.size()+1];
			strcpy(ruta,temp3.c_str());
			vtexturas[i].LoadTexture(ruta);
			delete [] ruta;
		
		}


		temp.clear();

		glGenTextures(1, &vtexturas[i].texID);
		glBindTexture(GL_TEXTURE_2D, vtexturas[i].texID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, vtexturas[i].width, vtexturas[i].height,
				      GL_RGB, GL_UNSIGNED_BYTE, vtexturas[i].data);
	}
}
void CNivel::ComprobarNodo(int nodo_indice,float fraccion_ini,float fraccion_final,CVector Pinicial,CVector Pfinal){
	
	if(nodo_indice<0)
	{
		TLeaf *hoja=&mapa.mLeaves[-(nodo_indice+1)];
		for(int i=0;i<hoja->mNbLeafBrushes;i++){
			TBrush *elbrush=&mapa.mBrushes[mapa.mLeafBrushes[hoja->mLeafBrush+i].mBrushIndex];
			if(elbrush->mNbBrushSides>0 && mapa.mTextures[elbrush->mTextureIndex].mContents & 1 )
				ComprobarBrush(elbrush,Pinicial,Pfinal);

		}

		return;
	}
    const TNode* nodo=&mapa.mNodes[nodo_indice];
	const TPlane * plano=&mapa.mPlanes[nodo->mPlane];

	float distancia_inicial= (plano->mNormal[0]*Pinicial.x+plano->mNormal[1]*Pinicial.y+plano->mNormal[2]*Pinicial.z)-plano->mDistance;//obtener la distancia al plano del punto de inicio de la recta
	float distancia_final=(plano->mNormal[0]*Pfinal.x+plano->mNormal[1]*Pfinal.y+plano->mNormal[2]*Pfinal.z)-plano->mDistance;//obtener la distancia al plano del punto final de la recta
	float offset=0;
	if(this->tipo_trazado==TT_ESFERA)
		offset=this->radioEsfera;
	if(tipo_trazado==TT_RAYO)
		offset=0.0f;
	////3 situaciones posibles con los valores calculados en las lineas anteriores///
	if(distancia_inicial >=offset && distancia_final>=offset){// 1º los dos puntos estan delante del plano se continua por el hijo izquierdo
		ComprobarNodo(nodo->mChildren[0],fraccion_ini,fraccion_final,Pinicial,Pfinal);
	}
	else if (distancia_inicial <-offset && distancia_final<-offset){ //2º los dos puntos estan detras del plano se continua por el hijo derecho
		ComprobarNodo(nodo->mChildren[1],fraccion_ini,fraccion_final,Pinicial,Pfinal);
	}
	else{// 3º uno de los puntos esta delante del plano y el otro detras
		int lado=0;
		float fraccion1=1.0f,fraccion2=0.0f,mitadfraccion=0.0f;
		CVector mitad;
		if(distancia_inicial<distancia_final){//primer paso se comparan las distancias para saber a que nodo(izq o derecho) debemos ir
			lado=1;//se divide la recta en 2 partes (la que esta delante del plano y la que esta detras del plano)
			float distancia_inversa=1.0f/(distancia_inicial-distancia_final);
			fraccion1=(distancia_inicial-offset-EPSILON)*distancia_inversa;
			fraccion2=(distancia_inicial+offset+EPSILON)*distancia_inversa;
		}
		else if(distancia_final<distancia_inicial){
			lado=0;
			float distancia_inversa=1.0f/(distancia_inicial-distancia_final);
			fraccion1=(distancia_inicial+offset+EPSILON)*distancia_inversa;
			fraccion2=(distancia_inicial-offset-EPSILON)*distancia_inversa;
		}
		/*else{
		 lado=0;
		 fraccion1=1.0f;
		 fraccion2=0.0f;
		}*/
		
		//segundo paso 
		//hacer que los valores esten entre 0 y 1
		if(fraccion1<0.0f) 
			fraccion1=0.0f;
		else if(fraccion1>1.0f)
			fraccion1=1.0f;

		if(fraccion2<0.0f) 
			fraccion2=0.0f;
		else if(fraccion2>1.0f)
			fraccion2=1.0f;
		///3º paso calcular el punto medio
		mitadfraccion=fraccion_ini+(fraccion_final-fraccion_ini)*fraccion1;

		mitad.x=Pinicial.x+fraccion1*(Pfinal.x-Pinicial.x);
		mitad.y=Pinicial.y+fraccion1*(Pfinal.y-Pinicial.y);
		mitad.z=Pinicial.z+fraccion1*(Pfinal.z-Pinicial.z);


		ComprobarNodo(nodo->mChildren[lado],fraccion_ini,mitadfraccion,Pinicial,mitad);//4º se realiza llamada recursiva al lado del plano obtenido desde el punto inicial al punto medio

		//5º paso calcular el punto medio con el otro segmento de la recta que va desde la mitad hasta el punto final
		mitadfraccion=fraccion_ini+(fraccion_final-fraccion_ini)*fraccion2;

		mitad.x=Pinicial.x+fraccion2*(Pfinal.x-Pinicial.x);
		mitad.y=Pinicial.y+fraccion2*(Pfinal.y-Pinicial.y);
		mitad.z=Pinicial.z+fraccion2*(Pfinal.z-Pinicial.z);

		if(lado==1)
			ComprobarNodo(nodo->mChildren[0],mitadfraccion,fraccion_final,mitad,Pfinal);
		else
			ComprobarNodo(nodo->mChildren[1],mitadfraccion,fraccion_final,mitad,Pfinal);
	
			

	}
}
void CNivel::ComprobarBrush(TBrush *brush,CVector vInicio,CVector vFinal){
	//cada brush es un conjunto de planos que encierra un area convexa para las colisiones
	float fraccionInicio=-1.0f;
	float fraccionFinal=1.0f;
	bool inicioFuera=false;
	///bool finFuera=false;
	float offset=0;
	float distanciaInicio;
	float distanciaFinal;
	if(tipo_trazado==TT_ESFERA)
		offset=radioEsfera;
	if(tipo_trazado==TT_RAYO)
		offset=0.0f;
	for(int i=0;i<brush->mNbBrushSides;i++){//recorrer todos los planos que forman el brush
		TBrushSide * brushside=&mapa.mBrushSides[brush->mBrushSide+i];
		TPlane * plano=&mapa.mPlanes[brushside->mPlaneIndex];


		distanciaInicio=(plano->mNormal[0]*vInicio.x+plano->mNormal[1]*vInicio.y+plano->mNormal[2]*vInicio.z)-(plano->mDistance+offset);//calcular la distancia al plano para calcular la interseccion con el plano
		distanciaFinal=(plano->mNormal[0]*vFinal.x+plano->mNormal[1]*vFinal.y+plano->mNormal[2]*vFinal.z)-(plano->mDistance+offset);
		if(distanciaInicio>0)
			inicioFuera=true;

//		if(distanciaFinal>0)
//		finFuera=false;

		if(distanciaInicio>0 && distanciaFinal >0)//comprobacion que el segmento este dentro del brush ,se descarta en este caso
			return;
		if(distanciaInicio<=0 && distanciaFinal <=0)//comprobacion que el punto atraviese el brush no se continua evaluando
			continue;

		if(distanciaInicio>distanciaFinal){
			//el segmento esta dentro del brush
			float fraccion1=(distanciaInicio-EPSILON)/(distanciaInicio-distanciaFinal);
			if(fraccion1>fraccionInicio){
				fraccionInicio=fraccion1;
				colision=true;
			}
		}
		else{
			//el segmento no esta dentro del brush
			float fraccion1=(distanciaInicio+EPSILON)/(distanciaInicio-distanciaFinal);
			if(fraccion1<fraccionFinal)
				fraccionFinal=fraccion1;
		}
	}

	if(inicioFuera==false){
		/*outputStartOut=false;
		if(finFuera==false)
			outputAllSolid=true;*/
		return;
	}
	if(fraccionInicio<fraccionFinal)
	{
		if(fraccionInicio>-1 && fraccionInicio<outputFraction){
			if(fraccionInicio<0)
				fraccionInicio=0;
			outputFraction=fraccionInicio;
		}
	}
	
}
CVector CNivel::Trazar(CVector inicio,CVector  fin){
	colision=false;
	CVector temp;
	outputFraction=1.0f;
	ComprobarNodo(0,0.0f,1.0f,inicio,fin);
	if(outputFraction==1.0f){
		return fin;
	}
	else
	{  
		colision=true;
		temp.x=inicio.x+outputFraction*(fin.x-inicio.x);	
		temp.y=inicio.y+outputFraction*(fin.y-inicio.y);	
		temp.z=inicio.z+outputFraction*(fin.z-inicio.z);
		
	}
return temp;
}

CVector CNivel::TrazaRayo(CVector inicio,CVector fin){
	tipo_trazado=TT_RAYO;
	return Trazar(inicio,fin);
}

CVector CNivel::TrazaEsfera(CVector inicio,CVector fin,float radio){
	radioEsfera=radio;

	tipo_trazado=TT_ESFERA;
	return Trazar(inicio,fin);

}
