#include "../Vector2.h"
#include <SDL/SDL.h>

class Character
{
public:
	virtual void TakeDamage() = 0;
	virtual void Die() = 0;
	virtual void Move() = 0;
	virtual void Shoot() = 0;

private:
	Vector2<double> mPosition,
	 				mVelocity;

	Mix_Chunk mDamageSound = NULL,
			   mTauntSound = NULL,
			   mDeathSound = NULL;

	int mHealth;

	double mSpeed;
};
