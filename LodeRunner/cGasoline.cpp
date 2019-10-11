// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cGasoline.h"

cGasoline::cGasoline()
{
}


cGasoline::~cGasoline()
{
}

void cGasoline::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, Gasoline->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(Gasoline->X0(), Gasoline->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(Gasoline->X1(), Gasoline->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(Gasoline->X1(), Gasoline->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(Gasoline->X0(), Gasoline->Y0());	glVertex3i(x, y + Height(), 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cGasoline::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_forward", 0, 1, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_backward", 5, 6, 0.2f);
	animControl->AddAnim("NoLoop", "jump", 2, 2, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 4, 4, 0.2f);
}

void cGasoline::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);

	if (keys[GLUT_KEY_RIGHT])
	{
		if (animControl->ActiveName() != "walk_forward")
			animControl->SetActiveAnim("walk_forward");
	}
	else if (keys[GLUT_KEY_LEFT])
	{
		if (animControl->ActiveName() != "walk_backward")
			animControl->SetActiveAnim("walk_backward");
	}
	else
	{
		if (animControl->ActiveName() != "idle")
			animControl->SetActiveAnim("idle");
	}

}

void cGasoline::ReadKeyboard(unsigned char key, int x, int y, bool press)
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

void cGasoline::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
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

void cGasoline::ReadMouse(int button, int state, int x, int y)
{

}

//void cGasoline::collision(float x0, float x1, float y0, float y1) {
//	float px0, px1, py0, py1;
//
//	px0 = x;
//	px1 = x + width;
//	py0 = y;
//	py1 = y + height;
//
//	if (px0 <= x1 && x0 <= px1 && py0 <= y1 && py1 >= y0) {
//		float diffLeft, diffRight, diffUp, diffDown;
//		diffLeft = abs(px0 - x1);
//		diffRight = abs(px1 - x0);
//		diffUp = abs(py1 - y0);
//		diffDown = abs(py0 - y1);
//
//		float min;
//
//		min = std::min({ diffLeft, diffRight, diffUp, diffDown });
//
//		if (min == diffLeft) {
//			x = x1;
//		}
//		else if (min == diffRight) {
//			x = x0 - width; // width selisih
//		}
//		else if (min == diffUp) {
//			y = y0 - height;
//		}
//		else {
//			y = y1;
//		}
//	}
//}