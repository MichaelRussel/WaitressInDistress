// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#pragma once
#include"Globals.h"
#include "cSprite.h"
#include "cAnimation.h"
#include "cAnimControl.h"
#include "cGameObject.h"

class cGasoline :public cGameObject
{
private:
	cAnimControl *animControl;
	cSprite *Gasoline;
	float x, y;
	int width, height;
	bool keys[255];
public:
	cGasoline(cSprite *Gasoline, float x, float y, int width, int height)
		:Gasoline(Gasoline), x(x), y(y), width(width), height(height) {}
	cGasoline();
	~cGasoline();

	int Height() const { return height; }
	void Height(int val) { height = val; }
	int Width() const { return width; }
	void Width(int val) { width = val; }
	float X() const { return x; }
	void X(float val) { x = val; }
	float Y() const { return y; }
	void Y(float val) { y = val; }

	//void cGasoline::collision(float x0, float x1, float y0, float y1);

	// Inherited via cGameObject
	virtual void Render() override;
	virtual void Init() override;
	virtual void Update(float tpf = 0.0333) override;
	virtual void ReadKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadSpecialKeyboard(unsigned char key, int x, int y, bool press) override;
	virtual void ReadMouse(int button, int state, int x, int y) override;
};

