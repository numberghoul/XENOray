#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include "quickcg.h"
using namespace QuickCG;

/*
g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic -std=c++11
g++ *.cpp -lSDL -std=c++11
*/

//place the example code below here:

#define mapWidth 24
#define mapHeight 24

extern int worldMap;

extern double posX, posY;  //x and y start position
extern double dirX, dirY; //initial direction vector
extern double planeX, planeY; //the 2d raycaster version of camera plane

void RunGame();
