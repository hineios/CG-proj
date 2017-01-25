#include <iostream>
#include "MyApp.h"
#include "Map.h"
#include "Pacman.h"
#include "Definitions.h"

using namespace std;
using namespace game;

game::Map *game::MyApp::map = new Map();
game::Pacman *game::MyApp::pacman = new Pacman();
game::Pinky *game::MyApp::pinky = new Pinky();
game::Blinky *game::MyApp::blinky = new Blinky();
game::Inky *game::MyApp::inky = new Inky();
game::Clyde *game::MyApp::clyde = new Clyde();
int ** game::MyApp::matrix2D = map->LoadMatrix();
float game::MyApp::w = WINDOW_WIDTH;
float game::MyApp::h = WINDOW_HEIGHT;
int game::MyApp::camera = 1;
char* game::MyApp::comandos = "SCORE                                                LIVES";
int game::MyApp::day= DAY;
int game::MyApp::floor=0;
int game::MyApp::pacman_dead = 0;

game::MyApp::MyApp(int argc,char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (w, h);
	glutInitWindowPosition (-1, -1);
	glutCreateWindow("Pacman");

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutTimerFunc(0,myTimer,1);
	glutTimerFunc(33,iterParticulas,1);
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(processSpecialKeys);
	
	glutMainLoop();

}

game::MyApp::~MyApp() {}

void game::MyApp::myDisplay(void) {
	/*char * lives;
	int i = 0;
	while( i < pacman->getLives()){
		lives[i] = '@';
		i++;
	}
	lives[++i] = '\0';*/

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	setCamera();
	GLfloat ambientLight[4] = {0, 0, 0, 0};
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	
	//Day Light
	GLfloat direction[] = {0.0, -0.5, 1.0, 0.0 };
	GLfloat ambient[] = { .0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specular[] = { .8, .8, .8, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	
	//Night Light
	GLfloat Lt1dir[3]  = {pacman->getXNormal(), pacman->getYNormal(), -1};
	GLfloat Lt1cut[1]  = {45};
	GLfloat position[] = {pacman->getXPoz(), pacman->getYPoz(),2.3, 1};
	glLightfv(GL_LIGHT1, GL_POSITION, position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Lt1dir);
	glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF,    Lt1cut);
	
	if (day == DAY){
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);
	}
	else {
		pacman->initParticulasAux();
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
	}

	animation();
	//if(floor == 0){
	//	floor =1;
	map->raw_texture_load("Water3.raw",100,100, day);
//	}
//	else {
//		floor =0;
		//map->raw_texture_load("uno2.raw",100,100, day);
//	}
	
	map->init(matrix2D);
	pacman->load();
	pinky->load();
	blinky->load();
	inky->load();
	clyde->load();
	
	pacman->kaBoom();
	// mensagem no canto inferior - HUD
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) w, 0.0, (GLfloat) h);
	glMatrixMode( GL_MODELVIEW);
	glLoadIdentity();
	glColor3f( 1., 0.8, 0.);
	glRasterPos2i( 25, 10);
	for( int i=0; comandos[i] != '\0'; i++)
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, comandos[i]);
	glRasterPos2i( 392, 10);
	ostringstream buffer1;
	buffer1 << pacman->getLives();
	for (int j=0; buffer1.str()[j] != '\0'; j++)
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, buffer1.str()[j]);
	//glColor3f( 1.0, 0.8, 0.0);
	glRasterPos2i( 95, 10);
	ostringstream buffer;
	buffer << pacman->getScore();
	for (int k=0; buffer.str()[k] != '\0'; k++)
      glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, buffer.str()[k]);
    glutSwapBuffers();
}

void game::MyApp::myReshape(GLsizei width, GLsizei height) {
	 w = width;   h = height; 
	 glViewport( 0, 0, w, h);
}

void game::MyApp::myTimer(int x){
	glutTimerFunc(TIMER_INTERVAL,myTimer,x);
	blinky->timer();
	pinky->timer();
	inky->timer();
	clyde->timer();
	glutPostRedisplay();
}

void game::MyApp::myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 27: // ESC key
			exit(0);
			break;
		case 'w': //Andar para cima
		case 'W':
			pacman->turnUp();
			break;
		case 's': //Andar para baixo
		case 'S':
			pacman->turnDown();
			break;
		case 'a' : //Andar para a esquerda
		case 'A' :
			pacman->turnLeft();
			break;
		case 'd': //Andar para a direita
		case 'D':
			pacman->turnRight();
			break;
		case 'n': //night
		case 'N':
			if (day == NIGHT)
				day = DAY;
			else
				day = NIGHT;
			break;
		case '1'://Cameras
		case '2':
		case '3':
		case '4':
		case '5':{
			int cam = key - '0';
			if ( cam != camera ){
				camera = cam;
			}
			break;
		}
		default:
			break;
		case 'e':
		case 'E':
			pacman->initParticulas(pacman->getXPoz(), pacman->getYPoz());
			break;
	}

}

