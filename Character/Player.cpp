#include "Player.h"

Player::Player() :
	Character(0, 0, 0, 0, 0, 0, -1)
{
	setArmor(0);
	setBattery(0);
}

Player::Player(int health, int armor, int battery, double speed, double posX, double posY, double dirX, double dirY, double cameraX, double cameraY) :
	Character(health, speed, posX, posY, dirX, dirY, -1)
{
	setCameraPlane(cameraX, cameraY);
}

Player::Player(int health, int armor, int battery, double speed, Vector2<double> pos, Vector2<double> dir, Vector2<double> camera) :
	Character(health, speed, pos, dir, -1)
{
	setArmor(armor);
	setBattery(battery);
	setCameraPlane(camera.x, camera.y);
}

Vector2<double> Player::getCameraPlane() const { return mCameraPlane; }
int Player::getArmor() const { return mArmor; }
int Player::getBattery() const { return mBattery; }
Gun &Player::getCurrentGun() { return mGuns.at(mCurrentGun); }

void Player::setCameraPlane(const Vector2<double> &cam) { setCameraPlane(cam.x, cam.y); }
void Player::setCameraPlane(const double &camX, const double &camY)
{
	mCameraPlane.setX(camX);
	mCameraPlane.setY(camY);
}

void Player::setArmor(const int &armor) { mArmor = armor; }
void Player::setBattery(const int &battery) { mBattery = battery; }

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
	//playSound(mShootSound);
	getCurrentGun().shoot();
}

void Player::Die()
{
}

void Player::AddGun(int screenX, int screenY, int damage, int shotDelay, int defaultTexture)
{
	Gun g(screenX, screenY, damage, shotDelay, defaultTexture);
	mGuns.push_back(g);
}

void Player::AddGun(Vector2<int> screenPos, int damage, int shotDelay, int defaultTexture)
{
	Gun g(screenPos, damage, shotDelay, defaultTexture);
	mGuns.push_back(g);
}
