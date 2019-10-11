#pragma once
#include "Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "cGameObject.h"
#include "cScene.h"
#include "cRect.h"
#include "cPlayer.h"


class cFireBall :public cGameObject
{
private:
	cAnimControl *animControl;
	std::vector<cSprite*> *fireballSheet;
	float x, y;
	int width, height;
	bool keys[255];
	bool isLeft;
	bool fireBallSummoned = false;
	cRect visible_area;

public:
	int fireBallDamage;
	int fireBallSize;
	int fireBallSpawnedX;
	int fireBallSpawnedY;

	static cFireBall& getInstance()
	{
		static cFireBall instance;
		return instance;
	}
	cFireBall(std::vector<cSprite*> *fireballSheet, float x, float y, int width, int height)
		:fireballSheet(fireballSheet), x(x), y(y), width(width), height(height) {
		
		int temp = rand() % 2;
		if (temp == 1) {
			isLeft = true;
			cFireBall::getInstance().fireBallSpawnedX = 0;
		
		}
		else {
			isLeft = false;
			cFireBall::getInstance().fireBallSpawnedX = GAME_WIDTH;
		
		}
	}
	cFireBall();
	~cFireBall();

	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }

	void fireBallStats();

	// Inherited via cGameObject
	virtual void Render() override;
	virtual void Init() override;
	virtual void Update(float tpf = 0.0333) override;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadMouse(int button, int state, int x, int y) override;
};

