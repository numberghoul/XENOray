#include "Game.h"
#include "../level.h"

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
	int worldMap[mapWidth][mapHeight];

	for(int i = 0; i < mapWidth; i++)
	{
		for(int j = 0; j < mapHeight; j++)
		{
			worldMap[i][j] = levels[0][i][j];
		}
	}

	LoadTextures();

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	float deltaMouse = 0.0f;

	while(!done())
	{
		int oldmx, oldmy;
		SDL_GetMouseState(&oldmx, &oldmy);

		RenderWalls(worldMap);

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

void Game::LoadTextures()
{
	int success = 0;

	for(int i = 0; i < numTextures; i++) mTextures[i].resize(texWidth * texHeight);

	unsigned long tw, th;
    success = (loadImage(mTextures[0], tw, th, "textures/Ship/ceiling.png") == 0) ? success : 1;
    success = (loadImage(mTextures[1], tw, th, "textures/Ship/wall.png") == 0) ? success : 1;
    success = (loadImage(mTextures[2], tw, th, "textures/Ship/wallBlood.png") == 0) ? success : 1;
    success = (loadImage(mTextures[3], tw, th, "textures/Ship/wallWindow.png") == 0) ? success : 1;
    success = (loadImage(mTextures[4], tw, th, "textures/Ship/grate.png") == 0) ? success : 1;
    success = (loadImage(mTextures[5], tw, th, "textures/Cave/normalCaveWall.png") == 0) ? success : 1;
    success = (loadImage(mTextures[6], tw, th, "textures/Cave/normalCaveWallShroom.png") == 0) ? success : 1;
    success = (loadImage(mTextures[7], tw, th, "textures/Cave/normalCaveWallShroom2.png") == 0) ? success : 1;

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;
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

void Game::RenderWalls(int worldMap[][mapHeight])
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
			Uint32 color = mTextures[texNum][texHeight * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1) color = (color >> 1) & 8355711;
			mBuffer[y][x] = color;
		}
	}
	
	drawBuffer(mBuffer[0]);
	for(int x = 0; x < getWidth(); x++) for(int y = 0; y < getHeight(); y++) mBuffer[y][x] = 0; //clear the buffer instead of cls()
	redraw();
}
