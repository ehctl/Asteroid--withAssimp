#pragma once
// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"

int main(int argc, char** argv)
{
	Game game;

	bool check = game.Initialize();

	if (check) {
		game.RunLoop();
	}

	game.ShutDown();

	return 0;
}

