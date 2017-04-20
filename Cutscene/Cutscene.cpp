#include "Cutscene.h"

CutsceneManager::CutsceneManager(int start)
{
	mCurrentScene = start;

	//sets all cutscenes to default state
	for (int i = 0; i < numCutscenes; ++i)
	{
		mSceneType[i] = SceneType::STATIC;
		mNumFrames[i] = 1;
		mFrameSpeeds[i] = 0.0;
	}

	//this is where scenes information is defined

	//SCENE1. andy moving mouth
	mSceneType[SCENE1] = SceneType::ANIMATED;
	mNumFrames[SCENE1] = 2;
	mFrameSpeeds[SCENE1] = .005;

	//SCENE7. this is the scene where andy fixes the code. 4 frames long
	mSceneType[SCENE7] = SceneType::PROGRESSIVE;
	mNumFrames[SCENE7] = 7;
	mFrameSpeeds[SCENE7] = .003;

	//skipped frames (part of animations)
	mNumFrames[SCENE1_2] = 0;

	mNumFrames[SCENE7_2] = 0;
	mNumFrames[SCENE7_3] = 0;
	mNumFrames[SCENE7_4] = 0;
	mNumFrames[SCENE7_5] = 0;
	mNumFrames[SCENE7_6] = 0;
	mNumFrames[SCENE7_7] = 0;


	LoadImages();
	LoadText();

	mQuit = false;
}

void CutsceneManager::LoadImages()
{
	bool success = false;

	//makes every scene the proper size (the size of the image on top of the )
 	for(int i = 0; i < numCutscenes; i++) mImages[i].resize(imageHeight * imageWidth);

	unsigned long tw, th;
	// Scenes
    success |= loadImage(mImages[SCENE1], tw, th, "scenes/scene1open.png");
	success |= loadImage(mImages[SCENE1_2], tw, th, "scenes/scene1close.png");
    success |= loadImage(mImages[SCENE2], tw, th, "scenes/scene2.png");
	success |= loadImage(mImages[SCENE3], tw, th, "scenes/scene3_good.png");
    success |= loadImage(mImages[SCENE4], tw, th, "scenes/scene4.png");
	success |= loadImage(mImages[SCENE5], tw, th, "scenes/scene5.png");
    success |= loadImage(mImages[SCENE6], tw, th, "scenes/scene6.png");
	success |= loadImage(mImages[SCENE7], tw, th, "scenes/scene7-1.png");
    success |= loadImage(mImages[SCENE7_2], tw, th, "scenes/scene7-2.png");
	success |= loadImage(mImages[SCENE7_3], tw, th, "scenes/scene7-3.png");
    success |= loadImage(mImages[SCENE7_4], tw, th, "scenes/scene7-4.png");
	success |= loadImage(mImages[SCENE7_5], tw, th, "scenes/scene7-5.png");
    success |= loadImage(mImages[SCENE7_6], tw, th, "scenes/scene7-6.png");
	success |= loadImage(mImages[SCENE7_7], tw, th, "scenes/scene7-7.png");
	success |= loadImage(mImages[SCENE8], tw, th, "scenes/scene8.png");

	if (success == 0)
		std::cout << "Images Loaded" << std::endl;
	else
		std::cout << "Images Not Loaded" << std::endl;
}

