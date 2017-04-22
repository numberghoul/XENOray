//Shoutout to WL_DEF.H
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <exception>
#include <cmath>
#include <thread>
#include <SDL/SDL_mixer.h>
#include <climits>

#include "HelperClasses/Vector2.h"
#include "quickcg.h"

using namespace QuickCG;

#define GAMENAME "EPITOME"

#define screenWidth 800
#define screenHeight 600

#define texWidth 64
#define texHeight 64

#define mapWidth 30
#define mapHeight 30

#define numTextures 28
#define numSounds 2

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

	CaveCeiling, CaveWall, CaveWallMushroom, CaveWallMushroom2, CaveFloor, TestSprite,

	GameLogo, UI
};

enum Sounds
{
	DamageSound, WillhelmScream
};

Vector2<int> Raycast(mapTile map[][mapHeight], Vector2<double> rayPos, Vector2<double> rayDir,	Vector2<double> &stepDir,
	int &hit, int &side);
double SqrDistFromPointToRay(Vector2<double> rayPoint1, Vector2<int> rayPoint2, Vector2<double> point);

int sgn(double val);

// playSound wraps _playSound in a new thread
void playSound(Mix_Chunk *sound);

// Bound to its own thread so that the sleep function can be called without halting the program
void _playSound(Mix_Chunk *sound);

void BAD();
