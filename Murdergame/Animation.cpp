#include "Animation.h"



Animation::Animation()
{
}

Animation::Animation(AnimationId id, int textureOffset, int frameCount, int width, int height, int originx, int originy, int speed) :
	id(id), textureOffset(textureOffset), frameCount(frameCount), width(width), height(height), originx(originx), originy(originy), speed(speed)
{
}


Animation::~Animation()
{
}
