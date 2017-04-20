#include "Cutscene/Cutscene.h"
#include "Game/Game.h"

int main(int /*argc*/, char */*argv*/[])
{
	screen(screenWidth, screenHeight, 0, "EPITOME");

	CutsceneManager cutsceneName(0);

	//plays the intro
	cutsceneName.PlayRange(SCENE1, SCENE8);

	//cutsceneName.DrawCutscene(SCENE8, STATIC);

	//Game game;
	//game.RunGame();

	sleep();

	return 0;
}
