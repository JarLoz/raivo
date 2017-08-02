#include "InputManager.h"



InputManager * InputManager::getInstance()
{
	if (manager == NULL) {
		manager = new InputManager();
	}
	return manager;
}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::updateInputs(const sf::Window & relativeTo)
{
	// Get keyboard input, set direction.
	Vec2 newDirection = VEC_NULL;
	if (sf::Keyboard::isKeyPressed(MOVE_RIGHT)) {
		newDirection += VEC_RIGHT;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_LEFT)) {
		newDirection += VEC_LEFT;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_UP)) {
		newDirection += VEC_UP;
	}
	if (sf::Keyboard::isKeyPressed(MOVE_DOWN)) {
		newDirection += VEC_DOWN;
	}
	movementDirection = normalizeVec(newDirection);

	// Find mouse position
	Vec2 mousePositionInPixels(sf::Mouse::getPosition(relativeTo));

	mousePositionInPixels.x -= RESOLUTION_X / 2;
	mousePositionInPixels.y = RESOLUTION_Y / 2 - mousePositionInPixels.y;
	mousePosition = (mousePositionInPixels / SCALE_FACTOR) + cameraPosition;


	// Get mouse button states.
	bool currentState = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (currentState && !mousePressedLeft) {
		mousePressedLeft = true;
		mouseClickLeft = true;
	} else {
		mousePressedLeft = currentState;
		mouseClickLeft = false;
	}
	currentState = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	if (currentState && !mousePressedRight) {
		mousePressedRight = true;
		mouseClickRight = true;
	} else {
		mousePressedRight = currentState;
		mouseClickRight = false;
	}
}

Vec2 InputManager::getDirection()
{
	return movementDirection;
}

Vec2 InputManager::getMousePosition()
{
	return mousePosition;
}

bool InputManager::getMouseClickLeft()
{
	return mouseClickLeft;
}

bool InputManager::getMouseClickRight()
{
	return mouseClickRight;
}

bool InputManager::getAttack()
{
	return getMouseClickLeft();
}

bool InputManager::closeGame(sf::Window & window)
{
		//Check window events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return true;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			return true;
		}
	return false;
}
