#include "Menu.h"

void DisplayMenu()
{
	std::vector<ColorRGB> BG;
	int success =0;
	unsigned long mw, mh;
  	success = loadImage(BG, mw, mh, "textures/gamelogo.png");

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;

	double skipX = screenWidth / mw;
	double skipY = screenHeight / mh;
	std::cout << skipX << " " << skipX << std::endl;

	//draw each pixel of the image
	for(int y = 0; y < mh; y++)
	{
		for(int x = 0; x < mw; x++)
		{
			for (int i = x * skipX; i < screenWidth && i < x * skipX + skipX; i++)
			{
				for (int j = y * skipY; j < screenHeight && j < y * skipY + skipY; j++)
				{
					pset(i, j, BG[y * mw + x]);
				}
			}
		}
	}

	redraw();
	sleep();
}
