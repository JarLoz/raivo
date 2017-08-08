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
	// Tick over the frame counter
	advanceCurrentFrame();
	// Do all input-related things
	handleInput();
	// Handle state changes based on animations ending
	if (currentAnimationOver()) {
		switch (state) {
			case GameObject::ATTACK_WINDUP:
				setState(GameObject::ATTACK);
				setCurrentAnimation(ANIMATIONS[PLAYER_ATTACK]);
				setCurrentFrame(0);
				setSpeed(PLAYER_SPEED*2);
				direction = attackDirection;
				break;
			case GameObject::ATTACK:
				setState(GameObject::IDLE);
				setCurrentAnimation(ANIMATIONS[PLAYER_IDLE]);
				setCurrentFrame(0);
				setSpeed(PLAYER_SPEED);
				break;
		}
	}
	// If animations still running, handle other triggers.
	else {
		switch (state) {
			// First 3 frames of attack animation move the player forwards towards the attack.
			case GameObject::ATTACK:
				if (currentFrame == 3) {
					setSpeed(0);
				}
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
	if (DRAW_HITBOXES) {
		target.draw(getHitCircle(sf::Color::Red));
		if (state == GameObject::ATTACK) {
			//hit circle for attacking
			float scaledRadius = PLAYER_ATTACK_SIZE * SCALE_FACTOR;
			sf::CircleShape circle;
			circle.setRadius(scaledRadius);
			circle.setOrigin(scaledRadius, scaledRadius);
			circle.setOutlineColor(sf::Color::Red);
			circle.setFillColor(sf::Color::Transparent);
			circle.setOutlineThickness(1);
			circle.setPosition(getDrawPosition(attackDirection*1.8f));

			target.draw(circle);
		}
	}

	//Draw the base sprite
	sf::Sprite objectSprite = AssetManager::getInstance()->getAnimationFrame(currentAnimation.id, currentFrame);
	Vec2 mouseDir = getRelativeMouseDirection();
	switch (state) {
		case GameObject::IDLE:
		case GameObject::MOVING:
			if (mouseDir.x < 0) {
				objectSprite.setScale(-1, 1);
			}
			break;
		case GameObject::ATTACK:
		case GameObject::ATTACK_WINDUP:
		case GameObject::ATTACK_COOLDOWN:
			if (attackDirection.x < 0) {
				objectSprite.setScale(-1, 1);
			}
			break;
	}
	objectSprite.setPosition(getDrawPosition());
	target.draw(objectSprite);



	//If attacking, draw the sword sprite
	if (state == GameObject::ATTACK) {
		sf::Sprite swordSprite = AssetManager::getInstance()->getAnimationFrame(PLAYER_SWORD_WHOOSH, currentFrame);
		// Flip the sprite around based on attack direction.
		if (attackDirection.x < 0) {
			swordSprite.setScale(1, -1);
		}
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

Vec2 PlayerObject::getRelativeMouseDirection() const
{
	return normalizeVec(InputManager::getInstance()->getMousePosition() - position);
}

void PlayerObject::handleInput()
{
	if (state == GameObject::IDLE || state == GameObject::MOVING || state == GameObject::ATTACK_WINDUP) {
		// Set the direction of movement
		direction = getDirection();
	}
	if (state == GameObject::IDLE || state == GameObject::MOVING) {
		// If attack input, initiate attack sequence
		if (InputManager::getInstance()->getMouseClickLeft()) {
			attackDirection = getRelativeMouseDirection();
			setState(GameObject::ATTACK_WINDUP);
			setCurrentAnimation(ANIMATIONS[PLAYER_ATTACK_WINDUP]);
			setCurrentFrame(0);
			setSpeed(PLAYER_SPEED / 2);
		}
	}
}
