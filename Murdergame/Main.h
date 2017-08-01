#pragma once
// A header file to hold all the common sfml/system libraries and constants.
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <list>
#include <unordered_map>
#include <string>
#include <iostream>
#include "Vec2.h"


// Some constant values


// Tickrate/framerate of the game, in frames per second.
const int TICKRATE = 60;

// Scaling from ingame units to pixels.
const float SCALE_FACTOR = 30;

// Window resolution.
const float RESOLUTION_X = 1980;
const float RESOLUTION_Y = 1080;

// Keybindings.
const sf::Keyboard::Key MOVE_RIGHT = sf::Keyboard::D;
const sf::Keyboard::Key MOVE_UP = sf::Keyboard::W;
const sf::Keyboard::Key MOVE_LEFT = sf::Keyboard::A;
const sf::Keyboard::Key MOVE_DOWN = sf::Keyboard::S;

// Movement values
const float PLAYER_SPEED = 0.2f;
const float PLAYER_ACCELERATION_INCREMENT = 0.1f;
const float ENEMY_SPEED = 0.1f;

// Asset path
const std::string ASSET_PATH = "D:/dev/assets/";

// Debug constants;
const bool DRAW_HITBOXES = true;