#include "Game/Game.h"

int main(int /*argc*/, char */*argv*/[])
{
	screen(screenWidth, screenHeight, 0, "EPITOME");

	Game game;
	game.RunGame();

	return 0;
}
