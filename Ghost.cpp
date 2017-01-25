#include "Ghost.h"
#include "Definitions.h"
#include <math.h>

using namespace game;

Ghost::Ghost(){}
Ghost::~Ghost(){}

int* Ghost::getState(){return &state;}
void Ghost::load(){}
float Ghost::getYPoz(){return xpoz;}
float Ghost::getXPoz(){return ypoz;}
void Ghost::move(int**, int, int){}
void Ghost::moveLeft(int**){}
void Ghost::moveRight(int**){}
void Ghost::moveUp(int**){}
void Ghost::moveDown(int**){}
void Ghost::moveChase(int**, int, int){}
void Ghost::moveJail(int**){}
void Ghost::timer(){}
void Ghost::kill(){}
