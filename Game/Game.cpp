#include "Game.h"

Game::Game(int width, int height)
{
	setWidth(width);
	setHeight(height);

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

	// Audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		BAD();
    
	mQuit = false;
}

void Game::RunGame(std::string mapName)
{
	LoadMap(mapName);
	LoadEnemies(mapName);
	LoadTextures();

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	float deltaMouse = 0.0f;

	while(!mQuit)
	{
		int oldmx, oldmy;
		SDL_GetMouseState(&oldmx, &oldmy);

		Render();

		//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		mFrameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / mFrameTime); //FPS counter

		readKeys();
		UpdateRotation(deltaMouse);
		UpdateMovement();
		CheckShoot();
		CheckQuit();

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		deltaMouse = mx - oldmx;
		deltaMouse /= 1000.0f;

		SDL_WarpMouse(screenWidth/2, screenHeight/2);
		SDL_ShowCursor(0);
	}
}

void Game::CheckQuit()
{
	mQuit = keyDown(SDLK_ESCAPE);
}

void Game::LoadTextures()
{
	int success = 0;

	for(int i = 0; i < numTextures; i++) mTextures[i].resize(texWidth * texHeight);

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

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;
}

void Game::LoadEnemies(std::string mapName)
{
	Enemy e(3, 20, 0, 4.0, 4.0, Textures::TestSprite);
	mEnemies.insertAtFront(e);
	mEnemies.at(0).loadDeathSound("sound/urgh.wav");

	e.setPosition(22.5, 3);
	//mEnemies.insertAtFront(e);
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
					continue;}

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
}

void Game::UpdateMovement()
{
	double moveSpeed = mFrameTime * 4.5; //the constant value is in squares/second
	double posX = mPlayer.getPosition().x, posY = mPlayer.getPosition().y;
	double dirX = mPlayer.getDirection().x, dirY = mPlayer.getDirection().y;
	double planeX = mPlayer.getCameraPlane().x, planeY = mPlayer.getCameraPlane().y;

	int newMapPosX, newMapPosY;

	//Sprint
	if (keyDown(SDLK_RSHIFT) || keyDown(SDLK_LSHIFT))
	{
		moveSpeed *= 1.75;
	}

	//move forward if no wall in front of you
	if (keyDown(SDLK_w) || keyDown(SDLK_UP))
	{
		newMapPosX = int(posX + dirX * moveSpeed);
		newMapPosY = int(posY + dirY * moveSpeed);

		if(newMapPosX < mapWidth && newMapPosX >= 0 && mMap[newMapPosX][int(posY)].object == false) posX += dirX * moveSpeed;
		if(newMapPosY < mapHeight && newMapPosY >= 0 && mMap[int(posX)][newMapPosY].object == false) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keyDown(SDLK_s) || keyDown(SDLK_DOWN))
	{
		newMapPosX = int(posX - dirX * moveSpeed);
		newMapPosY = int(posY - dirY * moveSpeed);

		if(newMapPosX < mapWidth && newMapPosX >= 0 && mMap[newMapPosX][int(posY)].object == false) posX -= dirX * moveSpeed;
		if(newMapPosY < mapHeight && newMapPosY >= 0 && mMap[int(posX)][newMapPosY].object == false) posY -= dirY * moveSpeed;
	}
	//Strafe right
	if (keyDown(SDLK_d))
	{
		newMapPosX = int(posX + planeX * moveSpeed);
		newMapPosY = int(posY + planeY * moveSpeed);

		if(newMapPosX < mapWidth && newMapPosX >= 0 && mMap[newMapPosX][int(posY)].object == false) posX += planeX * moveSpeed;
		if(newMapPosY < mapHeight && newMapPosY >= 0 && mMap[int(posX)][newMapPosY].object == false) posY += planeY * moveSpeed;
	}
	//Strafe left
	if (keyDown(SDLK_a))
	{
		newMapPosX = int(posX - planeX * moveSpeed);
		newMapPosY = int(posY - planeY * moveSpeed);

		if(newMapPosX < mapWidth && newMapPosX >= 0 && mMap[newMapPosX][int(posY)].object == false) posX -= planeX * moveSpeed;
		if(newMapPosY < mapHeight && newMapPosY >= 0 && mMap[int(posX)][newMapPosY].object == false) posY -= planeY * moveSpeed;
	}

	mPlayer.Move(posX, posY);

	//std::cout << posX << " " << posY << std::endl;
}

