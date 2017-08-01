#pragma once
#include "Main.h"
#include "Animation.h"
#include "AssetManager.h"
class GameObject: public sf::Drawable
{
public:
	enum State {IDLE,MOVING,ATTACK_WINDUP,ATTACK,ATTACK_COOLDOWN};
	// State of the object
	State state;
	// Position of the object in the gameworld. Scale about 1 unit per half a metre, essentially width of the hero sprite
	Vec2 position;
	// Direction of movement. Unit vector, the object moves this times speed per update() call.
	Vec2 direction;
	// Radius of hitbox.
	float radius;
	// Speed, in units / frame.
	float speed;
	// Used for acceleration, values 0-1
	float acceleration;

	Animation currentAnimation;
	int currentFrame;

	GameObject();
	~GameObject();
	// Updates the object state. Called once per frame.
	void update();
	void updatePosition();
	void setState(State newState);
	void setPosition(Vec2);
	void setDirection(Vec2);
	void setRadius(float);
	void setSpeed(float);
	void setCurrentAnimation(Animation);
	void setCurrentFrame(int);
	void advanceCurrentFrame();
	bool currentAnimationOver();

	// Implementing sf::Drawable
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Do the ingame units -> pixel coordinates conversion.
	Vec2 getDrawPosition() const;
	sf::CircleShape getHitCircle(sf::Color color) const;
};


