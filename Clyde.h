#ifndef CLYDE_H
#define CLYDE_H


#if defined(__APPLE__) || defined(MACOSX) 
 #include <GLUT/glut.h> 
#else 
 #include <GL/glut.h> 
#endif

#include "Ghost.h"

namespace game {
	class MyApp;
	class Clyde:Ghost {
		
		public:
			Clyde();
			virtual ~Clyde();
			void load();
			float getXPoz();
			float getYPoz();
			void kill();
			void move(int**, int, int);
			void moveChase(int**, int, int);
			void moveJail(int**);
			void moveLeft(int**);
			void moveRight(int**);
			void moveUp(int**);
			void moveDown(int**);
			int* getState();
			void timer();
	};
}

#endif 