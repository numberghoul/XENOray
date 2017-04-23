#pragma once

#include "../E_Def.h"

class Button
{
public:
	Button(Vector2<double> upperLeft, void (* action)(), std::string filename = "Textures/UI/button.png");
	double getUpX(){return mUpperLeft.x;}
	double getUpY(){return mUpperLeft.y;}
	double getLowX(){return mLowerRight.x;}
	double getLowY(){return mLowerRight.y;}
	bool OnClick(int clickx, int clicky);
	void Draw();
private:
	Vector2<double> mUpperLeft, mLowerRight;
	void (*Do)() = nullptr;
	//the sprite
	std::vector<ColorRGB> mSprite;
	long unsigned int mWidth;
	long unsigned int mHeight;
};
