#include "Game.h"

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

	Game::DrawUI();
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
			Enemy &e = mEnemies.at(spriteOrder.at(i));
			e.setCameraX(INT_MAX);
			curLocation = e.getPosition();

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
					if (abs(getWidth() / 2 - stripe) < e.getCameraX())
						e.setCameraX(abs(getWidth() / 2 - stripe));
					for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
					{
						// Update visibility
						bool isVisible = e.isVisible();
						e.setVisibility(true);

						int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
						int texY = ((d * texHeight) / spriteHeight) / 256;
						Uint32 color = mTextures[e.getTexture()][texWidth * texY + texX]; //get current color from the texture
						if((color & 0xFF000000) != 0) mBuffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
					}
				}
				else
				{
					bool isVisible = e.isVisible();
					e.setVisibility(false);
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

void Game::DrawUI()
{
	Gun &gun = mPlayer.getCurrentGun();
	int uiYOffset = (screenHeight * 3) / 4;
	int gunYOffset = gun.getScreenPos().x, gunXOffset = gun.getScreenPos().y;
	double skipX = screenWidth / 800;
	double skipY = (screenHeight - uiYOffset) / 150;

	for(int x = gunXOffset; x < gunXOffset + gunTexWidth; x++)
	{
		for(int y = gunYOffset; y < gunYOffset + gunTexHeight; y++)
		{
			Uint32 color = mGuns[gun.getCurrentTexture()][gunTexWidth * (y - gunYOffset) + (x - gunXOffset)];
			if (color & 0xFF000000)
				mBuffer[y][x] = color;
		}
	}
	for(int x = 0; x < 800; x++)
	{
		for(int y = 0; y < 150; y++)
		{
			for (double i = x * skipX; i < screenWidth && i < x * skipX + skipX; i++)
			{
				for (double j = y * skipY; j < screenHeight && j < y * skipY + skipY; j++)
				{
					mBuffer[int(j) + uiYOffset][int(i)] = mUI[800 * (y) + x];
				}
			}
			//mBuffer[y][x] = 0;
		}
	}
}
