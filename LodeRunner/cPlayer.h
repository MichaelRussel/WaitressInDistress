// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include"Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "cGameObject.h"
#include "cGameOverScene.h"
#include "cGame.h"

class cPlayer:public cGameObject
{
private:
	cAnimControl *animControl;
	std::vector<cSprite*> *playerSheet;
	float x, y;
	int width, height;
	bool keys[255];
public:
	static cPlayer& getInstance()
	{
		static cPlayer instance;
		return instance;
	}

	cPlayer(std::vector<cSprite*> *playerSheet, float x, float y, int width, int height)
		:playerSheet(playerSheet), x(x), y(y), width(width), height(height) {}
	cPlayer();
	~cPlayer();

	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }
	
	//static void gasUsage(int value);

	int health = 100;
	int gasPoint = 100;
	int latitude = 0;
	int maxLatitude = 0;
	int gasCollideAt;
	int fireBallCollideAt;
	bool isGround = false;
	bool gasolineGet = false;
	bool isGoal = false;
	bool isHit = false;

	void cPlayer::blockCollision(float x0, float x1, float y0, float y1);
	void cPlayer::gasolineCollision(float x0, float x1, float y0, float y1, int i);
	void cPlayer::goalCollision(float x0, float x1, float y0, float y1);
	void cPlayer::fireBallCollision(float x0, float x1, float y0, float y1,int i);
	// Inherited via cGameObject
	virtual void Render() override;
	virtual void Init() override;
	virtual void Update(float tpf = 0.0333) override;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadMouse(int button, int state, int x, int y) override;
	
};


