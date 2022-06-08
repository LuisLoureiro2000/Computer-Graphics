#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <GL/freeglut.h>

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define D_BROWN	 0.2, 0.0, 0.0, 0.0
#define L_BROWN	 0.6, 0.4, 0.0, 0.0
#define PI		 3.14159

#include "RgbImage.h"

extern float h;
GLUquadricObj* ceu = gluNewQuadric();

//================================================================================
//===========================================================Variaveis e constantes
void initMaterials(int material);

char Materiais[18][30] = {
	"Esmerald",  "Jade",  "obsidian",    "Pearl",        "Ruby",
	"Turquoise", "Brass", "Bronze",      "Chrome",       "Copper",
	"Gold",      "Silver","blackPlastic","cyankPlastic", "greenPlastic",
	"redPlastic", "whitePlastic","yellowPlastic" };

GLboolean ligateto = true;
GLboolean ligateto2 = true;
GLfloat angulo_porta = 0.0;
GLfloat angulo_pequena = 0.0;
GLfloat angulo_janela = 0.3;
struct tm timeinfo;
GLint hour, minute, second;
char texto[30];
GLfloat tam = 1;
GLfloat bs = 1;
GLuint   texture[5];
RgbImage imag;
GLint luzB = 0;
GLint luzG = 1;
GLint luzR = 1;
GLint luzB2 = 1;
GLint luzG2 = 1;
GLint luzR2 = 0;
GLfloat intensidadeT = 0.1;
GLfloat localPos[4] = { 0.5, 1, 0.5, 1.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };
GLint	  dim = 64;
//Direcional
GLfloat intensidadeT2 = 0.1;
GLfloat localPos2[4] = { -0.5, -1, -0.5, 0.0 };
GLfloat localCorDif2[4] = { luzR2, luzG2, luzB2, 0.0 };
GLfloat localCorEsp2[4] = { luzR2, luzG2, luzB2, 0.0 };


static GLfloat vertices[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
		-tam,  -tam,  tam,	// 0 
		-tam,   tam,  tam,	// 1 
		-tam,   tam, -tam,	// 2 
		-tam,  -tam, -tam,	// 3 
	//…………………………………………………… Direita
		 tam,  -tam,  tam,	// 4 
		 tam,   tam,  tam,	// 5 
		 tam,   tam, -tam,	// 6 
		 tam,  -tam, -tam,	// 7 
	//……………………………………………………… Cima
		-tam,  tam,  tam,	// 8 
		-tam,  tam, -tam,	// 9 
		 tam,  tam, -tam,	// 10 
		 tam,  tam,  tam,	// 11 
	//……………………………………………………… Baixo
		-tam,-tam,tam,		// 12
		-tam, -tam, -tam,	// 13
		 tam, -tam, -tam,	// 14
		 tam,  -tam,  tam,	// 15
	//……………………………………………………… frente
		-tam,  -tam,  tam, // 16
		tam,  -tam,  tam,	 // 17
		tam,   tam,  tam,	 // 18
		-tam,   tam,  tam, // 19
	//……………………………………………………… tras
		-tam,  -tam, -tam, // 20
		tam,  -tam, -tam,	 // 21
		tam,   tam, -tam,	 // 22
		-tam,  tam, -tam,	 // 23
};


static GLfloat normais[] = {
	//…………………………………………………………………………………………………… x=tam (Esquerda)
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  -1.0,  0.0,  0.0,
	  //…………………………………………………………………………………………………… x=tam (Direita)
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		//…………………………………………………………………………………………………… y=tam (Cima)
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   0.0,  1.0,  0.0,
	   //…………………………………………………………………………………………………… y=tam (Baixo)
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   0.0,  -1.0,  0.0,
	   //…………………………………………………………………………………………………… y=tam (Frente)
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   //…………………………………………………………………………………………………… y=tam (tras)
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	L_BROWN,
	D_BROWN,
	D_BROWN,
	D_BROWN,
	D_BROWN,
	D_BROWN,
	D_BROWN,
	D_BROWN,
	D_BROWN,
};
static GLfloat cor_pequena[] = {
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
	BLUE,
};
static GLfloat cor_parede[] = {
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
	WHITE,
};
static GLfloat cor_janela[] = {
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
	GREEN,
};
static GLfloat texturas[] = {
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1
};

// nao está feito !!


