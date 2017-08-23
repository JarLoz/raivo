#pragma once
#include "Main.h"
class SoundManager
{
	sf::SoundBuffer playerSwordSwingBuffer;
	sf::SoundBuffer playerSwordHitBuffer;
	sf::Sound playerSwordSwing;
	sf::Sound playerSwordHit;
public:
	SoundManager();
	~SoundManager();

	static SoundManager* manager;
	static SoundManager* getInstance();

	void loadSounds();
	void playPlayerSwordSwing();
	void playPlayerSwordHit();
};