//just has a ton of garbage strings that drawCutscene pulls from
void CutsceneManager::LoadText()
{
	//these are all the texts dur
	mTexts[SCENE1] = "ANDY: \"...now let that sink in. We've got about 10 minutes left in class, so I'm going to let you all relax for a moment.\"";
	mTexts[SCENE2] = "KID: \"Ehh Soir, I got a yuge problem wit muh program. Just can' figga this sucka out.\"";
	mTexts[SCENE3] = "Andy stared at the code, his palms sweaty. This was going to be his hardest debug yet.";
	mTexts[SCENE4] = "He kneaded his temples and closed his eyes. He called upon the strength of all of the masters of computer science: both Deitel and Deitel.";
	mTexts[SCENE5] = "And then, Andy, as he was every time a problem this difficult arose, transported to the computer science dimension.";
	mTexts[SCENE6] = "ANDY: \"I've got it! It was all so simple!\"";
	mTexts[SCENE7] = "With the finesse of a tiger sneaking downstairs to get a midnight snack, he deleted the offending line.";
	mTexts[SCENE8] = "ANDY: \"Thank you very much students, feel free to appl...\"";
	//mTexts[SCENE9] = "But they were all gone. Andy checked his watch and realized it was 7p.m. Class was long over.";
	//mTexts[SCENE10] = "The student's computer began to disappear like sand through his fingers.";
	//mTexts[SCENE11] = "ANDY: \"This can't be happening!\"";
	//mTexts[SCENE12] = "ANDY: \"Ahh... it was all a dream.\"";
}

void CutsceneManager::PlayRange(int start, int end)
{
	//don't go out of bounds. probably should throw exception
	if (end > numCutscenes)
		end = numCutscenes;

	std::cout << "playing cutscenes " << start+1 << " to " << end+1 << std::endl;

	for (int i = start; i <= end; ++i)
	{
		//skips animation frames
		if (mNumFrames[i] != 0)
		{
			std::cout << "displaying scene " << i+1 << std::endl;
			DrawCutscene(i, mSceneType[i], mFrameSpeeds[i], mNumFrames[i]);
		}
	}
}

//dankest function I ever wrote so wonderful
void CutsceneManager::DrawCutscene(int scene, SceneType type, double frameDelay, int numFrames)
{
	//clears screen right before drawing
	cls();

	//animation stays in loop while false
	bool exit = false;

	Uint16 character = 0;
	Uint16 lastCharacter = 0;

	Uint16 animOffset = 0;
	Uint16 lastAnimOffset = 0;

	//declares event used to detect the keypresses
	SDL_Event event = {0};

	//copies appropriate cutscene image for use
	vector<ColorRGB> thisImage = mImages[scene];

	//prints the first image for safety
	for (int y = 0; y < imageHeight; ++y)
	for (int x = 0; x < imageWidth; ++x)
		pset(x, y, thisImage[y * screenWidth + x]);

	//gets the exact time the cutscene starts for animation timing
	Uint32 initial = SDL_GetTicks();
	Uint32 tick = GetDeltaT(initial);

	if (type == SceneType::STATIC)
	{
		//stays in loop until all text is on screen
		while (character < mTexts[scene].length() + 1)
		{
			while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					end();
				//advances text to end on keypress
				if(event.type == SDL_KEYDOWN)
					character = mTexts[scene].length() + 1;
			}

			//only animation is text
			if (character != lastCharacter)
			{
				PrintText(scene, character);
				redraw();
			}

			tick = GetDeltaT(initial);

			//gets next frame info
			if (character < mTexts[scene].length() + 1)
			{
				lastCharacter = character;
				character = (int) (tick * textSpeed);
			}
		}

		//advances to next cutscene on keypress
		sleep();
	}

	//this is the animation handler
	else
	{
		while (exit == false)
		{
			switch (type)
			{
				//will stop when string is done printing
				case SceneType::PROGRESSIVE:
					//restricts animation within bounds
					if (animOffset > numFrames - 1)
						animOffset = numFrames - 1;

					while(SDL_PollEvent(&event))
					{
						if(event.type == SDL_QUIT) end();
						//if scene is indeed done advancing is possible
						if(event.type == SDL_KEYDOWN && character == mTexts[scene].length() + 1 && animOffset == numFrames - 1)
							exit = true;
						if(event.type == SDL_KEYDOWN)
							{character = mTexts[scene].length() + 1; animOffset = numFrames - 1;}
					}

					//if frame has advanced, reprint that sucker
					if (animOffset != lastAnimOffset)
					{
						thisImage = mImages[scene + animOffset]; //dank af
						for (int y = 0; y < imageHeight; ++y)
						for (int x = 0; x < imageWidth; ++x)
							pset(x, y, thisImage[y * screenWidth + x]);
					}
				break;

				case SceneType::ANIMATED:
				//will NEVER stop but when key pressed, text gets to the end
					while(SDL_PollEvent(&event))
		    		{
						if(event.type == SDL_QUIT) end();
						if(event.type == SDL_KEYDOWN && character == mTexts[scene].length() + 1)
						exit = true;
		    			if(event.type == SDL_KEYDOWN)
							{character = mTexts[scene].length() + 1;}
		    		}

					//if frame has advanced, reprint that sucker
					if (animOffset != lastAnimOffset)
					{
						thisImage = mImages[scene + (animOffset % numFrames)]; //dank af
						for (int y = 0; y < imageHeight; ++y)
						for (int x = 0; x < imageWidth; ++x)
							pset(x, y, thisImage[y * screenWidth + x]);
					}
				break;
			}


		//if character has updated, reprint text
		if (character != lastCharacter)
			PrintText(scene, character);

		//sets next tick
		tick = GetDeltaT(initial);

		//decides what's going to update in the next draw

		//doesn't increment character counter if end of string is reached
		if (character < mTexts[scene].length() + 1)
		{
			lastCharacter = character;
			character = (int) (tick * textSpeed); //technically this could be dangerous for extremely small values of textSpeed
		}

		lastAnimOffset = animOffset;
		animOffset = (int) (tick * frameDelay);

		redraw();
		}
	}
}

