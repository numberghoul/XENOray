#include <string>
#include <vector>
#include <iostream>

#include "../Player/Player.h"
#include "../quickcg.h"
using namespace QuickCG;

#define mapWidth 24
#define mapHeight 24

#define screenWidth 600
#define screenHeight 480

#define texWidth 64
#define texHeight 64

/*
g++ *.cpp Game/ *.cpp Player/ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic -std=c++11
g++ *.cpp Game/ *.cpp Player/ *.cpp -lSDL -std=c++11

You need to remove the spaces between Game/ and * when actually using the command
*/

class Game
{
public:
	Game(int width = screenWidth, int height = screenHeight);

	int getWidth() const { return mScreenWidth; }
	int getHeight() const { return mScreenHeight; }

	void setWidth(const int width) { mScreenWidth = width; }
	void setHeight(const int height) { mScreenHeight = height; }

	void RunGame();
private:
	Player mPlayer;
	double mFrameTime;
	int mScreenWidth, mScreenHeight;

	void Render(int worldMap[][mapHeight], std::vector<Uint32> texture[], Uint32 buffer [][screenWidth]);

	void UpdateMovement(int worldMap[][mapHeight]);
	void UpdateRotation(float deltaMouse);
};
