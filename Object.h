#ifndef OBJECT_H
#define OBJECT_H

#if defined(__APPLE__) || defined(MACOSX) 
 #include <GLUT/glut.h> 
#else 
 #include <GL/glut.h> 
#endif


namespace game {
	class MyApp;
	class Object{
		public:
			Object();
			virtual ~Object();
			void drawSphere(float, float, float,float);
			void drawWall(float, float, float,float, float, float);
	};
}

#endif