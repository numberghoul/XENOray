#pragma once

#include "../E_Def.h"

class Button
{
public:
	Button(Vector2<double> pos,Vector2<double> size, std::vector<Uint32> sprite, void (* action)());

	bool OnClick(Vector2<double> click);
private:
	Vector2<double> mUpperLeft, mLowerRight, mPos;
	void (*Do)() = nullptr;
	std::vector<Uint32> mSprite;
};
