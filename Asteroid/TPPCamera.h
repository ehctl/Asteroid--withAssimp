#pragma once
#include "Math.h"
#include "Camera.h"
class TPPCamera : public  Camera {
public:
	TPPCamera(class Game* game);

	void UpdateActor(float deltaTime) override;

};