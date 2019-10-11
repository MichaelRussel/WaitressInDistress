// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include "Globals.h"
#include "cScene.h"
#include "cRect.h"
#include "cGasoline.h"



#define TOTAL_TILE_Y 18
#define TOTAL_TILE_X 1000
#define TILE_SIZE 64
#define BLOCK_SIZE 32
#define TEXTURE_TILE_SIZE 128


class cGameOverScene :public cScene
{
public:
	std::vector<cGasoline*> *gasoline = new std::vector<cGasoline*>;

	static cGameOverScene& getInstance()
	{
		static cGameOverScene instance;
		return instance;
	}

	cGameOverScene();
	~cGameOverScene();


	bool soundCondition = true;

	virtual void Render();

	virtual void Init();

	virtual void Update(float tpf = 0.0333);

	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press);

	virtual void ReadMouse(int button, int state, int x, int y);



private:
	bool keys[255];
	std::string temp;
	std::string temp2;
	char *highScore;
	char *totalScore;
	int totalHighScore;
	int currHighScore;
};

