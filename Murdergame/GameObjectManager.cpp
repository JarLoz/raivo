#include "GameObjectManager.h"
#include "Animation.h"



GameObjectManager*  GameObjectManager::getInstance()
{
	if (manager == NULL) {
		manager = new GameObjectManager();
	}

	return manager;
}

GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
	delete player;
	EnemyObjectList::iterator i = enemies.begin();
	while (i != enemies.end()) {
		delete *i;
		i = enemies.erase(i);
	}
}

void GameObjectManager::addPlayer(Vec2 position)
{
	player = new PlayerObject();
	player->setPosition(position);
	player->setSpeed(PLAYER_SPEED);
	player->setCurrentAnimation(ANIMATIONS.at(PLAYER_IDLE));
	player->setCurrentFrame(0);
}

PlayerObject * GameObjectManager::getPlayer()
{
	return player;
}

void GameObjectManager::addEnemy(Vec2 position)
{
	EnemyObject* enemy = new EnemyObject();
	enemy->setPosition(position);
	enemy->setSpeed(ENEMY_SPEED);
	enemy->setCurrentAnimation(ANIMATIONS.at(ENEMY_IDLE));
	enemy->setCurrentFrame(0);
	enemies.push_back(enemy);
}

EnemyObjectList* GameObjectManager::getEnemies()
{
	return &enemies;
}

void GameObjectManager::update()
{
	player->update();
	EnemyObjectList::iterator i = enemies.begin();
	while (i != enemies.end()) {
		GameObject* current = *i;
		current->update();
		i++;
	}
}
