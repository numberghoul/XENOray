#include "Menu.h"

void DisplayMenu()
{
	std::vector<ColorRGB> BG;
	int success =0;
	unsigned long mw, mh;
  	success = loadImage(BG, mw, mh, "Textures/gamelogo.png");

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;

	Vector2<double> startPos((screenWidth/2) - 75, screenHeight/2);
	Vector2<double> startSize(150, 40);
	std::vector<Uint32> startImg;
	Button StartButton(startPos, startSize, startImg, &StartGame);

	success = 0;
	while(!success)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		if( event.type == SDL_MOUSEBUTTONUP )
		{
			int mx, my;
			SDL_GetMouseState(&mx, &my);
			success = StartButton.OnClick(mx, my);
		}

	double skipX = screenWidth / mw;
	double skipY = screenHeight / mh;
	//std::cout << skipX << " " << skipX << std::endl;

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

	for (int x = StartButton.getUpX(); x < StartButton.getLowX(); x++)
	{
		for(int y = StartButton.getUpY(); y < StartButton.getLowY(); y++)
		{
			pset(x, y, ColorRGB(0,0,0));
		}
	}

	redraw();
}
}

void StartGame()
{
	CutsceneManager cm;

	//plays the intro
	//cm.PlayRange(SCENE1, SCENE5);
	Game game;
	game.RunGame("e1m1");
}
