#include "AssetManager.h"



AssetManager * AssetManager::getInstance()
{
	if (manager == NULL) {
		manager = new AssetManager();
	}
	return manager;
}

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}

void AssetManager::loadAssets()
{
	playerTexture.loadFromFile(ASSET_PATH + "hero.png");
	enemyTexture.loadFromFile(ASSET_PATH + "enemy.png");
	font.loadFromFile(ASSET_PATH + "arial.ttf");
}

sf::Sprite AssetManager::getAnimationFrame(AnimationId animId, int frame)
{
	Animation animation = ANIMATIONS[animId];
	int framenumber = frame / animation.speed;

	sf::Sprite frameSprite;

	switch (animId) {
	case AnimationId::PLAYER_IDLE :
	case AnimationId::PLAYER_ATTACK_WINDUP:
	case AnimationId::PLAYER_ATTACK:
	case AnimationId::PLAYER_SWORD_WHOOSH:
		frameSprite.setTexture(playerTexture);
		break;
	case AnimationId::ENEMY_IDLE :
		frameSprite.setTexture(enemyTexture);
		break;
	}

	frameSprite.setOrigin(animation.originx, animation.originy);
	frameSprite.setTextureRect(sf::IntRect((framenumber)*animation.width, animation.textureOffset, animation.width, animation.height));

	return frameSprite;
}

sf::Font AssetManager::getFont()
{
	return font;
}
