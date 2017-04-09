#include <string>
#include <vector>
#include <iostream>

#include "../Player/Player.h"
#include "../quickcg.h"
using namespace QuickCG;

#define screenWidth 600
#define screenHeight 480

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

#define numSprites 1

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
	//1D Zbuffer
	double mZBuffer[screenWidth];
	//arrays used to sort the sprites
	int spriteOrder[numSprites];
	double spriteDistance[numSprites];

	//function used to sort the sprites
	void combSort(int* order, double* dist, int amount);

	void LoadTextures();
	
	void DrawSprites();

	void RenderWalls(int worldMap[][mapHeight]);

	void UpdateMovement(int worldMap[][mapHeight]);
	void UpdateRotation(float deltaMouse);
};
