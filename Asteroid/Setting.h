#pragma once
#include "Math.h"
#include <ctime>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 800;

const int SHIP_FPS = 60;


const int SHIP_WIDTH = 64;
const int SHIP_HEIGHT = 64;

const int SHIP_SPEED = 350;
const int SHIP_ANGULAR_SPEED = Math::TwoPi;

const float LASER_COOLDOWN = 0.5;

const int ASTEROID_SPEED = 250;

const int GAME_FPS = 60;   // fPS =  60


float randomFloat(int x, int y);

const float JUMP_DIS = 150.0f;

const float SCALE = 7.0f;