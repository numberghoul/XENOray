#pragma once

//CutsceneManager by Ryan so good

#include "../quickcg.h"
#include <iostream>

using std::vector; //take that hunter
using std::string;

using namespace QuickCG;

#define numCutscenes 15

#define textSpeed .05 //lower number lower speed

#define screenWidth 800
#define screenHeight 600

//images must be this size or everything breaks
//definitely fixable but for the sake of oldschool cutscenes I refuse
#define imageWidth screenWidth
#define imageHeight screenHeight * 2 / 3 //two thirds the height of the screen. other half text

//important enum that contains more logical cutscene names
//declared up here because they are called in main.cpp *thumbs up emoji*
enum CutsceneList { SCENE1, SCENE1_2, SCENE2, SCENE3, SCENE4, SCENE5, SCENE6, SCENE7, SCENE7_2, SCENE7_3, SCENE7_4, SCENE7_5, SCENE7_6, SCENE7_7, SCENE8 };
enum SceneType { STATIC, ANIMATED, PROGRESSIVE };

class CutsceneManager
{
public:
	//constructor loads images and strings in in preparation for printing
	CutsceneManager(int start);

	//plays range from
	void PlayRange(int start, int end); //displays cutscenes in the range defined by user

	//adds scene to buffer, calls printText() and then printBuffer()?
	void DrawCutscene(int scene, SceneType type, double frameDelay, int numFrames = 1);
private:
	//holds the current scene index
	int mCurrentScene;
	//holds screen height, width dur
	int mScreenWidth, mScreenHeight;

	//possible parallel array that tracks cutscene type (static, animated, progressive)
	SceneType mSceneType[numCutscenes];
	//another parallel array that groups frames into scenes
	int mNumFrames[numCutscenes]; //if this number is 0 that image is skipped
	//yet another parallel that chooses frame speeds for every speed
	double mFrameSpeeds[numCutscenes];

	vector<ColorRGB> mImages[numCutscenes];
	string mTexts[numCutscenes];

	//great
	bool mQuit;

	void LoadImages();
	void LoadText();

	void AnimateScene();

	//gets time since function call. Used for animation timings. Thanks Hunter
	Uint32 GetDeltaT(const Uint32 &initial);

	//draws text and image for cutscene
	void PrintText(int scene, Uint32 character = -1); //will automatically print entire text without second argument
};
