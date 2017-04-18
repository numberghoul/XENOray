#include "UI.h"

Button::Button(Vector2<double> pos, Vector2<double> size, std::vector<Uint32> sprite, void (* action)())
{
	mUpperLeft.x = pos.x; mLowerRight.y = pos.y;
	mSprite = sprite;
	Do = action;

	mLowerRight.x = mUpperLeft.x + size.x;
	mLowerRight.y = mUpperLeft.y + size.y;
}

bool Button::OnClick(Vector2<double> click)
{
	if (click.x < mLowerRight.x && click.x > mUpperLeft.x
	&& click.y < mLowerRight.y && > mUpperLeft.y)
	{
		Do();
	}
}
