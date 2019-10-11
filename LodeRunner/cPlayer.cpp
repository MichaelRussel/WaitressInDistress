// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cPlayer.h"



cPlayer::cPlayer()
{
	
}


cPlayer::~cPlayer()
{
}
bool faceLeft;
void cPlayer::Render()
{
	if (keys[GLUT_KEY_RIGHT]) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
		glBegin(GL_QUADS);
		glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	else if (keys[GLUT_KEY_LEFT]) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
		glBegin(GL_QUADS);
		glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width()/2, y, 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x - Width(), y, 49);

		glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x - Width(), y + Height(), 49);
		glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width()/2, y + Height(), 49);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		faceLeft = true;
	}
	else {
		if (faceLeft == true) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
			glBegin(GL_QUADS);
			glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width() / 2, y, 49);
			glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x - Width(), y, 49);
			glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x - Width(), y + Height(), 49);
			glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width() / 2, y + Height(), 49);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		else {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, playerSheet->at(animControl->Index())->Texture());
			glBegin(GL_QUADS);
			glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x, y, 49);
			glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y1());	glVertex3i(x + Width(), y, 49);
			glTexCoord2f(playerSheet->at(animControl->Index())->X1(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x + Width(), y + Height(), 49);
			glTexCoord2f(playerSheet->at(animControl->Index())->X0(), playerSheet->at(animControl->Index())->Y0());	glVertex3i(x, y + Height(), 49);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		
	}
		
}

void cPlayer::Init()
{
	animControl = new cAnimControl();
	animControl->AddAnim("StraightLoop", "walk_forward", 4, 7, 0.2f);
	animControl->AddAnim("StraightLoop", "walk_backward", 4, 7, 0.2f);
	animControl->AddAnim("StraightLoop", "jump", 0, 3, 0.2f);
	animControl->AddAnim("StraightLoop", "idle", 4, 7, 0.2f);
}

bool gasUsed = true;
void gasUsage(int value) {

	cPlayer::getInstance().gasPoint -= 8;
	if (gasUsed == false) {
		gasUsed = true;
	}
}

void cPlayer::Update(float tpf /*= 0.0333*/)
{
	animControl->UpdateAnim(tpf);
	
	if (isGround == false) {
		y -= 1;
	}
	else
		y = y;

	if (keys[GLUT_KEY_UP])
	{
		if (animControl->ActiveName() != "jump")
			animControl->SetActiveAnim("jump");
	}
	else if (keys[GLUT_KEY_RIGHT])
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
	if (keys[GLUT_KEY_LEFT] && isGround == false) {
		x -= 5;
	}
	if (keys[GLUT_KEY_RIGHT] && isGround == false) {
		x += 5;
	}
	if (keys[GLUT_KEY_UP] ) {
		// count maximum latitude
		cPlayer::getInstance().latitude = y - 156; // kurangi jarak dari ground agar 0
		if (cPlayer::getInstance().latitude >= cPlayer::getInstance().maxLatitude)
			cPlayer::getInstance().maxLatitude = cPlayer::getInstance().latitude;
		isGround = false;
		//gas usage 8/second
		if (gasUsed == true) {
			glutTimerFunc(1000, gasUsage, 0);
			gasUsed = false;
		}
		// goes up by 5
		y += 5;
	}
	
	if (keys[GLUT_KEY_DOWN]) {
		y -= 5;
	}

}

void cPlayer::ReadKeyboard(unsigned char key, int x, int y, bool press)
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

void cPlayer::ReadSpecialKeyboard(unsigned char key, int x, int y, bool press)
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

void cPlayer::ReadMouse(int button, int state, int x, int y)
{

}

