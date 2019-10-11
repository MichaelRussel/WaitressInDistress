// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.

#include "cMenuScene.h"
#include "cAssetManager.h"
#include "cGame.h"
#include "cBackground.h"
#include "gameScene.h"
#include "cSound.h"
#include "Globals.h"

#pragma warning(disable:4996)

cMenuScene::cMenuScene()
{

}

cMenuScene::~cMenuScene()
{
}


void cMenuScene::Init()
{
	temp = cGame::getInstance().getHighScore();
	highScore = const_cast<char*>(temp.c_str());

	cSound::getInstance().Play(SOUND_AMBIENT2);
	menu_background = new cBackground(cAssetManager::getInstance().menu_background, 0, 0, GAME_WIDTH, GAME_HEIGHT);
	addGameObject(menu_background);

}


void cMenuScene::Render()
{

	cScene::Render();
	renderBitmapString(120, GAME_HEIGHT - 50 , 9, GLUT_BITMAP_HELVETICA_18, "~RiZe Up~", 1, 1, 1);
	
	renderBitmapString(80, GAME_HEIGHT - 100, 9 , GLUT_BITMAP_HELVETICA_18, "Play Game", 1, 1, 1);

	if (soundCondition == true) {
		renderBitmapString(80, GAME_HEIGHT - 130, 9, GLUT_BITMAP_HELVETICA_18, "Sound : On", 1, 1, 1);
	}
	else {
		renderBitmapString(80, GAME_HEIGHT - 130, 9 , GLUT_BITMAP_HELVETICA_18, "Sound : Off", 1, 1, 1);
	}				
	renderBitmapString(390, GAME_HEIGHT - 30, 9 , GLUT_BITMAP_HELVETICA_18, "Highscore : " , 1, 1, 1);
	renderBitmapString(490, GAME_HEIGHT - 30, 9, GLUT_BITMAP_HELVETICA_18, highScore, 1, 1, 1);
			
	renderBitmapString(80, GAME_HEIGHT - 160, 9 , GLUT_BITMAP_HELVETICA_18, "Exit", 1, 1, 1);
}

// fps = 30 tpf = time per frame = 1/30
void cMenuScene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);
		

}

void cMenuScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
{

	cScene::ReadKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cMenuScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	cScene::ReadSpecialKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}


void cMenuScene::ReadMouse(int button, int state, int x, int y)
{
	//std::cout << x << " " << y << "\n";
	if (state == GLUT_DOWN && x >= 75 && x <= 180 && y >= 110 && y <= 140) {
		soundCondition = !soundCondition;
		cMenuScene:getInstance().soundCondition = soundCondition;
		cSound::getInstance().Pause(SOUND_AMBIENT2);
	}

	if (x >= 75 && x <= 175 && y >= 80 && y <= 105) {
		cGame::getInstance().UpdateScene(new gameScene);
	}

	if (x >= 75 && x <= 120 && y >= 140 && y <= 160) {
		exit(0);
	}
}

