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
	position += direction * speed;
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
	if (currentFrame > (currentAnimation.frameCount * currentAnimation.speed)-1) {
		currentFrame = 0;
	}
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
	Vec2 drawPosition = (position - cameraPosition) * SCALE_FACTOR;
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
