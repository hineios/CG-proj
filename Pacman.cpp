#include <stdlib.h>
#include <stdio.h>
#include "Pacman.h"
#include "Definitions.h"
#include <math.h>

using namespace game;

float Pacman::xpoz = 14.5;
float Pacman::ypoz = 8.0;
int Pacman::state = STATE_DOWN;
int Pacman::turn_state = STATE_DOWN;
int Pacman::lives = 3;
float Pacman::score = 0;
int Pacman::xnormal = 0;
int Pacman::ynormal = -1;
bool Pacman::dead = false;

Pacman::Pacman(){}

Pacman::~Pacman(){}

float Pacman::getXPoz(){return xpoz;}
float Pacman::getYPoz(){return ypoz;}
int Pacman::getState(){return state;}
int Pacman::getLives(){return lives;}
void Pacman::initParticulasAux(){
		GLfloat v, theta, phi;
		int i;

 for(i=0; i<MAX_PARTICULAS; i++)
    {
	v = 0.8*frand()+0.3;
    phi = frand()*PI;
    theta = 2.0*frand()*PI;
    particula[i].x = -50;
    particula[i].y = -50;
    particula[i].z = 1;
    particula[i].vx = v * cos(theta) * sin(phi);
    particula[i].vy = v * cos(phi);
    particula[i].vz = v * sin(theta) * sin(phi);
	particula[i].ax =  0.01f; /* simular um pouco de vento */
    particula[i].ay = -0.15f; /* simular a aceleração da gravidade */
    particula[i].az =  -0.20f;
	
	/* tom amarelado que vai ser multiplicado pela textura que varia entre branco e preto */
	particula[i].r = PACMAN_BODY_COLOR_R;
	particula[i].g = PACMAN_BODY_COLOR_G;	
	particula[i].b = PACMAN_BODY_COLOR_B;

	particula[i].life = 1.0f;		/* vida inicial */                
	particula[i].fade = 0.03f;	    /* step de decréscimo da vida para cada iteração */
	}
}

float Pacman::getScore(){return score;}
int Pacman::getXNormal() {return xnormal;}
int Pacman::getYNormal() {return ynormal;}
void Pacman::turnDown() {turn_state = STATE_DOWN;}
void Pacman::turnUp(){turn_state = STATE_UP;}
void Pacman::turnRight(){turn_state = STATE_RIGHT;}
void Pacman::turnLeft(){turn_state = STATE_LEFT;}
void Pacman::load(){
	if(dead){
		state = STATE_DOWN;
		turn_state = STATE_DOWN;
		lives -= 1;
		xnormal = 0;
		ynormal = -1;
		xpoz = 14.5;
		ypoz = 8.0;
	}
	else{
		glPushMatrix();
			glTranslatef(xpoz,ypoz,1.0);
			glRotatef(state,0,0,1);
			glRotatef(90,1,0,0);
		//Body
			glPushMatrix();
				GLfloat matPacman[] = {PACMAN_BODY_COLOR_R, PACMAN_BODY_COLOR_G, PACMAN_BODY_COLOR_B};
				glMaterialfv( GL_FRONT, GL_DIFFUSE, matPacman);
				GLfloat matPacman_specular[] = { 0., 0., 0., 1.0 };
				glMaterialfv( GL_FRONT, GL_SPECULAR, matPacman_specular);

				glutSolidSphere(0.9,100.,100.);
			glPopMatrix(); 
		//Eyes
			glPushMatrix();
				GLfloat matPacmanEye[] = {PACMAN_EYES_COLOR_R, PACMAN_EYES_COLOR_G, PACMAN_EYES_COLOR_B};
				glMaterialfv( GL_FRONT, GL_DIFFUSE, matPacmanEye);
				glTranslatef(0.35, 0.2, 0.7);
				glutSolidSphere(0.25, 50.0, 50.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.35, 0.2, 0.7);
				glutSolidSphere(0.25, 50.0, 50.0);
			glPopMatrix();
		//Eyebrows
			glPushMatrix();
				GLfloat matPacmanEyebrows[] = {PACMAN_EYEBROW_COLOR_R, PACMAN_EYEBROW_COLOR_G,PACMAN_EYEBROW_COLOR_B};
				glMaterialfv( GL_FRONT, GL_DIFFUSE, matPacmanEyebrows);
				glTranslatef(0.4, 0.5, 0.8);
				glRotatef(10,0,0,-1);
				glScalef(3.0, 0.8, 1.0);
				glutSolidSphere(0.1, 50.0, 50.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.4 , 0.5, 0.8);
				glRotatef(10,0,0,1);
				glScalef(3.0, 0.8, 1.0);
				glutSolidSphere(0.1, 50.0, 50.0);
			glPopMatrix();
		//Iris
			glPushMatrix();
				GLfloat matPacmanE[] = {PACMAN_EYEBROW_COLOR_R, PACMAN_EYEBROW_COLOR_G,PACMAN_EYEBROW_COLOR_B};
				glMaterialfv( GL_FRONT, GL_DIFFUSE, matPacmanEyebrows);
				glTranslatef(0.35, 0.2,0.855);
				glutSolidSphere(0.12, 10.0, 10.0);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-0.35, 0.2, 0.855);
				glutSolidSphere(0.12, 10.0, 10.0);
			glPopMatrix();		
		glPopMatrix();
	}
}

