#include "UI.h"

Button::Button(Vector2<double> upperLeft, void (* action)(), std::string filename)
{
	mUpperLeft.x = upperLeft.x; mUpperLeft.y = upperLeft.y;
	Do = action;
	bool success;

	std::cout << "it got here" << std::endl;

	mSprite.resize(400 * 200);

	//LOADS IN COLORRGB POOP
	success = loadImage(mSprite, mWidth, mHeight, filename);

	if (!success)
		std::cout << "good job ryan you aren't an idiot" << std::endl;

	//mSprite.shrink_to_fit();

	mLowerRight.x = mUpperLeft.x + mWidth;
	mLowerRight.y = mUpperLeft.y + mHeight;
}

bool Button::OnClick(int clickx, int clicky)
{
	//debug garbage
	//std::cout << "r: " << mLowerRight.x << " l:" << mUpperLeft.x << "d: " << mLowerRight.y << "u: " << mUpperLeft.y << std::endl;

	if (clickx < mLowerRight.x && clickx > mUpperLeft.x
	&& clicky < mLowerRight.y && clicky > mUpperLeft.y)
	{
		if (Do != nullptr)
			Do();
		return true;
	}

	return false;
}

void Button::Draw()
{	
	for (int y = 0; y < mHeight; ++y)
	for (int x = 0; x < mWidth; ++x)
	//for (int y = mLowerRight.y; y < mUpperLeft.y - 1; ++y)
	//for (int x = mUpperLeft.x; x < mLowerRight.x - 1; ++x)
	{
		//ah cool this work
		pset(x + mUpperLeft.x, y + mUpperLeft.y, mSprite[y * mWidth + x]);
	}
}