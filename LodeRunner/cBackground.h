#pragma once
#include"Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "cGameObject.h"
#include "cScene.h"
#include "cRect.h"
#include "cPlayer.h"


class cBackground :public cGameObject
{
private:
	cAnimControl *animControl;
	cSprite *playerSheet;
	float x, y;
	int width, height;
	bool keys[255];
	cRect visible_area;
	cPlayer *player;
public:
	cBackground(cSprite *playerSheet, float x, float y, int width, int height)
		:playerSheet(playerSheet), x(x), y(y), width(width), height(height) {}
	cBackground();
	~cBackground();

	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }

	// Inherited via cGameObject
	virtual void Render() override;
	virtual void Init() override;
	virtual void Update(float tpf = 0.0333) override;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadMouse(int button, int state, int x, int y) override;
};

