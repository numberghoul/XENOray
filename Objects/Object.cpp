#include "Object.h"

Object::Object(double posX, double posY, int angle, int texture)
{
	setPosX(posX);
	setPosY(posY);
	setAngle(angle);
	setTexture(texture);
}

double Object::getPosX() const
{
	return mPosX;
}

double Object::getPosY() const
{
	return mPosY;
}

int Object::getAngle() const
{
	return mAngle;
}

int Object::getTexture() const
{
	return mTexture;
}

void Object::setPosX(const double &posY)
{
	mPosY = posY;
}

void Object::setPosY(const double &posX)
{
	mPosX = posX;
}

void Object::setAngle(const int &angle)
{
	mAngle = angle;
}

void Object::setTexture(const int &texture)
{
	mTexture = texture;
}
