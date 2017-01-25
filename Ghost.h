#ifndef GHOST_H
#define GHOST_H


#if defined(__APPLE__) || defined(MACOSX) 
 #include <GLUT/glut.h> 
#else 
 #include <GL/glut.h> 
#endif
#include "Definitions.h"

namespace game {
	class MyApp;
	class Ghost {
		protected:
			float angle,xpoz,ypoz;
			int state;
			int move_state;
			int jail_time;
			bool jail;
		public:
			Ghost();
			virtual ~Ghost();
			virtual int* getState();
			virtual float getXPoz();
			virtual float getYPoz();
			virtual void move(int**, int, int);
			virtual void moveLeft(int**);
			virtual void moveRight(int**);
			virtual void moveUp(int**);
			virtual void moveDown(int**);
			virtual void moveChase(int**, int, int);
			virtual void moveJail(int**);
			virtual void load();
			virtual void timer();
			virtual void kill();
	};
}

#endif 