void cPlayer::blockCollision(float x0, float x1, float y0, float y1) {
	float px0, px1, py0, py1;

	px0 = x;
	px1 = x + width;
	py0 = y;
	py1 = y + height;

	if (px0 <= x1 && x0 <= px1 && py0 <= y1 && py1 >= y0) {
		float diffLeft, diffRight, diffUp, diffDown;
		diffLeft = abs(px0 - x1); 
		diffRight = abs(px1 - x0);
		diffUp = abs(py1 - y0);
		diffDown = abs(py0 - y1);

		float min;

		min = std::min({ diffLeft, diffRight, diffUp, diffDown }); 

		if (min == diffLeft) { 
			x = x1;
		}
		else if (min == diffRight) {
			x = x0 - width; // width selisih
		}
		else if (min == diffUp) {
			y = y0 - height;
		}
		else {
			y = y1;
			isGround = true;
		}
	}
}

void cPlayer::gasolineCollision(float x0, float x1, float y0, float y1, int i) {
	float px0, px1, py0, py1;

	px0 = x;
	px1 = x + width;
	py0 = y;
	py1 = y + height;

	if (px0 <= x1 && x0 <= px1 && py0 <= y1 && py1 >= y0) {
		float diffLeft, diffRight, diffUp, diffDown;
		diffLeft = abs(px0 - x1);
		diffRight = abs(px1 - x0);
		diffUp = abs(py1 - y0);
		diffDown = abs(py0 - y1);

		float min;

		min = std::min({ diffLeft, diffRight, diffUp, diffDown });

		if (min == diffLeft && gasolineGet == false) 
			gasolineGet = true;
		else if (min == diffDown && gasolineGet == false)
			gasolineGet = true;
		else if (min == diffUp && gasolineGet == false)
			gasolineGet = true;
		else if (min == diffRight && gasolineGet == false)
			gasolineGet = true;
		else if(gasolineGet == true) {
			cPlayer::getInstance().gasPoint += 50;
			cPlayer::getInstance().gasolineGet = gasolineGet;
		}
		cPlayer::getInstance().gasCollideAt = i;

		//std::cout << "\n" << cPlayer::getInstance().gasPoint << " ";
	}
}

void cPlayer::goalCollision(float x0, float x1, float y0, float y1) {
	float px0, px1, py0, py1;

	px0 = x;
	px1 = x + width;
	py0 = y;
	py1 = y + height;
	
	if (px0 <= x1 && x0 <= px1 && py0 <= y1 && py1 >= y0) {
		float diffLeft, diffRight, diffUp, diffDown;
		diffLeft = abs(px0 - x1);
		diffRight = abs(px1 - x0);
		diffUp = abs(py1 - y0);
		diffDown = abs(py0 - y1);

		float min;

		min = std::min({ diffLeft, diffRight, diffUp, diffDown });

		if (min == diffLeft)
			isGoal = true;
		else if (min == diffDown)
			isGoal = true;
		else if (min == diffUp)
			isGoal = true;
		else if (min == diffRight)
			isGoal = true;

		cPlayer::getInstance().isGoal = isGoal;
		
	}
}

void cPlayer::fireBallCollision(float x0, float x1, float y0, float y1, int i) {
	float px0, px1, py0, py1;

	px0 = x;
	px1 = x + width;
	py0 = y;
	py1 = y + height;

	if (px0 <= x1 && x0 <= px1 && py0 <= y1 && py1 >= y0) {
		float diffLeft, diffRight, diffUp, diffDown;
		diffLeft = abs(px0 - x1);
		diffRight = abs(px1 - x0);
		diffUp = abs(py1 - y0);
		diffDown = abs(py0 - y1);

		float min;

		min = std::min({ diffLeft, diffRight, diffUp, diffDown });

		if (min == diffLeft && isHit == false)
			isHit = true;
		else if (min == diffDown && isHit == false)
			isHit = true;
		else if (min == diffUp && isHit == false)
			isHit = true;
		else if (min == diffRight && isHit == false)
			isHit = true;
		else if (isHit == true) {
			//cPlayer::getInstance().health -= 100;
			cPlayer::getInstance().isHit = isHit;
		}
	
		cPlayer::getInstance().fireBallCollideAt = i;
		//std::cout << "\n" << cPlayer::getInstance().gasPoint << " ";
	}
}