void Pacman::move(int** matrix2D, int* ghost1, int* ghost2, int* ghost3, int* ghost4){
	int c = (int)floor(xpoz+0.5);
	int l = (int)floor(ypoz+0.5);
	switch(turn_state){
		case STATE_UP:
			moveUp(matrix2D);
			break;
		case STATE_DOWN:
			moveDown(matrix2D);
			break;
		case STATE_RIGHT:
			moveRight(matrix2D);
			break;
		case STATE_LEFT:
			moveLeft(matrix2D);
			break;
		default:
			break;
	}
	//Comer peças
	if ((matrix2D[l][c])==1) {
		matrix2D[l][c]=3;
		score +=10;
	}
	else{
		if((matrix2D[l][c])==2) {
			matrix2D[l][c]=3;
			score +=50;
			*ghost1 = GHOST_STATE_FRIGHTENED;
			*ghost2 = GHOST_STATE_FRIGHTENED;
			*ghost3 = GHOST_STATE_FRIGHTENED;
			*ghost4 = GHOST_STATE_FRIGHTENED;
		}
	}
}
void Pacman::moveLeft(int** matrix2D){
	int c;
	int l;
	xnormal = -1;
	ynormal = 0;
	switch(state){
		case STATE_UP:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l][c-1] != 0){
				xpoz = xpoz-ACT_RATE;
				ypoz = (float) l;
				state = STATE_LEFT;
			}
			else{
				turn_state = STATE_UP;
				moveUp(matrix2D);
				turn_state = STATE_LEFT;
			}
			break;
		case STATE_DOWN:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l][c-1] != 0){
				xpoz = xpoz-ACT_RATE;
				ypoz = (float) l;
				state = STATE_LEFT;
			}
			else{
				turn_state = STATE_DOWN;
				moveDown(matrix2D);
				turn_state = STATE_LEFT;
			}
			break;
		case STATE_RIGHT:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l][c-1] != 0){
				xpoz = xpoz-ACT_RATE;
				state = STATE_LEFT;
			}
			else{
				turn_state = STATE_RIGHT;
				moveRight(matrix2D);
				turn_state = STATE_LEFT;
			}
			break;
		case STATE_LEFT:
			c = (int)ceil(xpoz);
			l = (int)ceil(ypoz);
			if(matrix2D[l][c-1] != 0){
				xpoz = xpoz-ACT_RATE;
				state = STATE_LEFT;
			}
			break;
		default:
			break;
	}
}

void Pacman::moveRight(int** matrix2D){
	int c;
	int l;
	xnormal=1;
	ynormal=0;
	switch(state){
		case STATE_UP:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l][c+1] != 0){
				xpoz = xpoz+ACT_RATE;
				ypoz = (float) l;
				state = STATE_RIGHT;
			}
			else{
				turn_state = STATE_UP;
				moveUp(matrix2D);
				turn_state = STATE_RIGHT;
			}
			break;
		case STATE_DOWN:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l][c+1] != 0){
				xpoz = xpoz+ACT_RATE;
				ypoz = (float) l;
				state = STATE_RIGHT;
			}
			else{
				turn_state = STATE_DOWN;
				moveDown(matrix2D);
				turn_state = STATE_RIGHT;
			}
			break;
		case STATE_RIGHT:
			c = (int)floor(xpoz);
			l = (int)floor(ypoz);
			if(matrix2D[l][c+1] != 0){
				xpoz = xpoz+ACT_RATE;
				state = STATE_RIGHT;
			}
			break;
		case STATE_LEFT:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l][c+1] != 0){
				xpoz = xpoz+ACT_RATE;
				state = STATE_RIGHT;
			}
			else{
				turn_state = STATE_LEFT;
				moveLeft(matrix2D);
				turn_state = STATE_RIGHT;
			}
			break;
		default:
			break;
	}
}

void Pacman::moveUp(int** matrix2D){
	int c;
	int l;
	xnormal=0;
	ynormal=1;
	switch(state){
		case STATE_UP:
			c = (int)floor(xpoz);
			l = (int)floor(ypoz);
			if(matrix2D[l+1][c] != 0){
				ypoz = ypoz+ACT_RATE;
				state = STATE_UP;
			}
			break;
		case STATE_DOWN:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l+1][c] != 0){
				ypoz = ypoz+ACT_RATE;
				state = STATE_UP;
			}
			else{
				turn_state = STATE_DOWN;
				moveDown(matrix2D);
				turn_state = STATE_UP;
			}
			break;
		case STATE_RIGHT:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l+1][c] != 0){
				xpoz = (float) c;
				ypoz = ypoz+ACT_RATE;
				state = STATE_UP;
			}
			else{
				turn_state = STATE_RIGHT;
				moveRight(matrix2D);
				turn_state = STATE_UP;
			}
			break;
		case STATE_LEFT:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l+1][c] != 0){
				xpoz = (float) c;
				ypoz = ypoz+ACT_RATE;
				state = STATE_UP;
			}
			else{
				turn_state = STATE_LEFT;
				moveLeft(matrix2D);
				turn_state = STATE_UP;
			}
			break;
		default:
			break;
	}
}

