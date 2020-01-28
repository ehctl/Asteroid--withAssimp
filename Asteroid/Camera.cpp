#include "Camera.h"

#include "MoveComponent.h"
#include "SDL/SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"
#include "AudioSystem.h"
#include "SoundEvent.h"
#include "InputSystem.h"
#include "FPSCamera.h"
#include "ObjFile.h"
#include "Obj.h"
#include "TPPCamera.h"
#include "BoxComponent.h"


Camera::Camera(Game* game) 
	:Actor(game)
	
{
	mPitch = 0;
	mPitchSpeed = 0;
	mMaxPitch = Math::Pi / 3;
	name = "Camera";
	mMoveComp =new  MoveComponent(this);
	mMode = freeCam;
}

Quaternion Camera::getPitchQuaternion() {
	return Quaternion(getSide(), mPitch);
}

void Camera::attachToObj(Obj* obj) {
	mMode = attachedCam;
	pos = obj->getPos();
	mObj = obj;
}

void Camera::ActorInput(InputState* state) {
	float forwardSpeed = 0.0f;
	float sideSpeed = 0.0f;
	float angularSpeed;
		// wasd movement
		if (state->keyboard.getKeyValue(SDL_SCANCODE_A))
		{
			forwardSpeed += 100.0f;

		}
		if (state->keyboard.getKeyValue(SDL_SCANCODE_D))
		{
			forwardSpeed -= 100.0f;
		}
		if (state->keyboard.getKeyValue(SDL_SCANCODE_W))
		{
			sideSpeed += 100.0f;
		}
		if (state->keyboard.getKeyValue(SDL_SCANCODE_S))
		{
			sideSpeed -= 100.0f;
		}
		mMoveComp->SetForwardSpeed(forwardSpeed);
		mMoveComp->SetSideSpeed(sideSpeed);
		
		// jump 
		if (state->keyboard.getKeyState(SDL_SCANCODE_SPACE) == EPressed) {
			mMoveComp->setJump(true);
			mMoveComp->setPreJump(pos.z);
		}
	

	auto mousePos = state->mouse.getPosition();
	auto x = mousePos.x / 500;
	auto y = mousePos.y / 500;

	angularSpeed = x * Math::Pi * 8;
	y = -y * Math::Pi * 8;

	mMoveComp->SetAngularSpeed(angularSpeed);
	mPitchSpeed = y;
	

	if (state->keyboard.getKeyValue(SDL_SCANCODE_F)) {
		if (game->getMode() == THIRD_PERSON) 	game->setMode(FIRST_PERSON);
	}
	else if (state->keyboard.getKeyValue(SDL_SCANCODE_T)) {
		if (game->getMode() == FIRST_PERSON)	game->setMode(THIRD_PERSON);
	}
}