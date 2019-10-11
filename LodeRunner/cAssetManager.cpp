// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma warning(disable:4996)
#include "cAssetManager.h"
#include "Globals.h"

cAssetManager::cAssetManager(void) {}
cAssetManager::~cAssetManager(void) {}

int cAssetManager::GetID(int img)
{
	return textures[img].GetID();
}

void cAssetManager::GetSize(int img, int *w, int *h)
{
	textures[img].GetSize(w, h);
}

bool cAssetManager::LoadImage(int img, char *filename, int type)
{
	int res;

	res = textures[img].Load(filename, type);
	if (!res) return false;

	return true;
}
bool cAssetManager::Load()
{
	int res;
	int res2;
	int res3;
	int res4;
	int res5;

	// Load dari path
	res = LoadImage(SPRITESHEET_PLAYERS, "Textures/waiter.png", GL_RGBA);
	if (!res) return false;

	//split player sprite sheet
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 4; i++) {
			float x0, y0, x1, y1;
			int row = 2, col = 4;
			//GetSize(GetID(SPRITESHEET_PLAYERS), &tex_w, &tex_h);
			float sprite_width = 1.0f/col;
			float sprite_height = 1.0f/row;
			x0 = sprite_width*i;
			x1 = sprite_width*(i + 1);
			y0 = sprite_height*j;
			y1 = sprite_height*(j + 1);
			player->push_back(new cSprite(GetID(SPRITESHEET_PLAYERS), x0, y0, x1, y1));
		}
	}

	res5 = LoadImage(FIREBALL, "Textures/fireball.png", GL_RGBA);
	if (!res5) return false;
	//split fireball sprite sheet
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			float x0, y0, x1, y1;
			int row = 8, col = 8;
			//GetSize(GetID(SPRITESHEET_PLAYERS), &tex_w, &tex_h);
			float sprite_width = 1.0f / col;
			float sprite_height = 1.0f / row;
			x0 = sprite_width*i;
			x1 = sprite_width*(i + 1);
			y0 = sprite_height*j;
			y1 = sprite_height*(j + 1);
			fireball->push_back(new cSprite(GetID(FIREBALL), x0, y0, x1, y1));
		}
	}

	// Load  background
	res = LoadImage(BACKGROUND, "Textures/background.png", GL_RGBA);
	if (!res) return false;
	background = new cSprite(GetID(BACKGROUND), 0, 0, 1, 1);

	res2 = LoadImage(MENU_BACKGROUND, "Textures/menu_background.png", GL_RGBA);
	if (!res2) return false;
	menu_background = new cSprite(GetID(MENU_BACKGROUND), 0, 0, 1, 1);

	//load block
	res3 = LoadImage(BLOCK, "Textures/brick-block.png", GL_RGBA);
	if (!res3) return false;
	block = new cSprite(GetID(BLOCK), 0, 0, 1, 1);

	//load gasoline
	res4 = LoadImage(GASOLINE, "Textures/gas-sprite.png", GL_RGBA);
	if (!res4) return false;
	gasoline = new cSprite(GetID(GASOLINE), 0, 0, 1, 1);

	return true;
}

