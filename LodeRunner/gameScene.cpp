// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "gameScene.h"
#include "cAssetManager.h"
#include "cGame.h"
#include "cMenuScene.h"
#include "cBlock.h"
#include "cBackground.h"
#include "cSound.h"
#pragma warning(disable:4996)

gameScene::gameScene()
{
	
}

gameScene::~gameScene()
{
}

void gameScene::Init()
{	
	// map inizialization
	map = cGame::getInstance().getMap();
	// music inizialization
	soundCondition = cMenuScene::getInstance().soundCondition;

	// if sound off
	if (soundCondition == 0) {
		cSound::getInstance().StopAll();
	}
	// if sound on
	else if (soundCondition == 1) {
		cSound::getInstance().StopAll();
		cSound::getInstance().Play(SOUND_AMBIENT3);
		cSound::getInstance().Play(SOUND_AMBIENT4);
	}

	int x = 0;
	int y = 2250;
	int blockCount = 0;
	int gasCount = 0;

	for (char temp : map) {
		x += 30;
		if (temp == '#') {
			gasoline->push_back(new cGasoline(cAssetManager::getInstance().gasoline, x, y, BLOCK_SIZE, BLOCK_SIZE));
			addGameObject(gasoline->at(gasCount));
			gasCount++;
		}
		else if (temp == '0') {
			player = new cPlayer(cAssetManager::getInstance().player, x, y, 0.8 * TILE_SIZE, 1.25 * TILE_SIZE);
			addGameObject(player);
		}
		else if (temp == '|' || temp == '-') {
			block->push_back(new cBlock(cAssetManager::getInstance().block, x ,y, BLOCK_SIZE, BLOCK_SIZE));
			addGameObject(block->at(blockCount));
			blockCount++;
		}
		else if (temp == '\n') {
			x = 0;
			y -= 30;
		}
	}
	

}
int i = 0;
bool meteorSummoned = true;
void summonMeteor(int value) {
	//cFireBall::getInstance().fireBallStats();
	if (meteorSummoned == false) {
		i++;
		meteorSummoned = true;
		//glutPostRedisplay();
	}
}

