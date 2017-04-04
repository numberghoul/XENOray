#include "Game/Game.h"

int main(int /*argc*/, char */*argv*/[])
{
	screen(1280, 720, 0, "XENO");

	Game game;
	game.RunGame();

	return 0;
}
