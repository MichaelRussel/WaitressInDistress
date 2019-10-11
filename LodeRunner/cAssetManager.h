// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cSprite.h"

//Image array size
#define NUM_TEX		 100
//Image identifiers
#define SPRITESHEET_PLAYERS	1
#define BLOCK 1
#define BACKGROUND 2
#define MENU_BACKGROUND 2
#define GASOLINE 3
#define FIREBALL 4

class cAssetManager
{
public:
	static cAssetManager& getInstance()
	{
		static cAssetManager instance;
		return instance;
	}

	int  GetID(int img);
	void GetSize(int img, int *w, int *h);
	bool Load();

	std::vector<cSprite*> *player = new std::vector<cSprite*>;
	cSprite *background = new cSprite();
	cSprite *menu_background = new cSprite();
	cSprite *block = new cSprite();
	cSprite *gasoline = new cSprite();
	std::vector<cSprite*> *fireball = new std::vector<cSprite*>;

private:
	~cAssetManager(void);
	cAssetManager(void);
	cAssetManager(cAssetManager const&) = delete;
	void operator=(cAssetManager const&) = delete;


	cTexture textures[NUM_TEX];
	bool LoadImage(int img, char *filename, int type = GL_RGBA);
};
