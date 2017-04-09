#include "Game/Game.h"

int main(int /*argc*/, char */*argv*/[])
{
	screen(screenWidth, screenHeight, 0, "XENO");

	Game game;
	game.RunGame();

	return 0;
}
