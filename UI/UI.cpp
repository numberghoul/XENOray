#include "UI.h"

#define buttonWidth 400
#define buttonHeight 200

Button::Button(Vector2<double> upperLeft, void (* action)(), std::string filename)
{
	mUpperLeft.x = upperLeft.x; mUpperLeft.y = upperLeft.y;
	Do = action;
	bool success;

	//widens that sprite. ready to accept
	mSprite.resize(buttonWidth * buttonHeight);

	success = loadImage(mSprite, mWidth, mHeight, filename);

	//sets bounds of button for mouse collision later
	mLowerRight.x = mUpperLeft.x + mWidth;
	mLowerRight.y = mUpperLeft.y + mHeight;
}

bool Button::OnClick(int clickx, int clicky)
{
	//debug garbage
	//std::cout << "r: " << mLowerRight.x << " l:" << mUpperLeft.x << "d: " << mLowerRight.y << "u: " << mUpperLeft.y << std::endl;

	//if click passed in is within button bounds, call function
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
	{
		pset(x + mUpperLeft.x, y + mUpperLeft.y, mSprite[y * mWidth + x]);
	}
}