#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

SoundManager * SoundManager::getInstance()
{
	if (!manager) {
		manager = new SoundManager();
	}
	return manager;
}

void SoundManager::loadSounds()
{
	playerSwordSwingBuffer.loadFromFile(ASSET_PATH + "sword_whoosh.wav");
	playerSwordSwing.setBuffer(playerSwordSwingBuffer);

	playerSwordHitBuffer.loadFromFile(ASSET_PATH + "sword_hit.wav");
	playerSwordHit.setBuffer(playerSwordHitBuffer);
}

void SoundManager::playPlayerSwordSwing()
{
	playerSwordSwing.play();
}

void SoundManager::playPlayerSwordHit()
{
	playerSwordHit.play();
}
