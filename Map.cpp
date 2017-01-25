#include <stdio.h>
#include <stdlib.h>
#include "Definitions.h"
#include "Map.h"


using namespace game;

Map::Map(){}

Map::~Map(){}

void game::Map::raw_texture_load(const char *filename, int width, int height, int day)
 {
     unsigned char *data;
     FILE *file;
 
     // open texture data
     file = fopen(filename, "rb");
     if (file == NULL) exit(1);
 
     // allocate buffer
     data = (unsigned char*) malloc(width * height * 4);
 
     // read texture data
     fread(data, width * height * 4, 1, file);
     fclose(file);
 
     // allocate a texture name
     glGenTextures(1, &texname);
 
     // select our current texture
     glBindTexture(GL_TEXTURE_2D, texname);
 
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     if (day == NIGHT)
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); /* não era necessário pois este comando é executado por omiss‹o */
	 else
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	 //free the bitmap
     free(data);
 
 }

void game::Map::init(int **matrix){
	Object *Piece = new Object();
	int x, y;
	//GLuint texture = raw_texture_load("Water.raw",100,100);
	/*GLfloat matBackGr[] = {FLOOR_COLOR_R, FLOOR_COLOR_G, FLOOR_COLOR_B};
	glMaterialfv( GL_FRONT, GL_DIFFUSE, matBackGr);
	GLfloat matBackGr_specular[] = { 0., 0., 0., 1.0 };
	glMaterialfv( GL_FRONT, GL_SPECULAR, matBackGr_specular);*/


     glEnable(GL_TEXTURE_2D);

     /* create a square on the XY
        note that OpenGL origin is at the lower left
        but texture origin is at upper left
        => it has to be mirrored
        (gasman knows why i have to mirror X as well) */
	 for (float z=0.0; z<29; z+=1.0) {
		for (float w=1.0; w<32; w+=1.0) {
			glPushMatrix();
			glTranslatef( z, w, -1);
			glBegin( GL_POLYGON);
				glNormal3f( 0., 0., 1.0);
				glTexCoord2d(0,0); glVertex3f( 0., 0., 1.);
				glTexCoord2d(1,0); glVertex3f( 1., 0., 1.);
				glTexCoord2d(1,1); glVertex3f( 1., 1., 1.);
				glTexCoord2d(0,1); glVertex3f( 0., 1., 1.);
			glEnd();
			glPopMatrix();
		}
	}

    glDisable(GL_TEXTURE_2D);
	
	GLfloat matWall[] = {WALL_COLOR_R,WALL_COLOR_G,WALL_COLOR_B};
	glMaterialfv( GL_FRONT, GL_DIFFUSE, matWall);

	GLfloat matWall_specular[] = { 0., 0., 0., 1.0 };
	glMaterialfv( GL_FRONT, GL_SPECULAR, matWall_specular);
	//Walls
	//1,2
	Piece->drawWall(14.5, 0.5, 0.5, 29, 1, 1);
	Piece->drawWall(14.5, 31.5, 0.5, 29, 1, 1);
	//3,4
	Piece->drawWall(0.5, 8.5, 0.5, 1, 15, 1);
	Piece->drawWall(28.5, 8.5, 0.5, 1, 15, 1);
	//5,6
	Piece->drawWall(0.5, 24.5, 0.5, 1, 13, 1);
	Piece->drawWall(28.5, 24.5, 0.5, 1, 13, 1);
	//7, 8
	Piece->drawWall(3.5, 14, 0.5, 5, 4, 1);
	Piece->drawWall(25.5, 14, 0.5, 5, 4, 1);
	//9,10
	Piece->drawWall(3.5, 20, 0.5, 5, 4, 1);
	Piece->drawWall(25.5, 20, 0.5, 5, 4, 1);
	//11,12
	Piece->drawWall(2, 6.5, 0.5, 2, 1, 1);
	Piece->drawWall(27, 6.5, 0.5, 2, 1, 1);
	//13,14
	Piece->drawWall(7.5, 3.5, 0.5, 9, 1, 1);
	Piece->drawWall(21.5, 3.5, 0.5, 9, 1, 1);
	//15,16
	Piece->drawWall(8.5, 5.5, 0.5, 1, 3, 1);
	Piece->drawWall(20.5, 5.5, 0.5, 1, 3, 1);
	//17,18
	Piece->drawWall(5.5, 7.5, 0.5, 1, 3, 1);
	Piece->drawWall(23.5, 7.5, 0.5, 1, 3, 1);
	//19,20
	Piece->drawWall(14.5, 6.5, 0.5, 7, 1, 1);
	Piece->drawWall(14.5, 4.5, 0.5, 1, 3, 1);
	//21,22
	Piece->drawWall(4.5 , 9.5, 0.5, 3, 1, 1);
	Piece->drawWall(24.5, 9.5, 0.5, 3, 1, 1);
	//23,24
	Piece->drawWall(10.0 , 9.5, 0.5, 4, 1, 1);
	Piece->drawWall(19.0, 9.5, 0.5, 4, 1, 1);
	//25,26
	Piece->drawWall(14.5 , 10.5, 0.5, 1, 3, 1);
	Piece->drawWall(14.5, 12.5, 0.5, 7, 1, 1);
	//27,28
	Piece->drawWall(8.5 , 14.0, 0.5, 1, 4, 1);
	Piece->drawWall(20.5, 14.0, 0.5, 1, 4, 1);
	//29,30
	Piece->drawWall(8.5 , 21.5, 0.5, 1, 7, 1);
	Piece->drawWall(20.5, 21.5, 0.5, 1, 7, 1);
	//31,32
	Piece->drawWall(10.5 , 21.5, 0.5, 3, 1, 1);
	Piece->drawWall(18.5, 21.5, 0.5, 3, 1, 1);
	//33,34
	Piece->drawWall(14.5 , 22.5, 0.5, 1, 3, 1);
	Piece->drawWall(14.5, 24.5, 0.5, 7, 1, 1);
	//35,36
	Piece->drawWall(4.5 , 24.5, 0.5, 3, 1, 1);
	Piece->drawWall(24.5, 24.5, 0.5, 3, 1, 1);
	//37,38
	Piece->drawWall(4.5 , 28.0, 0.5, 3, 2, 1);
	Piece->drawWall(24.5, 28.0, 0.5, 3, 2, 1);
	//39,40
	Piece->drawWall(10.0 , 28.0, 0.5, 4, 2, 1);
	Piece->drawWall(19.0, 28.0, 0.5, 4, 2, 1);
	//41
	Piece->drawWall(14.5, 29.0, 0.5, 1, 4, 1);
	
	//Special drawWalls -- Ghost Zone
	GLfloat matGhostZone[] = {GHOST_ZONE_COLOR_R,GHOST_ZONE_COLOR_G, GHOST_ZONE_COLOR_B};
	glMaterialfv( GL_FRONT, GL_DIFFUSE, matGhostZone);

	Piece->drawWall(11.125, 17, 0.5, 0.25, 4, 1);
	Piece->drawWall(17.875, 17, 0.5, 0.25, 4, 1);
	Piece->drawWall(14.5, 15.125, 0.5, 6.5, 0.25, 1);
	Piece->drawWall(12.25, 18.875, 0.5, 2.5, 0.25, 1);
	Piece->drawWall(16.75, 18.875, 0.5, 2.5, 0.25, 1);
	glColor3f(1.0, 1.0, 1.0 );
	Piece->drawWall(14.5, 18.850, 0.5, 2, 0.125, 1);

	//Sphere Points
	GLfloat matSphere_specular[] = { 1., 1., 1., 1.0 };
	glMaterialfv( GL_FRONT, GL_SPECULAR, matSphere_specular);
	GLfloat mat_shine = 500.0;
	glMaterialf (GL_FRONT, GL_SHININESS, mat_shine);

	for(x=0;x<33;x++){
		for(y=0;y<32;y++) {
			if(matrix[y][x]==1){
				GLfloat matSphere_difuse[] = {SPHERE_COLOR_R, SPHERE_COLOR_G, SPHERE_COLOR_B};
				glMaterialfv( GL_FRONT, GL_DIFFUSE, matSphere_difuse);
				Piece->drawSphere(x, y, 0.5, SCALE_SPHERE);
			}
			else if (matrix[y][x] == 2){
				GLfloat matSphere_i_difuse[] = { IMORTAL_SPHERE_COLOR_R, IMORTAL_SPHERE_COLOR_G, IMORTAL_SPHERE_COLOR_B};
				glMaterialfv( GL_FRONT, GL_DIFFUSE, matSphere_i_difuse);
				Piece->drawSphere(x, y, 0.5, SCALE_IMORTAL_SPHERE);
			}
		}
	}

	delete[] Piece;
}

