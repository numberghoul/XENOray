//Shoutout to WL_DEF.H
#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "HelperClasses/Vector2.h"
#include "quickcg.h"

using namespace QuickCG;

#define screenWidth 800
#define screenHeight 600

#define texWidth 64
#define texHeight 64

#define mapWidth 30
#define mapHeight 30

#define numTextures 26

typedef struct mapTile
{
	int floor;
	int object;
	int ceiling;
}mapTile;

enum Textures
{
	ShipWallRaised, ShipWallStraight, ShipWallBloodRaised, ShipWallBloodStraight, ShipWallBloodStraight2,
	ShipWallCircuit, ShipWallPort, ShipWallWindowLeft, ShipWallWindowRight, ShipWallWindow, ShipGrate,
	ShipGrateBottomLeft, ShipGrateBottomRight, ShipGrateTopLeft, ShipGrateTopRight, ShipRoomFloor, ShipRoomFloorBlood2,
	ShipRoomFloorBlood, ShipCeiling, ShipCeilingLatch,

	CaveCeiling, CaveWall, CaveWallMushroom, CaveWallMushroom2, CaveFloor, TestSprite
};

Vector2<int> Raycast(mapTile map[][mapHeight], Vector2<double> rayPos, Vector2<double> rayDir,	Vector2<double> &stepDir,
	int &hit, int &side);

void BAD();