void game::MyApp::processSpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_UP:
			pacman->turnUp();
			break;
		case GLUT_KEY_DOWN:
			pacman->turnDown();
			break;
		case GLUT_KEY_LEFT :
			pacman->turnLeft();
			break;
		case GLUT_KEY_RIGHT:
			pacman->turnRight();
			break;
	}
}

void game::MyApp::animation(){
	if(!pacman->getDead()){
		float border_x_left = pacman->getXPoz() - 1.0;
		float border_x_right = pacman->getXPoz() + 1.0;;
		float border_y_down= pacman->getYPoz() - 1.0;
		float border_y_up = pacman->getYPoz() + 1.0;
		pacman_dead += 1;
		if((blinky->getXPoz()>= border_x_left) && (blinky->getXPoz()<= border_x_right) &&
			(blinky->getYPoz()>= border_y_down) && (blinky->getYPoz()<= border_y_up)){
				if( *(blinky->getState()) != GHOST_STATE_NORMAL){
					blinky->kill();
				}
				else{ 
					pacman->kill();
					pacman->initParticulas(pacman->getXPoz(), pacman->getYPoz());
				}
		}else if((pinky->getXPoz()>= border_x_left) && (pinky->getXPoz()<= border_x_right) &&
			(pinky->getYPoz()>= border_y_down) && (pinky->getYPoz()<= border_y_up)){
			if( *(pinky->getState()) != GHOST_STATE_NORMAL){
					pinky->kill();
				}
				else{ 
					pacman->kill();
					pacman->initParticulas(pacman->getXPoz(), pacman->getYPoz());
				}
		}
		else if((clyde->getXPoz()>= border_x_left) && (clyde->getXPoz()<= border_x_right) &&
			(clyde->getYPoz()>= border_y_down) && (clyde->getYPoz()<= border_y_up)){
			if( *(clyde->getState()) != GHOST_STATE_NORMAL){
					clyde->kill();
				}
				else{ 
					pacman->kill();
					pacman->initParticulas(pacman->getXPoz(), pacman->getYPoz());
				}
		}else if((inky->getXPoz()>= border_x_left) && (inky->getXPoz()<= border_x_right) &&
			(inky->getYPoz()>= border_y_down) && (inky->getYPoz()<= border_y_up)){
			if( *(inky->getState()) != GHOST_STATE_NORMAL){
					inky->kill();
				}
				else{ 
					pacman->kill();
					pacman->initParticulas(pacman->getXPoz(), pacman->getYPoz());
				}
		}else{
			pacman->move(matrix2D, pinky->getState(), blinky->getState(), inky->getState(), clyde->getState());
		}
	}
	else if(pacman_dead > 200){
		pacman_dead = 0;
		pacman->revive();
	}
	
	pinky->move(matrix2D, pacman->getXPoz(),pacman->getYPoz());
	blinky->move(matrix2D, pacman->getXPoz(),pacman->getYPoz());
	inky->move(matrix2D, pacman->getXPoz(),pacman->getYPoz());
	clyde->move(matrix2D, pacman->getXPoz(),pacman->getYPoz());
}

void game::MyApp::setCamera(){
	double f = ((float) w) / h;

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	switch(camera){
		default:
		case 1:
			if ( f >= 1. )
				glOrtho(-1.0f * f, 30.0f * f, -1.0f, 33.0f, -2.0f, 5.0f);
			else
 				glOrtho(-1.0f, 30.0f, -1.0f / f, 33.0f / f, -2.0f, 5.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			break;
		case 2:
			gluPerspective(45.0, f, 1,100);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(pacman->getXPoz(),pacman->getYPoz()-10,10,//eye
					  pacman->getXPoz(),pacman->getYPoz(),0.5,//point
					  0,0,1);//up
			break;
		case 3:
			gluPerspective(45.0, f, 1,100);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(14.5,-10,35,//eye
					  14.5,14,0.5,//point
					  0,0,1);//up
			break;
		case 4:
			glOrtho( pacman->getXPoz()-2.0, pacman->getXPoz()+2.0, pacman->getYPoz()-2.0, pacman->getYPoz()+2.0, -5.0f, 5.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			break;
		case 5:
			gluPerspective(45.0, f, 1,100);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			gluLookAt(pacman->getXPoz(),pacman->getYPoz()-10,3,//eye
					  pacman->getXPoz(),pacman->getYPoz(),0.5,//point
					  0,0,1);//up
			break;
	}
}

void game::MyApp::iterParticulas(int value){
	pacman->setParticulas();

	glutPostRedisplay();
	glutTimerFunc(20,iterParticulas,1);

}