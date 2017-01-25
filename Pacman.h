#ifndef PACMAN_H
#define PACMAN_H

#include "Pinky.h"
#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h"



#if defined(__APPLE__) || defined(MACOSX) 
 #include <GLUT/glut.h> 
#else 
 #include <GL/glut.h> 
#endif


typedef struct {
	float	life;		// vida
	float	fade;		// fade
	float	r, g, b;    // color
	GLfloat x, y, z;    // posição
	GLfloat vx, vy, vz; // velocidade 
    GLfloat ax, ay, az; // aceleração
} Particle;

namespace game {
	class MyApp;
	class Pacman {
		protected:
			static float xpoz, ypoz;
			static int state, turn_state;
			static float score;
			static int lives;
			static int xnormal;
			static int ynormal;
			static bool dead;
		private:
			Particle particula[MAX_PARTICULAS];
		public:
			Pacman();
			virtual ~Pacman();
			float getXPoz();
			float getYPoz();
			int getState();
			void load();
			void move(int**, int*, int*, int*, int*);
			void moveLeft(int**);
			void moveRight(int**);
			void moveUp(int**);
			void moveDown(int**);
			void turnDown();
			void turnUp();
			void turnRight();
			void turnLeft();
			int getLives();
			float getScore();
			int getYNormal();
			int getXNormal();
			void initParticulas(int,int);
			void initParticulasAux();
			void setParticulas();
			void kaBoom();
			void kill();
			void revive();
			bool getDead();
	};
}

#endif