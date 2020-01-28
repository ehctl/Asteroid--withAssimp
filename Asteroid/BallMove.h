#pragma once
#include "Component.h"
#include "MoveComponent.h"

class BallMove : public MoveComponent {
public:
	BallMove(class Actor* actor);

	void Update(float deltaTime);

};