void gameScene::Render()
{
	cScene::Render();
	int playerX = player->X() + 130;
	int playerY = player->Y() + 310;

	renderBitmapString(playerX, playerY,9, GLUT_BITMAP_HELVETICA_18, "Gas Remaining : ", 1, 0, 0);
	renderBitmapString(playerX + 120, playerY, 9, GLUT_BITMAP_HELVETICA_18, gas, 1, 0, 0);
	renderBitmapString(playerX, playerY - 20, 9, GLUT_BITMAP_HELVETICA_18, "Hp Left : ", 1, 0 ,0);
	renderBitmapString(playerX + 65, playerY - 20, 9, GLUT_BITMAP_HELVETICA_18, health , 1, 0, 0);
	renderBitmapString(playerX, playerY - 40, 9, GLUT_BITMAP_HELVETICA_18, "Highest Latitude :", 0, 0, 1);
	renderBitmapString(playerX + 135, playerY - 40, 9, GLUT_BITMAP_HELVETICA_18, latitude, 0, 0, 1);

	visible_area.top = player->Y() + player->Height() + 250;
	visible_area.bottom = player->Y() - 250;
	visible_area.left = player->X() - 250;
	visible_area.right = player->X() + player->Width() + 250;

	//make background move as player move
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, cAssetManager::getInstance().background->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1), glVertex3i(visible_area.left, visible_area.bottom, 49); // texcoor ambil png, vertex3 dari gambar 
	glTexCoord2f(1, 1), glVertex3i(visible_area.right, visible_area.bottom, 49);
	glTexCoord2f(1, 0), glVertex3i(visible_area.right, visible_area.top, 49);
	glTexCoord2f(0, 0), glVertex3i(visible_area.left, visible_area.top, 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void gameScene::Update(float tpf = 0.0333)
{
	cScene::Update(tpf);

	//summon fireball/meteor whatever la
	if (meteorSummoned == true) {
		glutTimerFunc(1000, summonMeteor, 0);
		cFireBall::getInstance().fireBallStats();
		fireball->push_back(
			new cFireBall(cAssetManager::getInstance().fireball,
				cFireBall::getInstance().fireBallSpawnedX,
				cFireBall::getInstance().fireBallSpawnedY,
				cFireBall::getInstance().fireBallSize,
				cFireBall::getInstance().fireBallSize));
		addGameObject(fireball->at(i));
		meteorSummoned = false;
	}

	// convert int to char* for user display
	temp = std::to_string(cPlayer::getInstance().health);
	health = const_cast<char*>(temp.c_str());

	temp2 = std::to_string(cPlayer::getInstance().gasPoint);
	gas = const_cast<char*>(temp2.c_str());

	temp3 = std::to_string(cPlayer::getInstance().maxLatitude);
	latitude = const_cast<char*>(temp3.c_str());

	
	// player's camera 
	glMatrixMode(GL_PROJECTION); // render camera
	glLoadIdentity(); // reset/refresh projection sebelumnya

	visible_area.top = player->Y() + player->Height() + 250;
	visible_area.bottom = player->Y() - 250;
	visible_area.left = player->X() - 250;
	visible_area.right = player->X() + player->Width() + 250;
	
	glOrtho(visible_area.left, visible_area.right, visible_area.bottom, visible_area.top, 3, -101);
	glMatrixMode(GL_MODELVIEW); // scalling/translate model
	glLoadIdentity();
	
	//block collision
	for (int i = 0; i < block->size(); i++) {
		float x0, x1, y0, y1;

		x0 = block->at(i)->X();
		x1 = block->at(i)->X() + block->at(i)->Width();
		y0 = block->at(i)->Y();
		y1 = block->at(i)->Y() + block->at(i)->Height();

		player->blockCollision(x0, x1, y0, y1);
	}
	//gasoline collision
	for (int i = 0; i < gasoline->size(); i++) {
		float x0, x1, y0, y1;

		x0 = gasoline->at(i)->X();
		x1 = gasoline->at(i)->X() + gasoline->at(i)->Width();
		y0 = gasoline->at(i)->Y();
		y1 = gasoline->at(i)->Y() + gasoline->at(i)->Height();

		player->gasolineCollision(x0, x1, y0, y1, i);
	}

	// remove gas if get
	if (cPlayer::getInstance().gasolineGet == true) {
		removeGameObject(gasoline->at(cPlayer::getInstance().gasCollideAt));
	}

	//fireball collision
	for (int i = 0; i < fireball->size(); i++) {
		float x0, x1, y0, y1;

		x0 = fireball->at(i)->X();
		x1 = fireball->at(i)->X() + fireball->at(i)->Width();
		y0 = fireball->at(i)->Y();
		y1 = fireball->at(i)->Y() + fireball->at(i)->Height();

		player->fireBallCollision(x0, x1, y0, y1, i);
	}
	// remove fireball if hit
	if (cPlayer::getInstance().isHit == true ) {
		cPlayer::getInstance().health -= cFireBall::getInstance().fireBallDamage;
		removeGameObject(fireball->at(cPlayer::getInstance().fireBallCollideAt));
		cPlayer::getInstance().isHit = false;
		std::cout << cFireBall::getInstance().fireBallDamage;
	}
	
	//check gameOverScene condition
	player->goalCollision(110, 160, 2130, 2210);
	if (cPlayer::getInstance().health <= 0) 
		cGame::getInstance().UpdateScene(new cGameOverScene);
	

	if (cPlayer::getInstance().isGoal == true)
		cGame::getInstance().UpdateScene(new cGameOverScene);

	if (cPlayer::getInstance().gasPoint <= 0)
		cGame::getInstance().UpdateScene(new cGameOverScene);
}

void gameScene::ReadKeyboard(unsigned char key, int x, int y, bool press)
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

void gameScene::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	
	cScene::ReadSpecialKeyboard(key, x, y, press);
	if (press)
	{
		keys[key] = false;
	}
	else
	{
		keys[key] = false;
	}
}

void gameScene::ReadMouse(int button, int state, int x, int y)
{
	std::cout << x << " " << y << "\n";
}

void gameScene::gameSound() {
	
}


