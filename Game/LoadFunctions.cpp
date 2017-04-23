#include "Game.h"

void Game::InitPlayer()
{
	// Player Class Members
	mPlayer.setArmor(0);
	mPlayer.setBattery(100);
	mPlayer.setCameraPlane(0, 0.66);

	// Character Class Members
	mPlayer.setHealth(100);
	mPlayer.setSpeed(1);

	// Object Class Members
	mPlayer.setPosition(26, 26);
	mPlayer.setDirection(-1, 0);

	// Inwit default gun
	mPlayer.AddGun((screenHeight * 3) / 4 - 300, (screenWidth/2) - 250/2, 2, 1000, GunTextures::Raid);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim1);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim2);
	mPlayer.getCurrentGun().addAnimationFrame(GunTextures::RaidAnim3);
	mPlayer.setShootSound(mSounds[Sounds::ShootSound]);

	std::cout << "Player Initialized" << std::endl;
}

void Game::LoadTextures()
{
	int success = 0;

	// Initialize Each Image Buffer
	for(int i = 0; i < numTextures; i++) mTextures[i].resize(texWidth * texHeight);
	for(int i = 0; i < numGunTextures; i++) mGuns[i].resize(gunTexWidth * gunTexHeight);
	mUI.resize(256*800);

	unsigned long tw, th;
	// Ship Textures
	// Ceiling Textures
    success |= loadImage(mTextures[Textures::ShipCeiling], tw, th, "Textures/Ship/ceiling.png");
	success |= loadImage(mTextures[Textures::ShipCeilingLatch], tw, th, "Textures/Ship/ceilingLatch.png");
	// Wall Textures
    success |= loadImage(mTextures[Textures::ShipWallRaised], tw, th, "Textures/Ship/humanShipWall.png");
    success |= loadImage(mTextures[Textures::ShipWallStraight], tw, th, "Textures/Ship/humanShipWall2.png");
    success |= loadImage(mTextures[Textures::ShipWallBloodRaised], tw, th, "Textures/Ship/humanShipWall3.png");
    success |= loadImage(mTextures[Textures::ShipWallBloodStraight], tw, th, "Textures/Ship/humanShipWallBlood.png");
    success |= loadImage(mTextures[Textures::ShipWallBloodStraight2], tw, th, "Textures/Ship/humanShipWallBlood2.png");
    success |= loadImage(mTextures[Textures::ShipWallCircuit], tw, th, "Textures/Ship/humanShipWallCircuit.png");
    success |= loadImage(mTextures[Textures::ShipWallPort], tw, th, "Textures/Ship/humanShipWallGateClosed.png");
    success |= loadImage(mTextures[Textures::ShipWallWindowLeft], tw, th, "Textures/Ship/humanShipWallSideLeft.png");
    success |= loadImage(mTextures[Textures::ShipWallWindowRight], tw, th, "Textures/Ship/humanShipWallSideRight.png");
    success |= loadImage(mTextures[Textures::ShipWallWindow], tw, th, "Textures/Ship/humanShipWallWindow.png");
	// Floor Textures
    success |= loadImage(mTextures[Textures::ShipRoomFloor], tw, th, "Textures/Ship/roomFloor.png");
    success |= loadImage(mTextures[Textures::ShipRoomFloorBlood], tw, th, "Textures/Ship/roomFloorBlood.png");
    success |= loadImage(mTextures[Textures::ShipRoomFloorBlood2], tw, th, "Textures/Ship/roomFloorBlood2.png");
    success |= loadImage(mTextures[Textures::ShipGrateBottomLeft], tw, th, "Textures/Ship/hallFloorBottomLeft.png");
    success |= loadImage(mTextures[Textures::ShipGrateBottomRight], tw, th, "Textures/Ship/hallFloorBottomRight.png");
    success |= loadImage(mTextures[Textures::ShipGrateTopLeft], tw, th, "Textures/Ship/hallFloorTopLeft.png");
    success |= loadImage(mTextures[Textures::ShipGrateTopRight], tw, th, "Textures/Ship/hallFloorTopRight.png");
    success |= loadImage(mTextures[Textures::ShipGrate], tw, th, "Textures/Ship/grate.png");

	// Cave Textures
	//Ceiling Textures
    success |= loadImage(mTextures[Textures::CaveCeiling], tw, th, "Textures/Cave/caveCeiling.png");
	// Wall Textures
    success |= loadImage(mTextures[Textures::CaveWall], tw, th, "Textures/Cave/normalCaveWall.png");
    success |= loadImage(mTextures[Textures::CaveWallMushroom], tw, th, "Textures/Cave/normalCaveWallShroom.png");
    success |= loadImage(mTextures[Textures::CaveWallMushroom2], tw, th, "Textures/Cave/normalCaveWallShroom2.png");
	// Floor Textures
    success |= loadImage(mTextures[Textures::CaveFloor], tw, th, "Textures/Cave/alienCaveFloor.png");

	// Sprites
	success |= loadImage(mTextures[Textures::TestSprite], tw, th, "Textures/Sprites/27846.png");

	// Menu
	success |= loadImage(mTextures[Textures::GameLogo], tw, th, "Textures/gamelogo.png");

	//UIStuff
	success |= loadImage(mUI, tw, th, "Textures/UI/ofallonui.png");

	//Gun
	success |= loadImage(mGuns[GunTextures::Raid], tw, th, "Textures/UI/raid.png");
	success |= loadImage(mGuns[GunTextures::RaidAnim1], tw, th, "Textures/UI/raidboom1.png");
	success |= loadImage(mGuns[GunTextures::RaidAnim2], tw, th, "Textures/UI/raidboom2.png");
	success |= loadImage(mGuns[GunTextures::RaidAnim3], tw, th, "Textures/UI/raidboom3.png");

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;
}

