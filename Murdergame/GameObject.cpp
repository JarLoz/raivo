#include "GameObject.h"
#include "Globals.h"



GameObject::GameObject()
{
	acceleration = 0.f;
	radius = 1.f;
	direction = VEC_NULL;
}


GameObject::~GameObject()
{
}

void GameObject::update()
{
	advanceCurrentFrame();
}

void GameObject::updatePosition()
{
	position += direction * speed;
}

void GameObject::setState(State newState)
{
	state = newState;
}

void GameObject::setPosition(Vec2 pos)
{
	position = pos;
}

void GameObject::setDirection(Vec2 d)
{
	direction = d;
}

void GameObject::setRadius(float r)
{
	radius = r;
}

void GameObject::setSpeed(float s)
{
	speed = s;
}

void GameObject::setCurrentAnimation(Animation anim)
{
	currentAnimation = anim;
}

void GameObject::setCurrentFrame(int f)
{
	currentFrame = f;
}

void GameObject::advanceCurrentFrame()
{
	currentFrame++;
	if (currentAnimationOver()) {
		if (currentAnimation.loop) {
			currentFrame = 0;
		}
	}
}

bool GameObject::currentAnimationOver()
{
	if (currentFrame > currentAnimation.speed - 1) {
		return true;
	}
	return false;
}

void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const 
{
	if (DRAW_HITBOXES) {
		target.draw(getHitCircle(sf::Color::Red));
	}
	sf::Sprite objectSprite = AssetManager::getInstance()->getAnimationFrame(currentAnimation.id, currentFrame);
	objectSprite.setPosition(getDrawPosition());
	target.draw(objectSprite);
}

Vec2 GameObject::getDrawPosition() const
{
	return getDrawPosition(VEC_NULL);
}

Vec2 GameObject::getDrawPosition(Vec2 offset) const
{
	Vec2 drawPosition = ((position + offset) - cameraPosition) * SCALE_FACTOR;
	drawPosition.x += RESOLUTION_X / 2;
	drawPosition.y = RESOLUTION_Y / 2 - drawPosition.y;

	return drawPosition - cameraPosition;
}

sf::CircleShape GameObject::getHitCircle(sf::Color color) const
{
	float scaledRadius = radius * SCALE_FACTOR;
	sf::CircleShape circle;
	circle.setRadius(scaledRadius);
	circle.setOrigin(scaledRadius, scaledRadius);
	circle.setOutlineColor(color);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineThickness(1);
	circle.setPosition(getDrawPosition());

	return circle;
}