void Game::UpdateRotation(float deltaMouse)
{
	//speed modifiers
	double rotSpeed = mFrameTime * 4.5 * (deltaMouse != 0 ? 2 : 1); //the constant value is in radians/second

	if (deltaMouse > 0 || keyDown(SDLK_RIGHT))
		rotSpeed *= -1;
	else if (deltaMouse < 0 || keyDown(SDLK_LEFT))
		rotSpeed *= 1;
	else if (deltaMouse == 0)
		rotSpeed = 0;

	mPlayer.Rotate(rotSpeed);
}

void Game::CheckShoot()
{
	double cameraX;
	Vector2<double> stepDir, rayDir,
					rayPos(mPlayer.getPosition().x, mPlayer.getPosition().y);
	Vector2<int> hitPos;
	int hit, side;

	if (keyDown(SDLK_SPACE))
	{
		for (int i = 0; i < mEnemies.size() && mEnemies.at(i).isVisible(); ++i)
		{
			Enemy &e = mEnemies.at(i);
			bool isHit = false;
			for (int x = getWidth() - 80; x <= getWidth() + 80 && !isHit; x++)
			{
				cameraX = 2 * x / double(getWidth()) - 1;
				rayDir.setX(mPlayer.getDirection().x + mPlayer.getCameraPlane().x * cameraX);
				rayDir.setY(mPlayer.getDirection().y + mPlayer.getCameraPlane().y * cameraX);

				mPlayer.Shoot();
				hitPos = Raycast(mMap, rayPos, rayDir, stepDir, hit, side);

				double dist =  SqrDistFromPointToRay(rayPos, hitPos, e.getPosition());

				if (dist <= 1.5)
				{
					//std::cout << "HIT" << std::endl;
					isHit = true;
					e.TakeDamage(1);
					if (e.isDead())
						mEnemies.deleteAt(i);
				}
			}
		}
	}
}