void Game::LoadSounds()
{
	bool success = true;

	mSounds.resize(numSounds);

	mSounds[Sounds::DamageSound] = Mix_LoadWAV("sound/urgh.wav");
	mSounds[Sounds::WillhelmScream] = Mix_LoadWAV("sound/willhelm.wav");
	mSounds[Sounds::ShootSound] = Mix_LoadWAV("sound/rap.wav");

	for (int i = 0; i < numSounds; i++)
		success &= (mSounds[i] != nullptr);

	if (success)
		std::cout << "Sound Chunks Loaded" << std::endl;
	else
		BAD();

 	//MUSIC
 	mSongs.resize(numSongs);
 
 	mSongs[Songs::AndySong] = Mix_LoadMUS("Music/Andy.wav");
 	std::cout << SDL_GetError();
 
 	for (int i = 0; i < numSongs; i++)
 		success &= (mSongs[i] != nullptr);
 
 	if (success)
 		std::cout << "Music Loaded" << std::endl;
 	else
 		BAD();
}

void Game::LoadEnemies(std::string mapName)
{
	Enemy e(5, 20, 0, 4.0, 4.0, Textures::TestSprite);
	e.setDamageSound(mSounds[Sounds::DamageSound]);
	e.setDeathSound(mSounds[Sounds::WillhelmScream]);
	mEnemies.insertAtFront(e);

	e.setPosition(22.5, 3);
	mEnemies.insertAtFront(e);
	std::cout << "Enemies Loaded" << std::endl;
}

void Game::LoadMap(std::string mapName)
{
	std::string filepath = "./Maps/" + mapName + ".txt";
	std::ifstream infile(filepath);

	for(int k = 0; k < 3; k++)
	{
		for(int i = 0; i < 30; i++)
		{
			for(int j = 0; j < 30; j++)
			{
				std::string line;
				std::getline(infile, line, ',');

				if (line == "")
				{
					std::cout << "Finished" << std::endl;
					continue;
				}

				switch(k)
				{
					case 0:
						mMap[i][j].floor = std::stoi(line);
						break;
					case 1:
						mMap[i][j].object = std::stoi(line);
						break;
					case 2:
						mMap[i][j].ceiling = std::stoi(line);
						break;
				}
			}
		}
	}

	std::cout << "Map Loaded" << std::endl;
}