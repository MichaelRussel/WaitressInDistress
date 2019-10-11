// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
#include "cScene.h"
#include "cPlayer.h"
#include "cRect.h"
#include "cBackground.h"
#include "cBlock.h"
#include "cGasoline.h"
#include "cFireBall.h"

#define TOTAL_TILE_Y 18
#define TOTAL_TILE_X 1000
#define TILE_SIZE 64
#define TEXTURE_TILE_SIZE 128


class gameScene :public cScene
{
public:
	static gameScene& getInstance()
	{
		static gameScene instance;
		return instance;
	}

	gameScene();
	~gameScene();
	cPlayer *player;
	cBackground *background;
	std::vector<cBlock*> *block = new std::vector<cBlock*>;
	std::vector<cGasoline*> *gasoline = new std::vector<cGasoline*>;
	std::vector<cFireBall*> *fireball = new std::vector<cFireBall*>;
	cRect visible_area;

	virtual void Render();

	virtual void Init();

	virtual void Update(float tpf);

	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadMouse(int button, int state, int x, int y);

	void gameSound();

	bool soundCondition;

	//virtual void ChangeScene();


private:
	bool keys[255];
	std::string map;
	std::string temp;
	std::string temp2;
	std::string temp3;
	char* health;
	char* gas;
	char* latitude;
};

