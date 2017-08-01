#include "PlayerObject.h"
#include "GameObjectManager.h"
#include "InputManager.h"


PlayerObject::PlayerObject()
	: GameObject()
{
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::update()
{
	advanceCurrentFrame();
	handleInput();
	if (state == GameObject::ATTACK_WINDUP && currentAnimationOver()) {
		setState(GameObject::IDLE);
		setCurrentAnimation(ANIMATIONS[PLAYER_IDLE]);
		setCurrentFrame(0);
	}
}

void PlayerObject::updatePosition()
{
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
	Vec2 newDirection = InputManager::getInstance()->getDirection();
	bool hasMovementInput = (newDirection != VEC_NULL);
	if (hasMovementInput && acceleration < 1.f) {
		acceleration += PLAYER_ACCELERATION_INCREMENT;
	}
	if(!hasMovementInput && acceleration > 0.f) {
		acceleration -= PLAYER_ACCELERATION_INCREMENT;
	}
	return newDirection * acceleration;
}

void PlayerObject::handleInput()
{
	if (state == GameObject::IDLE || state == GameObject::MOVING) {
		// Set the direction of movement
		direction = getDirection();
		if (InputManager::getInstance()->getMouseClickLeft()) {
			direction = VEC_NULL;
			setState(GameObject::ATTACK_WINDUP);
			setCurrentAnimation(ANIMATIONS[PLAYER_ATTACK_WINDUP]);
			setCurrentFrame(0);
		}
	}
}
