
#include "Main.h"
#include "GameObject.h"
#include "PlayerObject.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "Globals.h"

// Initializing singleton pointers.
AssetManager* AssetManager::manager = NULL;
GameObjectManager* GameObjectManager::manager = NULL;
InputManager* InputManager::manager = NULL;
Vec2 cameraPosition(0.f,0.f);

int main()
{

	// Initialize render target
	sf::RenderWindow window(sf::VideoMode(RESOLUTION_X,RESOLUTION_Y), "Raivo");
	window.setFramerateLimit(TICKRATE);
	window.setMouseCursorGrabbed(true);
	window.setMouseCursorVisible(false);

	// Load assets;
	AssetManager::getInstance()->loadAssets();

	// Initialize player object
	GameObjectManager* gameObjectManager = GameObjectManager::getInstance();
	gameObjectManager->addPlayer(Vec2(0, 0));
	// Initialize one enemy
	gameObjectManager->addEnemy(Vec2(2, 3));
	gameObjectManager->addEnemy(Vec2(2, 5.5f));

	// Gameloop
	while (window.isOpen())
	{
		//Check if window is to be closed
		if (InputManager::getInstance()->closeGame(window)) {
				window.close();
		}

		// Do the updates
		gameObjectManager->update();
		// Draw the objects
		window.clear();
		EnemyObjectList::const_iterator i = gameObjectManager->getEnemies()->begin();
		while (i != gameObjectManager->getEnemies()->end()) {
			EnemyObject* enemy = *i;
			window.draw(*enemy);
			i++;
		}
		window.draw(*gameObjectManager->getPlayer());

		//Draw mouse pointer
		sf::CircleShape mousePointer;
		mousePointer.setRadius(1.f);
		mousePointer.setFillColor(sf::Color::Blue);
		Vec2 mousePosition = InputManager::getInstance()->getMousePosition(window);
		Vec2 drawPosition = (mousePosition - cameraPosition) * SCALE_FACTOR;
		drawPosition.x += RESOLUTION_X / 2;
		drawPosition.y = RESOLUTION_Y / 2 - drawPosition.y;

		mousePointer.setPosition(drawPosition.x,drawPosition.y);
		window.draw(mousePointer);

		window.display();
	}

	return 0;
}
