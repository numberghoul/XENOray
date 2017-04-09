#include "Game.h"

Game::Game(int width, int height)
{
	setWidth(width);
	setHeight(height);

	mPlayer.setPosition(1, 1);
	mPlayer.setDirection(-1, 0);
	mPlayer.setCameraPlane(0, 0.66);
}

void Game::RunGame()
{
	int worldMap[mapWidth][mapHeight]=
	{
		{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
		{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
		{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
		{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
		{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
		{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
		{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
		{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
		{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
		{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
		{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
		{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
		{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
		{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
		{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
		{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};

	Uint32 buffer[screenHeight][screenWidth];
	std::vector<Uint32> texture[8];
	for(int i = 0; i < 8; i++) texture[i].resize(texWidth * texHeight);

	//generate some textures
	for(int x = 0; x < texWidth; x++)
	{
		for(int y = 0; y < texHeight; y++)
		{
			int xorcolor = (x * 256 / texWidth) ^ (y * 256 / texHeight);
			//int xcolor = x * 256 / texWidth;
			int ycolor = y * 256 / texHeight;
			int xycolor = y * 128 / texHeight + x * 128 / texWidth;
			texture[0][texWidth * y + x] = 65536 * 254 * (x != y && x != texWidth - y); //flat red texture with black cross
			texture[1][texWidth * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			texture[2][texWidth * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			texture[3][texWidth * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			texture[4][texWidth * y + x] = 256 * xorcolor; //xor green
			texture[5][texWidth * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			texture[6][texWidth * y + x] = 65536 * ycolor; //red gradient
			texture[7][texWidth * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
		}
	}

	std::cout << "Textures loaded" << std::endl;

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	float deltaMouse = 0.0f;

	while(!done())
	{
		int oldmx, oldmy;
		SDL_GetMouseState(&oldmx, &oldmy);

		Render(worldMap, texture, buffer);
		drawBuffer(buffer[0]);
	    for(int x = 0; x < getWidth(); x++) for(int y = 0; y < getHeight(); y++) buffer[y][x] = 0; //clear the buffer instead of cls()
		redraw();

		//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		mFrameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / mFrameTime); //FPS counter

		readKeys();
		UpdateMovement(worldMap);
		UpdateRotation(deltaMouse);

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		deltaMouse = mx - oldmx;
		deltaMouse /= 1000.0f;

		SDL_WarpMouse(screenWidth/2, screenHeight/2);
		SDL_ShowCursor(0);
	}
}

void Game::UpdateMovement(int worldMap[][mapHeight])
{
	double moveSpeed = mFrameTime * 6.5; //the constant value is in squares/second
	double posX = mPlayer.getPosition().x, posY = mPlayer.getPosition().y;
	double dirX = mPlayer.getDirection().x, dirY = mPlayer.getDirection().y;
	double planeX = mPlayer.getCameraPlane().x, planeY = mPlayer.getCameraPlane().y;

	//Sprint
	if (keyDown(SDLK_RSHIFT) || keyDown(SDLK_LSHIFT))
	{
		moveSpeed *= 2;
	}

	//move forward if no wall in front of you
	if (keyDown(SDLK_w) || keyDown(SDLK_UP))
	{
		if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
		if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (keyDown(SDLK_s) || keyDown(SDLK_DOWN))
	{
		if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
	}
	//Strafe right
	if (keyDown(SDLK_d))
	{
		if(worldMap[int(posX + planeX * moveSpeed)][int(posY)] == false) posX += planeX * moveSpeed;
		if(worldMap[int(posX)][int(posY + planeY * moveSpeed)] == false) posY += planeY * moveSpeed;
	}
	//Strafe left
	if (keyDown(SDLK_a))
	{
		if(worldMap[int(posX - planeX * moveSpeed)][int(posY)] == false) posX -= planeX * moveSpeed;
		if(worldMap[int(posX)][int(posY - planeY * moveSpeed)] == false) posY -= planeY * moveSpeed;
	}

	mPlayer.setPosition(posX, posY);
}

void Game::UpdateRotation(float deltaMouse)
{
	//speed modifiers
	double rotSpeed = mFrameTime * 4.5; //the constant value is in radians/second
	double planeX = mPlayer.getCameraPlane().x, planeY = mPlayer.getCameraPlane().y;
	double dirX = mPlayer.getDirection().x, dirY = mPlayer.getDirection().y;

	//rotate to the right
	if (deltaMouse > 0 || keyDown(SDLK_RIGHT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (deltaMouse < 0 || keyDown(SDLK_LEFT))
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}

	mPlayer.setDirection(dirX, dirY);
	mPlayer.setCameraPlane(planeX, planeY);
}

void Game::Render(int worldMap[][mapHeight], std::vector<Uint32> texture[], Uint32 buffer[][screenWidth])
{
	for(int x = 0; x < getWidth(); x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / double(getWidth()) - 1; //x-coordinate in camera space

		Vector2<double> rayPos(mPlayer.getPosition().x, mPlayer.getPosition().y);
		Vector2<double> rayDir(mPlayer.getDirection().x + mPlayer.getCameraPlane().x * cameraX,
							   mPlayer.getDirection().y + mPlayer.getCameraPlane().y * cameraX);

		//which box of the map we're in
		Vector2<int> mapPos(int(rayPos.x), int(rayPos.y));

		//length of ray from current position to next x or y-side
		Vector2<double> sideDist;

		 //length of ray from one x or y-side to next x or y-side
		Vector2<double> deltaDist(sqrt(1 + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
								  sqrt(1 + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		Vector2<int> stepDir;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDir.x < 0)
		{
			stepDir.x = -1;
			sideDist.x = (rayPos.x - mapPos.x) * deltaDist.x;
		}
		else
		{
			stepDir.x = 1;
			sideDist.x = (mapPos.x + 1.0 - rayPos.x) * deltaDist.x;
		}
		if (rayDir.y < 0)
		{
			stepDir.y = -1;
			sideDist.y = (rayPos.y - mapPos.y) * deltaDist.y;
		}
		else
		{
			stepDir.y = 1;
			sideDist.y = (mapPos.y + 1.0 - rayPos.y) * deltaDist.y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				mapPos.x += stepDir.x;
				side = 0;
			}
			else
			{
				sideDist.y += deltaDist.y;
				mapPos.y += stepDir.y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapPos.x][mapPos.y] > 0) hit = 1;
		}
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

		/*
		//choose wall color
		ColorRGB color;
		switch(worldMap[mapPos.x][mapPos.y])
		{
			case 1:	color = RGB_Red;	break; //red
			case 2:	color = RGB_Green;	break; //green
			case 3:	color = RGB_Blue;	 break; //blue
			case 4:	color = RGB_White;	break; //white
			default: color = RGB_Yellow; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color);
		*/

		//texturing calculations
      int texNum = worldMap[mapPos.x][mapPos.y] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if (side == 0) wallX = rayPos.y + perpWallDist * rayDir.y;
      else           wallX = rayPos.x + perpWallDist * rayDir.x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = int(wallX * double(texWidth));
      if(side == 0 && rayDir.x > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDir.y < 0) texX = texWidth - texX - 1;

	  for(int y = drawStart; y<drawEnd; y++)
      {
        int d = y * 256 - getHeight() * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
        int texY = ((d * texHeight) / lineHeight) / 256;
        Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
	}
}