int ** Map::LoadMatrix(){ 
	int ** matrix;
	int c,l;
	int i;

	matrix = new int*[LINES];
	for (int j = 0; j < LINES; ++j)
		matrix[j] = new int[COLUMNS];

	for(l=0;l<33;l++){
		for(c=0;c<32;c++)
			matrix[c][l]=0;
	}

					//////////////////////////////////////////////////////////////////////////////
					//  GUIDE:: Mode(0) - Wall													//
					//	    	Mode(1) - Spheres												//
					//		    Mode(2) - Imortal Spheres										//
					//          Mode(3) - Line Way												//
					//////////////////////////////////////////////////////////////////////////////

	//Line 1
	for(i=2;i <28;++i)
		matrix[2][i]=1;
	//Line 3
	matrix[3][2]=1;
	matrix[3][13]=1;
	matrix[3][16]=1;
	matrix[3][27]=1;
	//Line 4
	matrix[4][2]=1;
	matrix[4][13]=1;
	matrix[4][16]=1;
	matrix[4][27]=1;
	//Line 5
	for(i=2;i < 8;++i)
		matrix[5][i]=1;
	for(i=10;i < 14;++i)
		matrix[5][i]=1;
	for(i=16;i < 20;++i)
		matrix[5][i]=1;
	for(i=22;i < 28;++i)
		matrix[5][i]=1;
	//Line 6
	matrix[6][4]=1;
	matrix[6][7]=1;
	matrix[6][10]=1;
	matrix[6][19]=1;
	matrix[6][22]=1;
	matrix[6][25]=1;
	//Line 7
	matrix[7][4]=1;
	matrix[7][7]=1;
	matrix[7][10]=1;
	matrix[7][19]=1;
	matrix[7][22]=1;
	matrix[7][25]=1;
	//Line 8
	for(i=3;i < 5;++i)
		matrix[8][i]=1;
	for(i=7;i < 23;++i)
		matrix[8][i]=1;
	for(i=25;i < 27;++i)
		matrix[8][i]=1;
	//Line 9
	matrix[9][2]=1;
	matrix[9][7]=1;
	matrix[9][13]=1;
	matrix[9][16]=1;
	matrix[9][22]=1;
	matrix[9][27]=1;
	//Line 10
	matrix[10][2]=1;
	matrix[10][7]=1;
	matrix[10][13]=1;
	matrix[10][16]=1;
	matrix[10][22]=1;
	matrix[10][27]=1;
	//Line 11
	for(i=2;i < 14;++i)
		matrix[11][i]=1;
	for(i=16;i < 28;++i)
		matrix[11][i]=1;
	//Center
	for(i=12;i < 23;++i) {
		matrix[i][7]=1;
		matrix[i][22]=1;
	}
	//Line 23
	for(i=2;i < 8;++i)
		matrix[23][i]=1;
	for(i=10;i < 14;++i)
		matrix[23][i]=1;
	for(i=16;i < 20;++i)
		matrix[23][i]=1;
	for(i=22;i < 28;++i)
		matrix[23][i]=1;
	//Line 24
	matrix[24][2]=1;
	matrix[24][7]=1;
	matrix[24][10]=1;
	matrix[24][19]=1;
	matrix[24][22]=1;
	matrix[24][27]=1;
	//Line 25
	matrix[25][2]=1;
	matrix[25][7]=1;
	matrix[25][10]=1;
	matrix[25][19]=1;
	matrix[25][22]=1;
	matrix[25][27]=1;
	//Line 26
	for(i=2;i < 28;++i)
		matrix[26][i]=1;
	//Line 27
	matrix[27][2]=1;
	matrix[27][7]=1;
	matrix[27][13]=1;
	matrix[27][16]=1;
	matrix[27][22]=1;
	matrix[27][27]=1;
	//Line 28
	matrix[28][7]=1;
	matrix[28][13]=1;
	matrix[28][16]=1;
	matrix[28][22]=1;
	//Line 29
	matrix[29][2]=1;
	matrix[29][7]=1;
	matrix[29][13]=1;
	matrix[29][16]=1;
	matrix[29][22]=1;
	matrix[29][27]=1;
	//Line 30
	for(i=2;i < 14;++i)
		matrix[30][i]=1;
	for(i=16;i < 28;++i)
		matrix[30][i]=1;
	//Sphere of Immortality
	matrix[8][2]=2;
	matrix[8][27]=2;
	matrix[28][27]=2;
	matrix[28][2]=2;

	//Way
	//Line 17
	for(i=0;i < 7;++i)
		matrix[17][i]=3;
	for(i=23; i<30;++i)
		matrix[17][i]=3;
	matrix[17][8]=3;
	matrix[17][9]=3;
	matrix[17][10]=3;
	matrix[17][21]=3;
	matrix[17][20]=3;
	matrix[17][19]=3;

	//Line 14
	for(i=10; i<20;++i)
		matrix[14][i]=3;
	//Line 20
	for(i=10; i<20;++i)
		matrix[20][i]=3;

	//Line 21
		matrix[21][13]=3;
		matrix[21][16]=3;

	//Line 22
		matrix[22][13]=3;
		matrix[22][16]=3;

	//Column 10
	for(i=12; i<21;++i)
		matrix[i][10]=3;
	//Column 19
	for(i=12; i<21;++i)
		matrix[i][19]=3;

	return matrix;

}