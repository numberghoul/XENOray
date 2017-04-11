#include <string>
#include <vector>
#include <iostream>

#include "../Player/Player.h"
#include "../quickcg.h"
using namespace QuickCG;

#define screenWidth 400
#define screenHeight 300

#define texWidth 64
#define texHeight 64

#define mapWidth 30
#define mapHeight 30

#define numTextures 8

enum Textures
{
	ShipCeiling, ShipWall, ShipWallBlood, ShipWallWindow, ShipFloor,

	CaveWall, CaveWallMushroom, CaveWallMushroom2
};

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
	std::vector<Uint32> mTextures[numTextures];
	Uint32 mBuffer[screenHeight][screenWidth];

	void LoadTextures();
	void Render(int worldMap[][mapHeight]);

	void UpdateMovement(int worldMap[][mapHeight]);
	void UpdateRotation(float deltaMouse);
};