//calculates time passed since function call
Uint32 CutsceneManager::GetDeltaT(const Uint32 &initial)
{
	return SDL_GetTicks() - initial;
}

//character holds the number of the character to end the printing on
void CutsceneManager::PrintText(int scene, Uint32 character)
{
	//oh jeez rick

	//OKAY SO HERE'S HOW THIS IS GOING TO work
	//STEP ONE JUST COPY AND PASTE THE FUNCTIONS FROM QUICKCG AND F WITH EM UNTIL THEY WORK
	//STEP TWO BONER RISING

	//TODO: make this nonlinear! to fix cutscenes
	//sort of did it
	//character variable holds the index of the stopping character

	int x = 20;
	int y = 420;

	int u,v;

	ColorRGB color = ColorRGB(0,255,0); //text is green
	ColorRGB color2 = ColorRGB(0,0,0); //background is black if it exists

	//loads proper text in
	//I would make a string the argument but since this function is very specialized
	//(it starts on a predefined screen position everytime), it doesn't really make too much sense
	std::string text = mTexts[scene];

	//will print a background behind the text if this is et to true
	bool bg = false;
	int forceLength = 0;

	//lineLength based on size of window but nothing else is. BAD DESIGN!
	int lineLength = (int) (screenWidth - 40) / 16;

	//changes the cubic size of the text. filled pixels independent of size
	int textMult = 3;

	//heavily modified functions from QuickCG
	int charNum = 0;
	for(size_t i = 0; i < character && i < text.size(); i++)
	{
		for (v = 0; v < 8; v++)
		for (u = 0; u < 8; u++)
		{
			//these two for loops determine text fill
			for (int k = 0; k < 2; ++k)
			for (int j = 0; j < 2; ++j)
			{
		  		if(font[text[i]][u][v]) pset(x + u*textMult + k, y + v*textMult + j, color);
		  		else if(bg) pset(x + u*textMult + k, y + v*textMult + j, color2);
	  		}
		}

		x += 8 * textMult;
		//this is pretty much straight out of FwD 2
		if(x > w - 8 * textMult || (text[i] == ' ' && charNum > lineLength - charNum) ) {charNum = 0; x %= 8 * textMult; y += 8 * textMult;}
		if(y > h - 8 * textMult) {y %= 8 * textMult;}
		charNum++;
	}
}
