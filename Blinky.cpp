#include <stdlib.h>
#include <stdio.h>
#include "Blinky.h"
#include "Definitions.h"
#include <math.h>
#include <iostream>
using namespace std;
using namespace game;

Blinky::Blinky(){
	angle = 0;
	jail_time = 0;
	jail = false;
	xpoz = BLINKY_START_X;
	ypoz = BLINKY_START_Y;
	state = GHOST_STATE_NORMAL;
	move_state = STATE_RIGHT;
}
Blinky::~Blinky(){}

int* Blinky::getState(){return &state;}
void Blinky::load(){
	GLfloat matBody[3];
	//Clyde
	glPushMatrix();
		glTranslatef(xpoz,ypoz,0.0);
		glRotatef((angle+90.0),0.0,0.0,0.1);
		glScalef(0.5,0.5,0.5);
		if(state == GHOST_STATE_NORMAL){
			matBody[0] = BLINKY_COLOR_R;
			matBody[1] = BLINKY_COLOR_G;
			matBody[2] = BLINKY_COLOR_B;
		}
		else{
			matBody[0] = 1.0;
			matBody[1] = 1.0;
			matBody[2] = 1.0;
		}
		glMaterialfv( GL_FRONT, GL_DIFFUSE, matBody);
		
		glBegin(GL_POLYGON);//base
			glNormal3f( 0.0, 0.0, -1.0);
			glVertex3f(-1.5,-0.5,0.5);
			glVertex3f(-0.5,-1.5,0.5);
			glVertex3f(0.5,-1.5,0.5);
			glVertex3f(1.5,-0.5,0.5);
			glVertex3f(1.5,0.5,0.5);
			glVertex3f(0.5,1.5,0.5);
			glVertex3f(-0.5,1.5,0.5);
			glVertex3f(-1.5,0.5,0.5);
		 glEnd();

		glBegin(GL_POLYGON);//topo
			glNormal3f( 0.0, 0.0, 1.0);
			glVertex3f(-1.5,-0.5,3.0);
			glVertex3f(-0.5,-1.5,3.0);
			glVertex3f(0.5,-1.5,3.0);
			glVertex3f(1.5,-0.5,3.0);
			glVertex3f(1.5,0.5,3.0);
			glVertex3f(0.5,1.5,3.0);
			glVertex3f(-0.5,1.5,3.0);
			glVertex3f(-1.5,0.0,3.0);
		glEnd();
		
		glBegin(GL_QUAD_STRIP);//lados
			glNormal3f( 0.0, 0.0, 1.0);		
			glVertex3f(-1.5,-0.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(-1.5,-0.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(-0.5,-1.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(-0.5,-1.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(0.5,-1.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(0.5,-1.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(1.5,-0.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(1.5,-0.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(1.5,0.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(1.5,0.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(0.5,1.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(0.5,1.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(-0.5,1.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(-0.5,1.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(-1.5,0.0,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(-1.5,0.5,0.5);
			glNormal3f( 0.0, 0.0, 1.0);	
			glVertex3f(-1.5,-0.5,3.0);
			glNormal3f( 0.0, 0.0, -1.0);	
			glVertex3f(-1.5,-0.5,0.5);
		glEnd();
		
		//Olhos 

		GLfloat matEyes[] = {0.0, 0.0, 0.0};
		glMaterialfv( GL_FRONT, GL_DIFFUSE, matEyes);
		glBegin(GL_TRIANGLES);
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(-1.0,-1.51,2.0);
			glVertex3f(-0.3,-1.51,2.0);
			glVertex3f(-1.0,-1.51,3.0);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(0.3,-1.51,2.0);
			glVertex3f(1.0,-1.51,2.0);
			glVertex3f(1.0,-1.51,3.0);
		glEnd();
	glPopMatrix();
}
void Blinky::kill(){
	jail_time = 400;
	jail = true;
	xpoz = PINKY_START_X;
	ypoz = PINKY_START_Y;
	state = GHOST_STATE_NORMAL;
	move_state = STATE_RIGHT;
}
float Blinky::getXPoz(){return xpoz;}
float Blinky::getYPoz(){return ypoz;}
void Blinky::move(int** matrix2D, int pacman_x, int pacman_y){
	float x = pacman_x - xpoz;
	float y = pacman_y - ypoz;
	angle = (atan2(y,x) * 180 / 3.1415926);
	if(jail)
		moveJail(matrix2D);
	else
		moveChase(matrix2D,pacman_x,pacman_y);
}
void Blinky::moveJail(int** matrix2D){
	if (jail_time == 0 && jail){
		if (xpoz == BLINKY_START_X){
			if(ypoz >= BLINKY_START_Y){
				jail = false;
				jail_time = 0;
			}
			else{
				ypoz += ACT_RATE;
			}
		}
		else if(xpoz < BLINKY_START_X){
			xpoz += ACT_RATE;
		}
		else if(xpoz > BLINKY_START_X){
			xpoz -= ACT_RATE;
		}
		else{
			xpoz = BLINKY_START_X;
		}
	}
}
void Blinky::moveChase(int** matrix2D, int pacman_x, int pacman_y){
	float x = pacman_x - xpoz;
	float y = pacman_y - ypoz;
	int c = (int)floor(xpoz);
	int l = (int)floor(ypoz);
	float test,test2;
	bool turn_up = false, turn_down = false, turn_left = false, turn_right = false;
	int random = rand() % 100;
	switch(move_state){
			case STATE_UP:
			case STATE_RIGHT:
				c = (int)floor(xpoz);
				l = (int)floor(ypoz);
				break;
			case STATE_DOWN:
			case STATE_LEFT:
				c = (int)floor(xpoz+0.5);
				l = (int)floor(ypoz+0.5);
				break;
	}
	if( ((0.001>=modf(xpoz,&test)) && (0.001>=modf(ypoz,&test2))) 
		|| ((0.999<=modf(xpoz,&test)) && (0.999<=modf(ypoz,&test2))) ){
		switch(move_state){
			case STATE_UP:
				turn_left = (matrix2D[l][c-1] != 0);
				turn_right = (matrix2D[l][c+1] != 0);
				if(turn_left && turn_right){
					if(random < 75){
						if( x <= 0){
							move_state = STATE_LEFT;
							moveLeft(matrix2D);
						}
						else{
							move_state = STATE_RIGHT;
							moveRight(matrix2D);
						}
					}
					else{
						if( x > 0){
							move_state = STATE_LEFT;
							moveLeft(matrix2D);
						}
						else{
							move_state = STATE_RIGHT;
							moveRight(matrix2D);
						}
					}
				}
				else if(turn_left){
					move_state = STATE_LEFT;
					moveLeft(matrix2D);
				}
				else if(turn_right){
					move_state = STATE_RIGHT;
					moveRight(matrix2D);
				}
				else{
					if(move_state == STATE_UP && matrix2D[l+1][c] != 0)
						moveUp(matrix2D);
					else if(matrix2D[l-1][c] != 0)
						moveDown(matrix2D);
				}
				break;
			case STATE_DOWN:
				turn_left = (matrix2D[l][c-1] != 0);
				turn_right = (matrix2D[l][c+1] != 0);
				if(turn_left && turn_right){
					if(random < 75){
						if( x <= 0){
							move_state = STATE_LEFT;
							moveLeft(matrix2D);
						}
						else{
							move_state = STATE_RIGHT;
							moveRight(matrix2D);
						}
					}
					else{
						if( x > 0){
							move_state = STATE_LEFT;
							moveLeft(matrix2D);
						}
						else{
							move_state = STATE_RIGHT;
							moveRight(matrix2D);
						}
					}
				}
				else if(turn_left){
					move_state = STATE_LEFT;
					moveLeft(matrix2D);
				}
				else if(turn_right){
					move_state = STATE_RIGHT;
					moveRight(matrix2D);
				}
				else{
					if(move_state == STATE_UP && matrix2D[l+1][c] != 0)
						moveUp(matrix2D);
					else if(matrix2D[l-1][c] != 0)
						moveDown(matrix2D);
				}
				break;
			case STATE_RIGHT:
				turn_up = (matrix2D[l+1][c] != 0);
				turn_down = (matrix2D[l-1][c] != 0);
				if(turn_up && turn_down){
					if(random < 75){
						if( y <= 0){
							move_state = STATE_DOWN;
							moveDown(matrix2D);
						}
						else{
							move_state = STATE_UP;
							moveUp(matrix2D);
						}
					}
					else{
						if( y > 0){
							move_state = STATE_DOWN;
							moveDown(matrix2D);
						}
						else{
							move_state = STATE_UP;
							moveUp(matrix2D);
						}
					}
				}
				else if(turn_down){
					move_state = STATE_DOWN;
					moveDown(matrix2D);
				}
				else if(turn_up){
					move_state = STATE_UP;
					moveUp(matrix2D);
				}
				else{
					if(move_state == STATE_LEFT && matrix2D[l][c-1] != 0)
						moveLeft(matrix2D);
					else if(matrix2D[l][c+1] != 0)
						moveRight(matrix2D);
				}
				break;
			case STATE_LEFT:
				turn_up = (matrix2D[l+1][c] != 0);
				turn_down = (matrix2D[l-1][c] != 0);
				if(turn_up && turn_down){
					if(random < 75){
						if( y <= 0){
							move_state = STATE_DOWN;
							moveDown(matrix2D);
						}
						else{
							move_state = STATE_UP;
							moveUp(matrix2D);
						}
					}
					else{
						if( y > 0){
							move_state = STATE_DOWN;
							moveDown(matrix2D);
						}
						else{
							move_state = STATE_UP;
							moveUp(matrix2D);
						}
					}
				}
				else if(turn_down){
					move_state = STATE_DOWN;
					moveDown(matrix2D);
				}
				else if(turn_up){
					move_state = STATE_UP;
					moveUp(matrix2D);
				}
				else{
					if(move_state == STATE_LEFT && matrix2D[l][c-1] != 0)
						moveLeft(matrix2D);
					else if(matrix2D[l][c+1] != 0)
						moveRight(matrix2D);
				}
				break;
			default:
				break;
		}
		}else{
			switch(move_state){
				case STATE_UP:
					if(matrix2D[l+1][c]!=0)
						moveUp(matrix2D);
					break;
				case STATE_DOWN:
					if(matrix2D[l-1][c]!=0)
						moveDown(matrix2D);
					break;
				case STATE_RIGHT:
					if(matrix2D[l][c+1]!=0)
						moveRight(matrix2D);
					break;
				case STATE_LEFT:
					if(matrix2D[l][c-1]!=0)
						moveLeft(matrix2D);
					break;
				default:
					break;
			}
		}
}
void Blinky::moveLeft(int** matrix2D){
	xpoz = xpoz-ACT_RATE;
}

void Blinky::moveRight(int** matrix2D){
	xpoz = xpoz+ACT_RATE;
}

void Blinky::moveUp(int** matrix2D){
	ypoz = ypoz+ACT_RATE;
}

void Blinky::moveDown(int** matrix2D){
	ypoz = ypoz-ACT_RATE;
}
void Blinky::timer(){
	if(state > 0)
		state -= 1;
	if(jail_time > 0)
		jail_time -= 1;
}