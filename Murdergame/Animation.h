#pragma once
#include "Main.h"
// Enum to give each animation a unique id.
enum AnimationId {
	PLAYER_IDLE,
	PLAYER_ATTACK_WINDUP,
	PLAYER_ATTACK,
	PLAYER_ATTACK_WINDDOWN,
	ENEMY_IDLE
};
// Simple container for animation-related information.
class Animation
{
public:
	// Id of the animation
	AnimationId id;
	// Offset in pixels from the top of the texture file.
	int textureOffset;
	// Number of frames in the animation
	int frameCount;
	// Animation frame width and height
	int width;
	int height;
	// Origin of the frames, used for centering
	int originx;
	int originy;
	// Number of drawn frames for each frame of animation. Bigger numbers -> slower animation.
	int speed;
	// If the animation is supposed to loop.
	bool loop;

	Animation();
	Animation(AnimationId id, int textureOffset, int frameCount, int width, int height, int originx, int originy, int speed, bool loop);
	~Animation();
};
// Collection of all animations.
static std::unordered_map<AnimationId, Animation> ANIMATIONS { 
	{PLAYER_IDLE,Animation(PLAYER_IDLE,0,4,80,80,50,50,5,true)},
	{PLAYER_ATTACK_WINDUP,Animation(PLAYER_ATTACK_WINDUP,80,4,80,80,50,50,6,false)},
	{PLAYER_ATTACK,Animation(PLAYER_ATTACK,160,1,80,80,50,50,1,false)},
	{ENEMY_IDLE,Animation(ENEMY_IDLE,0,1,60,68,30,34,1,true)}
};