void Game::Render()
{
	Vector2<double> playerPos = mPlayer.getPosition(), cameraPlane = mPlayer.getCameraPlane(), playerDir = mPlayer.getDirection();

	for(int x = 0; x < getWidth(); x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / double(getWidth()) - 1; //x-coordinate in camera space

		Vector2<double> rayPos(playerPos.x, playerPos.y),
						rayDir(playerDir.x + cameraPlane.x * cameraX, playerDir.y + cameraPlane.y * cameraX);

		double perpWallDist;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		Vector2<double> stepDir; //what direction to step in x or y-direction (either +1 or -1)
		Vector2<int> mapPos = Raycast(mMap, rayPos, rayDir, stepDir, hit, side);

		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapPos.x - rayPos.x + (1 - stepDir.x) / 2) / rayDir.x;
		else		   perpWallDist = (mapPos.y - rayPos.y + (1 - stepDir.y) / 2) / rayDir.y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(getHeight() / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + getHeight() / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + getHeight() / 2;
		if(drawEnd >= getHeight())drawEnd = getHeight() - 1;

		//texturing calculations
		int texNum = mMap[mapPos.x][mapPos.y].object - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = rayPos.y + perpWallDist * rayDir.y;
		else           wallX = rayPos.x + perpWallDist * rayDir.x;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = int(wallX * double(texWidth));
		if(side == 0 && rayDir.x > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDir.y < 0) texX = texWidth - texX - 1;

		for(int y = drawStart; y < drawEnd; y++)
		{
			int d = y * 256 - getHeight() * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			int texY = ((d * texHeight) / lineHeight) / 256;
			Uint32 color = mTextures[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			mBuffer[y][x] = color;
		}

		//SET THE mZBuffer FOR THE SPRITE CASTING
		mZBuffer[x] = perpWallDist; //perpendicular distance is used

		// Here lies the floor/ceiling code... be wary those who dwell
		Vector2<double> floorPos; // Position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && rayDir.x > 0)
		{
			floorPos.x = mapPos.x;
			floorPos.y = mapPos.y + wallX;
		}
		else if(side == 0 && rayDir.x < 0)
		{
			floorPos.x = mapPos.x + 1.0;
			floorPos.y = mapPos.y + wallX;
		}
		else if(side == 1 && rayDir.y > 0)
		{
			floorPos.x = mapPos.x + wallX;
			floorPos.y = mapPos.y;
		}
		else
		{
			floorPos.x = mapPos.x + wallX;
			floorPos.y = mapPos.y + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = perpWallDist;
		distPlayer = 0.0;

		if (drawEnd < 0) drawEnd = getHeight(); //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(int y = drawEnd; y < getHeight(); y++)
		{
			currentDist = getHeight() / (2.0 * y - getHeight()); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorPos.x + (1.0 - weight) * playerPos.x;
			double currentFloorY = weight * floorPos.y + (1.0 - weight) * playerPos.y;

			int texNumCeiling = mMap[int(currentFloorY)][int(currentFloorY)].ceiling - 1,
				texNumFloor = mMap[int(currentFloorX)][int(currentFloorY)].floor - 1;

			Vector2<int> floorTexPos;
			floorTexPos.x = int(currentFloorX * texWidth) % texWidth;
			floorTexPos.y = int(currentFloorY * texHeight) % texHeight;

			if ((texNumCeiling >= numTextures || texNumCeiling < 0) || (texNumFloor >= numTextures || texNumFloor < 0))
				continue;

			//floor
			mBuffer[y][x] = (mTextures[texNumFloor][texWidth * floorTexPos.y + floorTexPos.x] >> 1) & 8355711;
			//ceiling (symmetrical!)
			mBuffer[getHeight() - y][x] = mTextures[texNumCeiling][texWidth * floorTexPos.y + floorTexPos.x];
		}
	}

	Game::DrawSprites();

	drawBuffer(mBuffer[0]);
	for(int x = 0; x < getWidth(); x++) for(int y = 0; y < getHeight(); y++) mBuffer[y][x] = 0; //clear the buffer instead of cls()
	redraw();
}

void Game::DrawSprites()
{
	Vector2<double> pos = mPlayer.getPosition(),
	 				dir = mPlayer.getDirection(),
					plane = mPlayer.getCameraPlane();

	Vector2<double> curLocation;

	std::vector<int>	spriteOrder;
	std::vector<double> spriteDistance;

	spriteOrder.resize(mEnemies.size());
	spriteDistance.resize(mEnemies.size());

	//SPRITE CASTING
	//sort sprites from far to close
	for (int i = 0; i < mEnemies.size(); ++i)
	{
		try
		{
			curLocation = mEnemies.at(i).getPosition();

			spriteOrder.at(i) = i;
			spriteDistance.at(i) = ((pos.x - curLocation.x) * (pos.x - curLocation.x) + (pos.y - curLocation.y) * (pos.y - curLocation.y)); //sqrt not taken, unneeded
		}
		catch (std::out_of_range &oore)
		{
			std::cout << oore.what() << std::endl << "EXCEPTION IN SPRITE CASTING" << std::endl;
			return;
		}
	}

	combSort(spriteOrder, spriteDistance, mEnemies.size());

    //after sorting the sprites, do the projection and draw them
	for (int i = 0; i < mEnemies.size(); i++)
	{
		try
		{
			curLocation = mEnemies.at(spriteOrder.at(i)).getPosition();

			//translate sprite position to relative to camera
			Vector2<double> spritePos = curLocation - pos;

			//transform sprite with the inverse camera matrix
			// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
			// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
			// [ planeY   dirY ]                                          [ -planeY  planeX ]

			double invDet = 1.0 / (plane.x * dir.y - dir.x * plane.y); //required for correct matrix multiplication

			//this is actually the depth inside the screen, that what Z is in 3D
			Vector2<double> transform(invDet * (dir.y * spritePos.x - dir.x * spritePos.y),
										invDet * (-plane.y * spritePos.x + plane.x * spritePos.y));

			int spriteScreenX = int((getWidth() / 2) * (1 + transform.x / transform.y));

			//calculate height of the sprite on screen
			int spriteHeight = abs(int(getHeight() / (transform.y))); //using "transformY" instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
			int drawStartY = -spriteHeight / 2 + getHeight() / 2;
			if(drawStartY < 0) drawStartY = 0;
			int drawEndY = spriteHeight / 2 + getHeight() / 2;
			if(drawEndY >= getHeight()) drawEndY = getHeight() - 1;

			//calculate width of the sprite
			int spriteWidth = abs( int (getHeight() / (transform.y)));
			int drawStartX = -spriteWidth / 2 + spriteScreenX;
			if(drawStartX < 0) drawStartX = 0;
			int drawEndX = spriteWidth / 2 + spriteScreenX;
			if(drawEndX >= getWidth()) drawEndX = getWidth() - 1;

			//loop through every vertical stripe of the sprite on screen
			for(int stripe = drawStartX; stripe < drawEndX; stripe++)
			{
				int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) mZBuffer, with perpendicular distance
				Vector2<double> pos = mPlayer.getPosition();
				Vector2<double> planeLeft = pos + mPlayer.getDirection() - mPlayer.getCameraPlane(),
								planeRight = pos + mPlayer.getDirection() + mPlayer.getCameraPlane();
				bool isOnScreen = ((sgn((planeLeft.x - pos.x) * (curLocation.y - pos.y) - (planeLeft.y - pos.y) * (curLocation.x - pos.x)) == -1 &&
								   sgn((planeRight.x - pos.x) * (curLocation.y - pos.y) - (planeRight.y - pos.y) * (curLocation.x - pos.x)) == 1));
				if(transform.y > 0 && isOnScreen && transform.y < mZBuffer[stripe])
				{
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
						bool isVisible = mEnemies.at(spriteOrder.at(i)).isVisible();
						mEnemies.at(spriteOrder.at(i)).setVisibility(true);
						int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
						int texY = ((d * texHeight) / spriteHeight) / 256;
						Uint32 color = mTextures[mEnemies.at(spriteOrder.at(i)).getTexture()][texWidth * texY + texX]; //get current color from the texture
						if((color & 0xFF000000) != 0) mBuffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color

						//if (isVisible != true)
						//	std::cout << "Enemy at index " << spriteOrder.at(i) << " is now visible" << std::endl;
					}
				}
				else
				{
					bool isVisible = mEnemies.at(spriteOrder.at(i)).isVisible();
					mEnemies.at(spriteOrder.at(i)).setVisibility(false);

					//if (isVisible != false)
					//	std::cout << "Enemy at index " << spriteOrder.at(i) << " is no longer visible" << std::endl;
				}
			}
		}
		catch (std::out_of_range &oore)
		{
			std::cout << oore.what() << std::endl << "EXCEPTION IN SPRITE PROJECTION" << std::endl;
		}
	}
}

void Game::combSort(std::vector<int> &order, std::vector<double> &dist, int amount)
{
	int gap = amount, temp = 0;
	double tempDist = 0;
	bool swapped = false;
	while(gap > 1 || swapped)
	{
		//shrink factor 1.3
		gap = (gap * 10) / 13;
		if(gap == 9 || gap == 10) gap = 11;
		if (gap < 1) gap = 1;

		swapped = false;
		for(int i = 0; i < amount - gap; i++)
		{
			int j = i + gap;
			if(dist[i] < dist[j])
			{
				//std::swap(dist[i], dist[j]);
				//std::swap(order[i], order[j]);
				tempDist = dist[i];
				dist[i] = dist[j];
				dist[j] = tempDist;

				temp = order[i];
				order[i] = order[j];
				order[j] = temp;

				swapped = true;
			}
		}
	}
}
