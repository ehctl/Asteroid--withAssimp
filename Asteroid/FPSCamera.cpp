#include "FPSCamera.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Obj.h"
#include "Renderer.h"	
#include "AudioSystem.h"

FPSCamera::FPSCamera(Game* game	) 
	: Camera(game)

{
	pos = Vector3(30, 0, 30);
}

void FPSCamera::UpdateActor(float deltaTime) {
	

	mPitch += mPitchSpeed * deltaTime;

		// -Max << mPitch << Max
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);

	if (game->getMode() == FIRST_PERSON) {
		if (mMode == attachedCam) {
			mRotation = mObj->getRotation();
			Quaternion q( mObj->getSide() , mPitch );

			Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

			Vector3 poss = pos + Vector3(0,1.5,34);

			Vector3 target = poss + Vector3::Transform(mObj->GetForward(), q) * 100;

			Matrix4 view = Matrix4::CreateLookAt(poss, target, up);

			game->GetRenderer()->SetViewMatrix(view);
			//game->getAudioSystem()->SetListener(view);
		}
		else if( mMode == freeCam) {
			Quaternion q(getSide(), mPitch);

			Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

			Vector3 target = pos + Vector3::Transform(GetForward(), q) * 100;


			Matrix4 view = Matrix4::CreateLookAt(pos, target, up);

			game->GetRenderer()->SetViewMatrix(view);
			//game->getAudioSystem()->SetListener(view);

		}
	}
}