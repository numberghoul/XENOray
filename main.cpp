#include "Menu/Menu.h"
#include "Game/Game.h"

int main(int /*argc*/, char */*argv*/[])
{
	screen(screenWidth, screenHeight, 1, "EPITOME");

	//DisplayMenu();
	Game game;
	game.RunGame("e1m1");

	return 0;
}
