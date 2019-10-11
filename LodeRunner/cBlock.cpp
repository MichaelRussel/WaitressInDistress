// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cBlock.h"

cBlock::cBlock()
{
}


cBlock::~cBlock()
{
}

void cBlock::Render()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, block->Texture());
	glBegin(GL_QUADS);

	glTexCoord2f(block->X0(), block->Y1());	glVertex3i(x, y, 49);
	glTexCoord2f(block->X1(), block->Y1());	glVertex3i(x + Width(), y, 49);
	glTexCoord2f(block->X1(), block->Y0());	glVertex3i(x + Width(), y + Height(), 49);
	glTexCoord2f(block->X0(), block->Y0());	glVertex3i(x, y + Height(), 49);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void cBlock::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_forward", 0, 1, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_backward", 5, 6, 0.2f);
	animControl->AddAnim("NoLoop", "jump", 2, 2, 0.2f);
	animControl->AddAnim("NoLoop", "idle", 4, 4, 0.2f);
}

void cBlock::Update(float tpf /*= 0.0333*/)
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

void cBlock::ReadKeyboard(unsigned char key, int x, int y, bool press)
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

void cBlock::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
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

void cBlock::ReadMouse(int button, int state, int x, int y)
{

}