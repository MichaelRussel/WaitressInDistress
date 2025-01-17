// Copyright 2015 Kelvin Chandra, Software Laboratory Center, Binus University. All Rights Reserved.
#include "cSound.h"


cSound::cSound(void)
{
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

cSound::~cSound(void)
{
	for (int i = 0; i < NUM_SOUNDS; i++) sounds[i]->release();
	system->release();
}

bool cSound::Load()
{
	system->createStream("Sounds/03_-_Lode_Runner_-_NES_-_In-Game.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT1]);
	system->createStream("Sounds/menu_music.mp3", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT2]);
	system->createStream("Sounds/in_game.ogg", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT3]);
	system->createStream("Sounds/fireball.wav", FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT4]);
	return true;
}

void cSound::Play(int sound_id)
{
	if (sound_id == SOUND_AMBIENT1) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT1], false, &ambient1Channel);
		ambient1Channel->setVolume(0.25f); //between 0 and 1
	}
	else if (sound_id == SOUND_AMBIENT2) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT2], false, &ambient2Channel);
		ambient2Channel->setVolume(0.4f); //between 0 and 1
	}
	else if (sound_id == SOUND_AMBIENT3) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT3], false, &ambient3Channel);
		ambient3Channel->setVolume(0.4f); //between 0 and 1
	}
	else if (sound_id == SOUND_AMBIENT4) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT4], false, &ambient4Channel);
		ambient4Channel->setVolume(0.6f); //between 0 and 1
	}

	else system->playSound(FMOD_CHANNEL_FREE, sounds[sound_id], false, 0);
}

void cSound::StopAll()
{
	ambient1Channel->stop();
	ambient2Channel->stop();
}

void cSound::Update()
{
	system->update();
}

void cSound::Pause(int sound_id)
{
	bool soundCondition;
	if (sound_id == SOUND_AMBIENT1) {
		ambient1Channel->getPaused(&soundCondition);
		ambient1Channel->setPaused(!soundCondition);
	}
	else if (sound_id == SOUND_AMBIENT2) {
		ambient2Channel->getPaused(&soundCondition);
		ambient2Channel->setPaused(!soundCondition);
	}
	else if (sound_id == SOUND_AMBIENT3) {
		ambient3Channel->getPaused(&soundCondition);
		ambient3Channel->setPaused(!soundCondition);
	}
	else if (sound_id == SOUND_AMBIENT4) {
		ambient4Channel->getPaused(&soundCondition);
		ambient4Channel->setPaused(!soundCondition);
	}
}