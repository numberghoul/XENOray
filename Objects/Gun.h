#pragma once
#include "Object.h"

class Gun
{
public:
    Gun (Vector2<int> screenPos, int damage, int shotDelay, int defaultTexture);
    Gun (int screenX, int screenY, int damage, int shotDelay, int defaultTexture);

    int getDamage() const;
    Vector2<int> getScreenPos() const;
    int getDefaultTexture() const;
    int getCurrentTexture() const;
    bool isShooting() const;

    void update();
    bool canShoot() const;
    void addAnimationFrame(int frameTexture);
    void animate();
    void shoot();

private:
    int mDefaultTexture,
        mCurrentFrameIndex,
        mDamage,
        mShotDelay,
        mAnimTicks, mAnimOldTicks,
        mGameTicks, mGameOldTicks;
    Vector2<int> mScreenPos;
    std::vector<int> mAnimationFrames;

    bool mIsShooting;
};