#pragma once
#include "../HelperClasses/Vector2.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Character
{
public:
	virtual void TakeDamage(int damage) = 0;
	virtual void Move(double x, double y) = 0; // x and y represent the new position vector components
	virtual void Shoot() = 0;

protected:
	virtual void Die() = 0;

	Vector2<double> mPosition,
	 				mVelocity;

	Mix_Chunk *mDamageSound = nullptr,
			  *mTauntSound = nullptr,
			  *mDeathSound = nullptr;

	int mHealth;

	double mSpeed;
};
