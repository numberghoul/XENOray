#pragma once
#include "../E_Def.h"
#include "../Character/Player.h"
#include "../HelperClasses/List.h"

typedef struct sprite
{
	double x, y;
	int texture;
} Sprite;

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

	List<Character *> mEnemies;
	List<Sprite> mDoors,
			  	 mPickups;
	Sprite sprite[numSprites] =
	{
	  {5, 5, TestSprite}
	};

	//function used to sort the sprites
	void combSort(int* order, double* dist, int amount);

	void loadMap(std::string mapName);

	void LoadTextures();

	void Render();
	void CheckQuit();

	void DrawSprites();

	void UpdateMovement();
	void UpdateRotation(float deltaMouse);
};
