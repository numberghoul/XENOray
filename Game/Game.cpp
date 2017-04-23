#include "Game.h"

Game::Game(int width, int height)
{
	setWidth(width);
	setHeight(height);

	mQuit = false;
}

Game::~Game()
{
	for (int i = 0; i < numSounds; ++i)
		Mix_FreeChunk(mSounds.at(i));
	for ( int i = 0; i < numSongs; ++i)
		Mix_FreeMusic(mSongs.at(i));
}

void Game::RunGame(std::string mapName)
{
	LoadSounds();
	LoadTextures();
	LoadMap(mapName);
	LoadEnemies(mapName);
	InitPlayer();

	double time = 0; //time of current frame
	double oldTime = 0; //time of previous frame

	float deltaMouse = 0.0f;

	playSong(mSongs[Songs::AndySong]);

	while(!mQuit)
	{
		int oldmx, oldmy;
		SDL_GetMouseState(&oldmx, &oldmy);

		Render();

		//DRAW CROSSHAIR
		for (int i = -5; i <= 5; ++i)
			for (int j = -5; j <= 5; ++j)
			{
				if (i < 2 && j < 2)
				mBuffer[screenHeight/2 + i][screenWidth/2 + j] = RGBtoINT(ColorRGB(255,0,0));
			}
		drawBuffer(mBuffer[0]);
		for(int x = 0; x < getWidth(); x++) for(int y = 0; y < getHeight(); y++) mBuffer[y][x] = 0; //clear the buffer instead of cls()

		//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		mFrameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / mFrameTime); //FPS counter

		readKeys();
		UpdateRotation(deltaMouse);
		UpdateMovement();
		CheckShoot();
		CheckPause();
		//this will be removed in final build. used until pause menu has quit feature
		CheckQuit();

		int mx, my;
		SDL_GetMouseState(&mx, &my);

		deltaMouse = mx - oldmx;
		deltaMouse /= 1000.0f;

		SDL_WarpMouse(screenWidth/2, screenHeight/2);
		SDL_ShowCursor(0);

		redraw();
		//std::cout << mEnemies[0].isVisible() << " " << mEnemies[1].isVisible() << std::endl;
	}
}