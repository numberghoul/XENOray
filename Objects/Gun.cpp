#include "Gun.h"

Gun::Gun (Vector2<int> screenPos, int damage, int shotDelay, int defaultTexture)
{
    mScreenPos = screenPos;
    mDamage = damage;
    mDefaultTexture = defaultTexture;
    mShotDelay = shotDelay;
    mCurrentFrameIndex = 0;
    mIsShooting = false;

    mGameOldTicks = mGameTicks = 0;
    mAnimOldTicks = mAnimTicks = 0;
}

Gun::Gun (int screenX, int screenY, int damage, int shotDelay, int defaultTexture)
{
    mScreenPos.x = screenX;
    mScreenPos.y = screenY;
    mDamage = damage;
    mDefaultTexture = defaultTexture;
    mShotDelay = shotDelay;
    mCurrentFrameIndex = 0;
    mIsShooting = false;

    mGameOldTicks = mGameTicks = 0;
    mAnimOldTicks = mAnimTicks = 0;
}

int Gun::getDamage() const { return mDamage; }
Vector2<int> Gun::getScreenPos() const { return mScreenPos; }
int Gun::getDefaultTexture() const { return mDefaultTexture; }
int Gun::getCurrentTexture() const { return mCurrentFrameIndex == 0 ? mDefaultTexture : mAnimationFrames[mCurrentFrameIndex - 1]; }
bool Gun::isShooting() const { return mIsShooting; }

void Gun::update()
{
    mGameTicks = getTicks();
}

bool Gun::canShoot() const { return (mGameTicks - mGameOldTicks) > 500; }
void Gun::addAnimationFrame(int frameTexture) { mAnimationFrames.push_back(frameTexture); }
void Gun::animate()
{
    if((mAnimTicks - mAnimOldTicks) == 5)
	{
        if (mCurrentFrameIndex == mAnimationFrames.size() - 1)
        {
            mCurrentFrameIndex = 0;
            mIsShooting = false;
            return;
        }

		mAnimOldTicks = mAnimTicks;
		mCurrentFrameIndex++;
		//std::cout << mCurrentFrameIndex << std::endl;
	}

	mAnimTicks++;
}
void Gun::shoot()
{
    if (mIsShooting)
        mCurrentFrameIndex = 0;
    else 
        mIsShooting = true;

    mGameOldTicks = mGameTicks;
    update();
}
