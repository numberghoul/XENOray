#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "../Character/Player.h"
#include "../quickcg.h"
using namespace QuickCG;

#define screenWidth 800
#define screenHeight 600

#define texWidth 64
#define texHeight 64

#define mapWidth 30
#define mapHeight 30

#define numTextures 26

enum Textures
{
	ShipCeiling, ShipCeilingLatch, ShipWallRaised, ShipWallStraight, ShipWallBloodRaised, ShipWallBloodStraight, ShipWallBloodStraight2,
	ShipWallCircuit, ShipWallPort, ShipWallWindowLeft, ShipWallWindowRight, ShipWallWindow, ShipRoomFloor, ShipRoomFloorBlood,
	ShipRoomFloorBlood2, ShipGrateBottomLeft, ShipGrateBottomRight, ShipGrateTopLeft, ShipGrateTopRight, ShipGrate,

	CaveCeiling, CaveWall, CaveWallMushroom, CaveWallMushroom2, CaveFloor, TestSprite
};

typedef struct mapTile
{
	int floor;
	int object;
	int ceiling;
}mapTile;

struct Sprite
{
  double x;
  double y;
  int texture;
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

	void RunGame(std::string mapName);
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
	bool mQuit;

	mapTile mMap[mapWidth][mapHeight];

	Sprite sprite[numSprites] =
	{
	  {5, 5, TestSprite}
	};

	//function used to sort the sprites
	void combSort(int* order, double* dist, int amount);

	void loadMap(std::string mapName);

<<<<<<< HEAD
	void LoadTextures();

	void Render();
=======
	void Render(int worldMap[][mapHeight]);
	void CheckQuit();
>>>>>>> a8434dad32336f03a347f82a7a7d1e9f7bbf43cd

	void DrawSprites();

	void UpdateMovement();
	void UpdateRotation(float deltaMouse);
};
