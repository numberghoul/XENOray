#include "Game.h"

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
				if(newMapPosX + i * 0.1 < mapWidth  && newMapPosX + i * 0.1 >= 0 &&
				   newMapPosY + j * 0.1 < mapHeight && newMapPosY + j * 0.1 >= 0 &&
				   mMap[int(newMapPosX + i * 0.1)][int(newMapPosY + j * 0.1)].object != false)
				   collides = true;

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
			if (e.isVisible() && e.getCameraX() == 0)
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
	mQuit = keyDown(SDLK_ESCAPE);
}