//=========================================================== FACES DA PORTA
GLboolean   frenteVisivel = 1;
static GLuint     cima[] = { 8, 11, 10,  9 };   // regra da mao direita
static GLuint	  esquerda[] = { 1,2,3,0 };
static GLuint	  direita[] = { 4,7,6,5 };
static GLuint	  baixo[] = { 12,13,14,15 };
static GLuint	  frente[] = { 16,17,18,19 };
static GLuint	  tras[] = { 21,20,23,22 };


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador 
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat  angZoom = 90;
GLfloat  incZoom = 3;



//================================================================================
//=========================================================================== INIT
void initTexturas()
{
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("madeira_cao.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("vidro.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("porta_cao.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("malha.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	imag.LoadBmpFile("parede.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}
void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	if (ligateto)  glEnable(GL_LIGHT0);
	else   		  glDisable(GL_LIGHT0);
}

void iluminacao2() {
	glLightfv(GL_LIGHT1, GL_POSITION, localPos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, localCorDif2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, localCorEsp2);
	if (ligateto2)  glEnable(GL_LIGHT1);
	else   		  glDisable(GL_LIGHT1);
}

void initLights(void) {

	//…………………………………………………………………………………………………………………………………………… Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	glLightfv(GL_LIGHT1, GL_POSITION, localPos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, localCorDif2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, localCorEsp2);
}

void inicializa(void)
{
	glClearColor(BLACK);		//………………………………………………………………………………Apagar
	glEnable(GL_DEPTH_TEST);	//………………………………………………………………………………Profundidade
	glShadeModel(GL_SMOOTH);	//………………………………………………………………………………Interpolacao de cores	
	initTexturas();
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	initLights();
	initMaterials(22);

	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);


}

void draw_ceu()
{
	if (frenteVisivel);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	gluQuadricDrawStyle(ceu, GLU_FILL);
	gluQuadricNormals(ceu, GLU_SMOOTH);
	gluQuadricTexture(ceu, GL_TRUE);
	gluSphere(ceu, 10.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();

}
void updateLuz() {
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

void updateLuz2() {
	localCorDif2[0] = luzR2 * intensidadeT2;
	localCorDif2[1] = luzG2 * intensidadeT2;
	localCorDif2[2] = luzB2 * intensidadeT2;
	localCorEsp2[0] = luzR2 * intensidadeT2;
	localCorEsp2[1] = luzG2 * intensidadeT2;
	localCorEsp2[2] = luzB2 * intensidadeT2;
	glLightfv(GL_LIGHT1, GL_DIFFUSE, localCorDif2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, localCorEsp2);
}

void desenha_porta() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	initMaterials(1);
	glNormal3f(0, 1, 0);
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
	glPushMatrix();
	glTranslatef(-tam, 0, -tam / 10);
	glRotatef(angulo_porta, 0, 1, 0);
	glTranslatef(tam, 0, tam / 10);
	glTranslatef(-0.8, 0, 0);
	glScalef(0.2, 2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-tam, 0, -tam / 10);
	glRotatef(angulo_porta, 0, 1, 0);
	glTranslatef(tam, 0, tam / 10);
	glTranslatef(0.8, 0, 0);
	glScalef(0.2, 2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-tam, 0, -tam / 10);
	glRotatef(angulo_porta, 0, 1, 0);
	glTranslatef(tam, 0, tam / 10);
	glTranslatef(0, -0.3, 0);
	glScalef(1, 0.5, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-tam, 0, -tam / 10);
	glRotatef(angulo_porta, 0, 1, 0);
	glTranslatef(tam, 0, tam / 10);
	glTranslatef(0, 1.8, 0);
	glScalef(1, 0.3, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void desenha_janela() {
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	initMaterials(5);
	glNormal3f(0, 1, 0);
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, cor_janela);
	glEnableClientState(GL_COLOR_ARRAY);
	glPushMatrix();
	glTranslatef(-tam, 0, -tam / 10);
	glRotatef(angulo_porta, 0, 1, 0);
	glTranslatef(tam, 0, tam / 10);
	glTranslatef(0, 0.85, 0);
	glTranslatef(angulo_janela, 0, 0);
	glScalef(0.3, 0.6, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void desenha_parede() {
	initMaterials(8);
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores PAREDE
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, cor_parede);
	glEnableClientState(GL_COLOR_ARRAY);
	glPushMatrix();
	glTranslatef(3.2, 0.2, 0);
	glScalef(2, 2.2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-3.2, 0.2, 0);
	glScalef(2, 2.2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glScalef(0.6, 1, 1);
	glRotatef(90, 0, 0, 1);
	glTranslatef(2.3, 0, 0);
	glScalef(0.1, 2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-2, 0.2, -5);
	glScalef(2, 2.2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0, 1, 0);
	glTranslatef(-2, 0.2, 5);
	glScalef(2, 2.2, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(1.2, -2, 0.35);
	glScalef(2, 2.2, 0.2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	float			med_dim = (float)dim / 2;
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void desenha_pequena() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	initMaterials(17);
	glNormal3f(0, 1, 0);
	glVertexPointer(3, GL_FLOAT, 0, vertices); //………………………………………VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, cor_pequena);
	glEnableClientState(GL_COLOR_ARRAY);
	glPushMatrix();
	glTranslatef(-tam, 0, -tam / 10);
	glRotatef(angulo_porta, 0, 1, 0);
	glTranslatef(tam, 0, tam / 10);
	glTranslatef(0, -tam / 1.4, 0);
	glRotatef(angulo_pequena, 1, 0, 0);
	glTranslatef(0, +tam / 1.4, 0);
	glTranslatef(0, -tam * 1.4, 0);
	glScalef(0.6, 0.5, 0.2);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawScene() {

	//=================================================== Qual o lado visivel ???
	//==================================== MESA
	glEnable(GL_LIGHTING);
	iluminacao();
	iluminacao2();
	draw_ceu();
	if (frenteVisivel);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	desenha_porta();
	desenha_parede();
	desenha_pequena();
	desenha_janela();
}

void display(void) {

	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Não modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= Não modificar !!!!!!!!!!!!
	glEnable(GL_LIGHTING);
	iluminacao();
	iluminacao2();

	//…………………………………………………………………………………………………………………………………………………………Objectos
	drawEixos();
	drawScene();

	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {


	switch (key) {
	case 'W':
	case 'w':
		if (angulo_pequena > -90) {
			angulo_pequena = angulo_pequena - 6;
		}
		glutPostRedisplay();
		break;

	case 'A':
	case 'a':
		//??
		if (angulo_porta < 90) {
			angulo_porta = angulo_porta + 6;
		}
		glutPostRedisplay();
		break;

	case 'S':
	case 's':
		if (angulo_pequena < 90) {
			angulo_pequena = angulo_pequena + 6;
		}
		glutPostRedisplay();
		break;

	case 'e':
	case 'E':
		if (angulo_janela <= 0.3) {
			angulo_janela = angulo_janela + 0.1;
		}
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		//??
		if (angulo_porta > 0) {
			angulo_porta = angulo_porta - 6;
		}
		glutPostRedisplay();
		break;

	case 'q':
	case 'Q':
		if (angulo_janela >= -0.2) {
			angulo_janela = angulo_janela - 0.1;
		}
		glutPostRedisplay();
		break;

		//--------------------------- Escape
	case 't':
	case 'T':
		if (ligateto) ligateto = false;
		else ligateto = true;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		luzR = (luzR + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':
	case 'G':
		luzG = (luzG + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		luzB = (luzB + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'i': case 'I':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		if (ligateto2) ligateto2 = false;
		else ligateto2 = true;
		updateLuz2();
		glutPostRedisplay();
		break;
	case 'o':
	case 'O':
		luzR2 = (luzR2 + 1) % 2;
		updateLuz2();
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		luzG2 = (luzG2 + 1) % 2;
		updateLuz2();
		glutPostRedisplay();
		break;
	case 'n':
	case 'N':
		luzB2 = (luzB2 + 1) % 2;
		updateLuz2();
		glutPostRedisplay();
		break;
	case 'u':
	case 'U':
		intensidadeT2 = intensidadeT2 + 0.1;
		if (intensidadeT2 > 1.1) intensidadeT2 = 0;
		updateLuz2();
		glutPostRedisplay();
		break;
	case 'l':
	case 'L':
		h = h + 0.1;
		glutPostRedisplay();
		break;
	case 'v':
	case 'V':
		h = h - 0.1;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar à volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)   obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN) obsP[1] = (obsP[1] - 0.1);
	if (key == GLUT_KEY_LEFT)  aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT) aVisao = (aVisao - 0.1);
	if (key == GLUT_KEY_CTRL_L) rVisao = rVisao + 0.1;
	if (key == GLUT_KEY_CTRL_R) rVisao = rVisao - 0.1;
	if (obsP[1] > yC)   obsP[1] = yC;   // limita altura
	if (obsP[1] < -yC)  obsP[1] = -yC;

	obsP[0] = rVisao * cos(aVisao);      // actualiza posicao (X,Z)
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("{jh,ep}@dei.uc.pt|    |Mover Porta do cão: 's' e 'w'|   |Abrir Porta grande: 'a' e 'd'|      |Observador:'SETAS'|        |Mover janela verde: 'q' e 'e'| ");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}


