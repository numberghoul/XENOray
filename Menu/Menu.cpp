#include "Menu.h"

void DisplayMenu()
{
	// Audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		BAD();

	std::vector<ColorRGB> BG;
	int success =0;
	unsigned long mw, mh;
  	success = loadImage(BG, mw, mh, "Textures/gamelogo.png");
	Button StartButton(Vector2<double>(screenWidth/2 - 200, screenHeight/2), &StartGame);

	if (success == 0)
		std::cout << "Textures Loaded" << std::endl;
	else
		std::cout << "Textures Not Loaded" << std::endl;

	success = false;

	Mix_Music* menuMusic = Mix_LoadMUS("Music/CallMe8bit.wav");

	playSong(menuMusic);

	success = false;

	while(!success)
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		//could use MOUSEBUTTONDOWN to change button graphic
		//but how to do that with function pointers

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

		//draws the button. vector would allow drawing all buttons
		StartButton.Draw();

		redraw();
	}
}

//this function is really weird I don't know if I like it
//-Ryan
void StartGame()
{
	//Mix_FreeMusic(menuMusic);
	CutsceneManager cm;


	//plays the intro
	//cm.PlayRange(SCENE1, SCENE5);
	Game game;
	game.RunGame("e1m1");
}
