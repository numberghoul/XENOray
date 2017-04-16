#include "Player.h"

Player::Player(double posX, double posY, double dirX, double dirY, double cameraX, double cameraY)
{
	setPosition(posX, posY);
	setDirection(dirX, dirY);
	setCameraPlane(cameraX, cameraY);
}

Player::Player(Vector2<double> pos, Vector2<double> dir, Vector2<double> camera)
{
	setPosition(pos.x, pos.y);
	setDirection(dir.x, dir.y);
	setCameraPlane(camera.x, camera.y);
}

Vector2<double> Player::getPosition() const { return mPosition; }
Vector2<double> Player::getDirection() const { return mDirection; }
Vector2<double> Player::getCameraPlane() const { return mCameraPlane; }

void Player::setPosition(const Vector2<double> pos) { setPosition(pos.x, pos.y); }
void Player::setPosition(const double posX, const double posY)
{
	mPosition.setX(posX);
	mPosition.setY(posY);
}

void Player::setDirection(const Vector2<double> dir) { setDirection(dir.x, dir.y); }
void Player::setDirection(const double dirX, const double dirY)
{
	mDirection.setX(dirX);
	mDirection.setY(dirY);
}

void Player::setCameraPlane(const Vector2<double> cam) { setCameraPlane(cam.x, cam.y); }
void Player::setCameraPlane(const double camX, const double camY)
{
	mCameraPlane.setX(camX);
	mCameraPlane.setY(camY);
}

void Player::TakeDamage(int damage)
{
	mHealth -= damage;
	if (mHealth <= 0)
	{
		mHealth = 0;
		Die();
	}
}

void Player::Move(double x, double y)
{
	mPosition.setX(x);
	mPosition.setY(y);
}

void Player::Rotate(double rotSpeed)
{
	double oldDirX = mDirection.x;
	mDirection.x = mDirection.x * cos(rotSpeed) - mDirection.y * sin(rotSpeed);
	mDirection.y = oldDirX * sin(rotSpeed) + mDirection.y * cos(rotSpeed);
	double oldPlaneX = mCameraPlane.x;
	mCameraPlane.x = mCameraPlane.x * cos(rotSpeed) - mCameraPlane.y * sin(rotSpeed);
	mCameraPlane.y = oldPlaneX * sin(rotSpeed) + mCameraPlane.y * cos(rotSpeed);
}

void Player::Shoot()
{
}

void Player::Die()
{
}
