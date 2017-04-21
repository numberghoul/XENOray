#include "Object.h"

Object::Object(double posX, double posY, double directionX, double directionY, int texture, bool rotates)
{
	setPosition(posX, posY);
	setDirection(directionX, directionY);
	setRotation(rotates);
	setTexture(texture);
}

Object::Object(Vector2<double> pos, Vector2<double> dir, int texture, bool rotates)
{
	setPosition(pos);
	setDirection(dir);
	setRotation(rotates);
	setTexture(texture);
}

Vector2<double> Object::getDirection() const { return mDirection; }
Vector2<double> Object::getPosition() const { return mPosition; }
int Object::getTexture() const { return mTexture; }
bool Object::rotates() const { return mRotates; }

void Object::setDirection(const Vector2<double> &dir) { setPosition(dir.x, dir.y); }
void Object::setDirection(const double &dirX, const double &dirY)
{
	mDirection.setX(dirX);
	mDirection.setY(dirY);
}

void Object::setPosition(const Vector2<double> &pos) { setPosition(pos.x, pos.y); }
void Object::setPosition(const double &posX, const double &posY)
{
	mPosition.setX(posX);
	mPosition.setY(posY);
}

void Object::setTexture(const int &texture)
{
	mTexture = texture;
}

void Object::setRotation(const bool &rotates) { mRotates = rotates; }
