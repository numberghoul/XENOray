#include "../Vector2.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Character
{
public:
	virtual void TakeDamage(int damage) = 0;
	virtual void Move() = 0;
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
