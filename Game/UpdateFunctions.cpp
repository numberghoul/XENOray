#include "Game.h"

std::default_random_engine gen;
std::uniform_int_distribution<int> dis(0,U32Size), dirDis(8,24);

void Game::UpdateMovement()
{
	double moveSpeed = mFrameTime * 4.5; //the constant value is in squares/second
	double posX = mPlayer.getPosition().x, posY = mPlayer.getPosition().y;
	double dirX = mPlayer.getDirection().x, dirY = mPlayer.getDirection().y;
	double pDirX = -dirY, pDirY = dirX;
	bool collides = false;
	Vector2<double> velocity;

	double newMapPosX, newMapPosY;

	//move forward if no wall in front of you
	if (keyDown(SDLK_w) || keyDown(SDLK_UP))
	{
		velocity.y += dirY;
		velocity.x += dirX;
	}
	//move backwards if no wall behind you
	if (keyDown(SDLK_s) || keyDown(SDLK_DOWN))
	{
		velocity.y -= dirY;
		velocity.x -= dirX;
	}
	//Strafe right
	if (keyDown(SDLK_d))
	{
		velocity.y -= pDirY;
		velocity.x -= pDirX;
	}
	//Strafe left
	if (keyDown(SDLK_a))
	{
		velocity.y += pDirY;
		velocity.x += pDirX;
	}

	if (velocity.x != 0 && velocity.y != 0)
	{
		velocity.normalize();

		velocity = moveSpeed * velocity;

		if(keyDown(SDLK_LSHIFT) || keyDown(SDLK_RSHIFT))
		{
			velocity = 1.75 * velocity;
		}

		newMapPosX = posX + velocity.x;
		newMapPosY = posY + velocity.y;

		int i = -1, j = -1;
		for (i = -1; i <= 1 && !collides; ++i)
			for (j = -1; j <= 1 && !collides; ++j)
			{
				Vector2<double> check(i, j);
				check.normalize();

				if(newMapPosX + check.x * 0.05 < mapWidth  && newMapPosX + check.x * 0.05 >= 0 &&
				   newMapPosY + check.y * 0.05 < mapHeight && newMapPosY + check.y * 0.05 >= 0 &&
				   mMap[int(newMapPosX + check.x * 0.05)][int(newMapPosY + check.y * 0.05)].object != false)
				   collides = true;
			}

		if(!collides)
		{
			mPlayer.Move(newMapPosX, newMapPosY);
		}
		else
		{
			velocity.normalize();
			double oldVelX = velocity.x;
			if (mMap[int(posX)][int(posY + velocity.y)].object == false)
				velocity.x = 0;
			if (mMap[int(posX + oldVelX)][int(posY)].object == false)
				velocity.y = 0;
			if (mMap[int(posX + velocity.x)][int(posY + velocity.y)].object == false)
				mPlayer.Move(posX + 0.1 * velocity.x, posY + 0.1 * velocity.y);
		}
	}
}

void Game::UpdateRotation(float deltaMouse)
{
	// Speed modifiers
	double rotSpeed = mFrameTime * 2 * (deltaMouse != 0 ? 2 : 1); //the constant value is in radians/second

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
	Gun &gun = mPlayer.getCurrentGun();

	gun.update();
	if (keyDown(SDLK_SPACE) && gun.canShoot())
	{
		mPlayer.Shoot();

		for (int i = 0; i < mEnemies.size(); ++i)
		{
			Enemy &e = mEnemies.at(i);
			if (e.isVisible() && e.getCameraX() == 0 && (e.getPosition() - mPlayer.getPosition()).getSqrMagnitude() < 50)
			{
				e.TakeDamage(1);
				if (e.isDead())
					mEnemies.deleteAt(i);
			}
		}
	}

	if (gun.isShooting())
		gun.animate();
}

void Game::CheckQuit()
{
	//failsafe
	mQuit = keyDown(SDLK_1);
}

//replaces CheckQuit because pause now quits too
void Game::CheckPause()
{
	mPause = keyPressed(SDLK_ESCAPE);

	if (mPause)
	{
		int mx, my;
		//std::cout << "pause" << std::endl;

		//YOU CAN OVERLOAD PARANTHESES
		Uint32 coolMod = gen();
		Uint32 coolMod2 = gen();
		int mod = gen();
		Uint32 colorOffset = dis(gen);
		//determines direction of lines
		Uint32 dir = dirDis(gen);
		Uint32 dir2 = dirDis(gen);
		
		//used for converting back and forth
		ColorRGB color;
		Uint32 colorI;

		//button objects
		Button resume(Vector2<double>(screenWidth/2, screenHeight/2 + 400), nullptr);

		//pause background
		//settled on fractal-like function that emulates DOS color depth sort of thing
		for (int i = 0; i < screenWidth; ++i)
		for (int j = 0; j < screenHeight; ++j)
		{
			//converts random num to color struct
			color = INTtoRGB((( i/dir * (coolMod % mod) + j/dir2 * (coolMod2 % mod)) + colorOffset) / 4);
			//black and white
			color.r = color.b;
			color.g = color.b;
			color.b = color.b;
			//converts back for printing to screen
			colorI = RGBtoINT(color);
			mBuffer[j][i] = colorI;
		}

		while (mPause)
		{
			//std::cout << "in loop" << std::endl;

			//used for button logic
			SDL_GetMouseState(&mx, &my);

			readKeys();
			
			//this is where buttons logic should go
			
			if (keyPressed(SDLK_ESCAPE))
			{ 
				//std::cout << "unpause" << std::endl;
				mPause = false;
			}

			drawBuffer(mBuffer[0]);
		
			redraw();
		}
	}
}
