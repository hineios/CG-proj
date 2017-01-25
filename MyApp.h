#ifndef MyApp_H
#define MyApp_H

#if defined(__APPLE__) || defined(MACOSX) 
 #include <GLUT/glut.h> 
#else 
 #include <GL/glut.h> 
#endif

#include "Pacman.h"
#include "Map.h"
#include "Pinky.h"
#include "Blinky.h"
#include "Inky.h"
#include "Clyde.h"
#include <sstream>

namespace game {

	class Map;
	class MyApp {
		private:
			static int camera; 
			static int **matrix2D;
			static float w, h;
			static Map *map;
			static Pacman *pacman;
			static Pinky *pinky;
			static Blinky *blinky;
			static Inky *inky;
			static Clyde *clyde;
			static char* comandos;
			static int day;
			static int floor;
			static int pacman_dead;

		public:
			MyApp(int , char**);
			virtual ~MyApp();
			static void myReshape(GLsizei, GLsizei);
			static void myTimer(int);
			static void myDisplay(void);
			static void myKeyboard(unsigned char, int, int);
			static void processSpecialKeys(int, int, int);
			static void animation();
			static void setCamera();
			static void iterParticulas(int);
	};
}
#endif