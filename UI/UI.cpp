#include "UI.h"

Button::Button(Vector2<double> pos, Vector2<double> size, std::vector<Uint32> sprite, void (* action)())
{
	mUpperLeft.x = pos.x; mUpperLeft.y = pos.y;
	mSprite = sprite;
	Do = action;

	mLowerRight.x = mUpperLeft.x + size.x;
	mLowerRight.y = mUpperLeft.y + size.y;
}

bool Button::OnClick(int clickx, int clicky)
{
	if (clickx < mLowerRight.x && clickx > mUpperLeft.x
	&& clicky < mLowerRight.y && clicky > mUpperLeft.y)
	{
		Do();
	}
}
