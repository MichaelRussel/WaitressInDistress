// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cFireBall.h"
#include "Globals.h"


cFireBall::cFireBall()
{
}


cFireBall::~cFireBall()
{
}

void cFireBall::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, fireballSheet->at(animControl->Index())->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(fireballSheet->at(animControl->Index())->X0(), fireballSheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(fireballSheet->at(animControl->Index())->X1(), fireballSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(fireballSheet->at(animControl->Index())->X1(), fireballSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(fireballSheet->at(animControl->Index())->X0(), fireballSheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cFireBall::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "fireball_left", 0, 7, 0.2f);
	animControl->AddAnim("StraightLoop", "fireball_right", 32, 39, 0.2f);
	
}

void cFireBall::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);
	if (cFireBall::getInstance().fireBallSummoned && cFireBall::getInstance().fireBallSpawnedX == 600) {
		if (animControl->ActiveName() != "fireball_left")
			animControl->SetActiveAnim("fireball_left");
		x -= 5;
	}
	else {
		if (animControl->ActiveName() != "fireball_right")
			animControl->SetActiveAnim("fireball_right");
		x += 5;
	}
}

void cFireBall::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cFireBall::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
{
	if (press)
	{
		keys[key] = true;
	}
	else
	{
		keys[key] = false;
	}
}

void cFireBall::ReadMouse(int button, int state, int x, int y)
{

}

void cFireBall::fireBallStats() {
	cFireBall::getInstance().fireBallSummoned = true;

	srand(time(NULL));

	cFireBall::getInstance().fireBallSize = rand() % 32 + 64;
	std::cout << cFireBall::getInstance().fireBallSize << "\n";
	//if fireball size small then damage small, viceversa.
	if (cFireBall::getInstance().fireBallSize >= 32 && cFireBall::getInstance().fireBallSize <= 48) {
		cFireBall::getInstance().fireBallDamage = rand() % 3 + 4;
		std::cout << "small";
	}
	else if (cFireBall::getInstance().fireBallSize >= 49){
		cFireBall::getInstance().fireBallDamage = rand() % 8 + 7;
		std::cout << "big";
	}

	int temp = rand() % 2;
	if (temp == 0)
		cFireBall::getInstance().fireBallSpawnedX = 0;
	else
		cFireBall::getInstance().fireBallSpawnedX = 900;

	cFireBall::getInstance().fireBallSpawnedY = rand() % (2200 - 200 + 1);
}