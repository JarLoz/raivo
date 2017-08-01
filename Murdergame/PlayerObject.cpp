#include "PlayerObject.h"
#include "GameObjectManager.h"


PlayerObject::PlayerObject()
	: GameObject()
{
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::update()
{
	// Set the direction of movement
	direction = getDirection();

	// Update position. 

	// Calculate new position without collisions.
	Vec2 newPosition = position + direction * speed;

	// Loop through enemies
	GameObjectManager* gameObjectManager = GameObjectManager::getInstance();
	EnemyObjectList::const_iterator i = gameObjectManager->getEnemies()->begin();
	while (i != gameObjectManager->getEnemies()->end()) {
		EnemyObject* enemy = *i;
		// If collision, move the player outside the enemy hitbox (or circle).
		if (isColliding(newPosition, radius, enemy->position, enemy->radius)) {
			float collisionDistance = (getDistanceVec(newPosition, enemy->position) - radius - enemy->radius) * -1.f;
			Vec2 nudge = setLengthVec(normalizeVec(newPosition - enemy->position),collisionDistance);
			newPosition += nudge;
		}
		i++;
	}

	// Set the new position.
	position = newPosition;

}

Vec2 PlayerObject::getDirection()
{
	// Get keyboard input, set direction.
	bool hasMovementInput = false;
	Vec2 newDirection = VEC_NULL;
	if (sf::Keyboard::isKeyPressed(MOVE_RIGHT)) {
		newDirection += VEC_RIGHT;
		hasMovementInput = true;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_LEFT)) {
		newDirection += VEC_LEFT;
		hasMovementInput = true;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_UP)) {
		newDirection += VEC_UP;
		hasMovementInput = true;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_DOWN)) {
		newDirection += VEC_DOWN;
		hasMovementInput = true;
	}
	if (hasMovementInput && acceleration < 1.f) {
		acceleration += PLAYER_ACCELERATION_INCREMENT;
	}
	if(!hasMovementInput && acceleration > 0.f) {
		acceleration -= PLAYER_ACCELERATION_INCREMENT;
	}
	if (hasMovementInput) {
		return normalizeVec(newDirection) * acceleration;
	}
	else {
		return direction * acceleration;
	}
}
