#pragma once
#include "Main.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "EnemyObject.h"

typedef std::list<GameObject*> GameObjectList;
typedef std::list<EnemyObject*> EnemyObjectList;
// GameObjectManager acts as a container for GameObjects.
class GameObjectManager
{
public:
	EnemyObjectList enemies;
	PlayerObject* player;

	static GameObjectManager* manager;
	static GameObjectManager* getInstance();
	GameObjectManager();
	~GameObjectManager();

	void addPlayer(Vec2 position);
	void addEnemy(Vec2 position);
	PlayerObject* getPlayer();
	EnemyObjectList* getEnemies();

	void update();
};

