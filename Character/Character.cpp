#include "Character.h"

// Constructors
Character::Character(int health, double speed, double posX, double posY, double directionX, double directionY, int texture) :
	Object(posX, posY, directionX, directionY, texture, true)
{
	setHealth(health);
	setSpeed(speed);
	mIsDead = false;
}

Character::Character(int health, double speed, Vector2<double> pos, Vector2<double> dir, int texture) :
	Object(pos, dir, texture, true)
{
	setHealth(health);
	setSpeed(speed);
}

// Destructor
Character::~Character()
{
	if (mDamageSound != nullptr && mDamageSound->allocated)
	{
		Mix_FreeChunk(mDamageSound);
		mDamageSound = nullptr;
	}
	if (mTauntSound != nullptr && mTauntSound->allocated)
	{
		Mix_FreeChunk(mTauntSound);
		mTauntSound = nullptr;
	}
	if (mDeathSound != nullptr && mDeathSound->allocated)
	{
		Mix_FreeChunk(mDeathSound);
		mDeathSound = nullptr;
	}
}

// Getters
int Character::getHealth() const { return mHealth; }
double Character::getSpeed() const { return mSpeed; }

//Setters
void Character::setHealth(int health) { mHealth = health; }
void Character::setSpeed(double speed) { mSpeed = speed; }

void Character::loadDamageSound(std::string fileName) { mDamageSound = Mix_LoadWAV(fileName.c_str()); }
void Character::loadTauntSound(std::string fileName) { mTauntSound = Mix_LoadWAV(fileName.c_str()); }
void Character::loadDeathSound(std::string fileName) { mDeathSound = Mix_LoadWAV(fileName.c_str()); }

bool Character::isDead() { return mIsDead; }
