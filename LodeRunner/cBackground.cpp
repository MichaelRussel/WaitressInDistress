// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cBackground.h"
#include "Globals.h"


cBackground::cBackground()
{
}


cBackground::~cBackground()
{
}

void cBackground::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, playerSheet->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(playerSheet->X0(), playerSheet->Y1());	glVertex3i(x, y, 50);
	glTexCoord2f(playerSheet->X1(), playerSheet->Y1());	glVertex3i(x + Width(), y, 50);
	glTexCoord2f(playerSheet->X1(), playerSheet->Y0());	glVertex3i(x + Width(), y + Height(), 50);
	glTexCoord2f(playerSheet->X0(), playerSheet->Y0());	glVertex3i(x, y + Height(), 50);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cBackground::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_forward", 0, 1, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_backward", 5, 6, 0.2f);
	animControl->AddAnim("NoLoop", "jump", 2, 2, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 4, 4, 0.2f);
}

void cBackground::Update(float tpf /*= 0.0333*/)
{

}

void cBackground::ReadKeyboard(unsigned char key, int x, int y, bool press)
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

void cBackground::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
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

void cBackground::ReadMouse(int button, int state, int x, int y)
{

}