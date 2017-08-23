#pragma once
#include "Main.h"
#include "Animation.h"

class AssetManager
{
	static AssetManager* manager;
	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Font font;
	sf::SoundBuffer playerSwordSwing;
public:
	static AssetManager* getInstance();
	AssetManager();
	~AssetManager();
	void loadAssets();
	sf::Sprite getAnimationFrame(AnimationId animId, int frame);
	sf::Font getFont();
	sf::Sound getPlayerSwordSwingSound();
};

