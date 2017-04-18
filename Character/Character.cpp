#include "Character.h"

// Constructors
Character::Character(int health, double speed, double posX, double posY, double directionX, double directionY, int texture) :
	Object(posX, posY, directionX, directionY, texture, true)
{
	setHealth(health);
	setSpeed(speed);
}

Character::Character(int health, double speed, Vector2<double> pos, Vector2<double> dir, int texture) :
	Object(pos, dir, texture, true)
{
	setHealth(health);
	setSpeed(speed);
}

// Getters
int Character::getHealth() const { return mHealth; }
double Character::getSpeed() const { return mSpeed; }

//Setters
void Character::setHealth(int health) { mHealth = health; }
void Character::setSpeed(double speed) { mSpeed = speed; }
