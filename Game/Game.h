#include <string>
#include <vector>
#include <iostream>

#include "Render.h"

#define mapWidth 24
#define mapHeight 24

/*
g++ *.cpp Game/*.cpp Player/*.cpp -lSDL -O3 -W -Wall -ansi -pedantic -std=c++11
g++ *.cpp Game/*.cpp Player/*.cpp -lSDL -std=c++11
*/

class Game
{
public:
	Game(int width = 1280, int height = 720);

	int getWidth() const { return mScreenWidth; }
	int getHeight() const { return mScreenHeight; }

	void setWidth(const int width) { mScreenWidth = width; }
	void setHeight(const int height) { mScreenHeight = height; }

	void RunGame();
private:
	Player mPlayer;
	double mFrameTime;
	int mScreenWidth, mScreenHeight;

	void UpdateMovement(int worldMap[][mapHeight]);
	void UpdateRotation(float deltaMouse);
};
