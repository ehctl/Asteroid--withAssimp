#pragma once
#include "Actor.h"
#include "Game.h"

enum camMode {
	freeCam ,
	attachedCam
};

class Camera : public Actor {
public:
	Camera(class Game* game);

	void ActorInput(InputState* state) override;

	Quaternion getPitchQuaternion();

	void setPitchSpeed(float ps) { mPitchSpeed = ps; }

	void attachToObj(class Obj* obj);

protected:
	class Obj* mObj;
	camMode mMode;
};