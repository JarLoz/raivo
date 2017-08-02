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
	if (currentAnimationOver()) {
		switch (state) {
			case GameObject::ATTACK_WINDUP:
				setState(GameObject::ATTACK);
				setCurrentAnimation(ANIMATIONS[PLAYER_ATTACK]);
				setCurrentFrame(0);
				break;
			case GameObject::ATTACK:
				setState(GameObject::IDLE);
				setCurrentAnimation(ANIMATIONS[PLAYER_IDLE]);
				setCurrentFrame(0);
				break;
		}
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

void PlayerObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//Draw the base sprite
	GameObject::draw(target, states);
	//If attacking, draw the sword sprite
	if (state == GameObject::ATTACK) {
		sf::Sprite swordSprite = AssetManager::getInstance()->getAnimationFrame(PLAYER_SWORD_WHOOSH, currentFrame);
		swordSprite.setPosition(getDrawPosition(attackDirection * 1.8f));
		float angle = atan2(attackDirection.y, attackDirection.x) * (180.f / 3.14f) * -1.f;
		swordSprite.setRotation(angle);
		target.draw(swordSprite);
	}
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
		// If attack input, initiate attack sequence
		if (InputManager::getInstance()->getMouseClickLeft()) {
			direction = VEC_NULL;
			attackDirection = normalizeVec(InputManager::getInstance()->getMousePosition() - position);
			std::cout << "AttackDirection x: " << attackDirection.x << " y: " << attackDirection.y << "\n";
			setState(GameObject::ATTACK_WINDUP);
			setCurrentAnimation(ANIMATIONS[PLAYER_ATTACK_WINDUP]);
			setCurrentFrame(0);
		}
	}
}
