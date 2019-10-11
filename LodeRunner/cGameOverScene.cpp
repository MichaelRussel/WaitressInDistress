// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.

#include "cGameOverScene.h"
#include "cAssetManager.h"
#include "cGame.h"
#include "cMenuScene.h"
#include "cSound.h"


cGameOverScene::cGameOverScene()
{

}

cGameOverScene::~cGameOverScene()
{

}

void cGameOverScene::Init()
{
	// count highscore 
	if (cPlayer::getInstance().isGoal) {
		totalHighScore = cPlayer::getInstance().health * 50
		+ cPlayer::getInstance().gasPoint * 25
		+ cPlayer::getInstance().maxLatitude
		+ 2000;
		std::cout << "goal";
	}
	else
		totalHighScore = cPlayer::getInstance().health * 50
		+ cPlayer::getInstance().gasPoint * 25
		+ cPlayer::getInstance().maxLatitude;
	
	//convert  highscore to char*
	temp2 = std::to_string(totalHighScore);
	totalScore = const_cast<char*>(temp2.c_str());

	//current score and convert to char*
	currHighScore = std::stoi(cGame::getInstance().getHighScore());
	temp = cGame::getInstance().getHighScore();
	highScore = const_cast<char*>(temp.c_str());

	//set to first state
	cPlayer::getInstance().health = 100;
	cPlayer::getInstance().maxLatitude = 0;
	cPlayer::getInstance().gasPoint = 100;
	cPlayer::getInstance().isGoal = false;
	// return all gasoline to each position
	for (int i = 0; i < gasoline->size(); i++) {
		addGameObject(gasoline->at(i));
	}

	//check sound condtion
	soundCondition = cMenuScene::getInstance().soundCondition;
	// turn off sound
	if (soundCondition == 0 || soundCondition == 1) {
		cSound::getInstance().StopAll();
	}
}

void cGameOverScene::Render()
{
	cScene::Render();
	
	if (totalHighScore > currHighScore) {
	
		renderBitmapString(30, 290, 9, GLUT_BITMAP_HELVETICA_18, "New HighScore ! ", 1, 1, 1);
		renderBitmapString(30, 250, 9, GLUT_BITMAP_HELVETICA_18, "Highscore : ", 1, 1, 1);
		renderBitmapString(140, 250, 9, GLUT_BITMAP_HELVETICA_18, totalScore, 1, 1, 1);
		cGame::getInstance().setHighScore(totalScore);
	}
	else {
		renderBitmapString(30,290, 9, GLUT_BITMAP_HELVETICA_18, "Your Score : ", 1, 1, 1);
		renderBitmapString(140, 290, 9, GLUT_BITMAP_HELVETICA_18, totalScore, 1, 1, 1);
		renderBitmapString(30, 250, 9, GLUT_BITMAP_HELVETICA_18, "Highscore : ", 1, 1, 1);
		renderBitmapString(140, 250, 9, GLUT_BITMAP_HELVETICA_18, highScore, 1, 1, 1);
	}
	renderBitmapString(180,130, 9, GLUT_BITMAP_HELVETICA_18, "Click here to play again!", 1, 1, 1);
	
	renderBitmapString(250,90, 9, GLUT_BITMAP_HELVETICA_18, "Or Exit?", 1, 1, 1);

}

// fps = 30 tpf = time per frame = 1/30
void cGameOverScene::Update(float tpf /*= 0.0333*/)
{
	cScene::Update(tpf);

	glMatrixMode(GL_PROJECTION); // render camera
	glLoadIdentity(); // reset/refresh projection sebelumnya
	glOrtho(0, GAME_WIDTH, 0, GAME_HEIGHT, 3, -101);
	glMatrixMode(GL_MODELVIEW); // scalling/translate model
	glLoadIdentity();

}

void cGameOverScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
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

void cGameOverScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
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


void cGameOverScene::ReadMouse(int button, int state, int x, int y)
{
	std::cout << x << " " << y << "\n";

	if (x >= 180 && x <= 380 && y >= 450 && y <= 470) {
		cGame::getInstance().UpdateScene(new cMenuScene());
	}

	if (x >= 250 && x <= 320 && y >= 495 && y <= 510) {
		exit(0);
	}
}

