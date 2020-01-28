#pragma once
#include "Math.h"
#include "Camera.h"

class FPSCamera : public  Camera {
public: 
	FPSCamera(class Game* model);

	void UpdateActor(float deltaTime) override;


};