#include "Cutscene/Cutscene.h"
#include "Menu/Menu.h"

int main(int /*argc*/, char */*argv*/[])
{
	screen(screenWidth, screenHeight, 0, "EPITOME");

	DisplayMenu();

	CutsceneManager cm;

	//plays the intro
	cm.PlayRange(SCENE1, SCENE5);

	Game game;
	game.RunGame("e1m1");

	return 0;
}
