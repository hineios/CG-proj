#ifndef MAP_H
#define MAP_H

#include "Object.h"

#if defined(__APPLE__) || defined(MACOSX) 
 #include <GLUT/glut.h> 
#else 
 #include <GL/glut.h> 
#endif

namespace game {
	class MyApp;
	class Map{
		private:
		     GLuint texname;
		public:
			Map();
			virtual ~Map();
			virtual void init(int**);
			virtual int **LoadMatrix();
			virtual void raw_texture_load(const char *, int, int,int);
	};
}
#endif