void Pacman::moveDown(int** matrix2D){
	int c;
	int l;
	xnormal=0;
	ynormal=-1;
	switch(state){
		case STATE_UP:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l-1][c] != 0){
				ypoz = ypoz-ACT_RATE;
				state = STATE_DOWN;
			}
			else{
				turn_state = STATE_UP;
				moveUp(matrix2D);
				turn_state = STATE_DOWN;
			}
			break;
		case STATE_DOWN:
			c = (int)ceil(xpoz);
			l = (int)ceil(ypoz);
			if(matrix2D[l-1][c] != 0){
				ypoz = ypoz-ACT_RATE;
				state = STATE_DOWN;
			}
			break;
		case STATE_RIGHT:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l-1][c] != 0){
				xpoz = (float) c;
				ypoz = ypoz-ACT_RATE;
				state = STATE_DOWN;
			}
			else{
				turn_state = STATE_RIGHT;
				moveRight(matrix2D);
				turn_state = STATE_DOWN;
			}
			break;
		case STATE_LEFT:
			c = (int)floor(xpoz+0.5);
			l = (int)floor(ypoz+0.5);
			if(matrix2D[l-1][c] != 0){
				xpoz = (float) c;
				ypoz = ypoz-ACT_RATE;
				state = STATE_DOWN;
			}
			else{
				turn_state = STATE_LEFT;
				moveLeft(matrix2D);
				turn_state = STATE_DOWN;
			}
			break;
		default:
			break;
	}
}

void Pacman::initParticulas(int xpoz,int ypoz){
		GLfloat v, theta, phi;
		int i;

 for(i=0; i<MAX_PARTICULAS; i++)
    {
	v = 0.8*frand()+0.3;
    phi = frand()*PI;
    theta = 2.0*frand()*PI;
    particula[i].x = xpoz;
    particula[i].y = ypoz;
    particula[i].z = 1;
    particula[i].vx = v * cos(theta) * sin(phi);
    particula[i].vy = v * cos(phi);
    particula[i].vz = v * sin(theta) * sin(phi);
	particula[i].ax =  0.01f; /* simular um pouco de vento */
    particula[i].ay = -0.15f; /* simular a aceleração da gravidade */
    particula[i].az =  -0.20f;
	
	/* tom amarelado que vai ser multiplicado pela textura que varia entre branco e preto */
	particula[i].r = PACMAN_BODY_COLOR_R;
	particula[i].g = PACMAN_BODY_COLOR_G;	
	particula[i].b = PACMAN_BODY_COLOR_B;

	particula[i].life = 1.0f;		/* vida inicial */                
	particula[i].fade = 0.03f;	    /* step de decréscimo da vida para cada iteração */
	}
}

void Pacman::setParticulas(){

	int i;
	float h; 

	/* Método de Euler de integração de eq. diferenciais ordinárias 
		h representa o step de tempo; dv/dt = a; dx/dt = v; e conhecem-se os valores iniciais de x e v */

	h=0.125f;
	for (i=0; i<MAX_PARTICULAS; i++)
	{
		particula[i].x += (h*particula[i].vx);
		particula[i].y += (h*particula[i].vy);
		particula[i].z += (h*particula[i].vz);
		particula[i].vx += (h*particula[i].ax);
		particula[i].vy += (h*particula[i].ay);
		particula[i].vz += (h*particula[i].az);
		particula[i].life -= particula[i].fade;
	}
}

void Pacman::kaBoom(){
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);//Ativa a Transparência
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//Perspectiva  
	
	int i;
	for (i=0; i<MAX_PARTICULAS; i++)
	{
		if(particula[i].life > 0.0f) /* só desenha as que ainda estão vivas */
		{

			/* A vida da partícula representa o canal alpha da cor. Como o blend está activo a cor final é a soma da cor rgb do fragmento multiplicada pelo
			alpha com a cor do pixel destino */
			GLfloat matPacman[] = {particula[i].r,particula[i].g,particula[i].b, particula[i].life};
			glMaterialfv( GL_FRONT, GL_DIFFUSE, matPacman);

			glBegin(GL_POINTS);	/* 4 vértices - 2 triangulos: v0 v1 v2; v1 v2 v3 */			         
			glVertex3f(particula[i].x,particula[i].y,particula[i].z);    
			glEnd();	
		}
	}
	glDisable(GL_BLEND);


}
void Pacman::kill(){dead = true;}
void Pacman::revive(){dead = false;}
bool Pacman::getDead(){return dead;}
