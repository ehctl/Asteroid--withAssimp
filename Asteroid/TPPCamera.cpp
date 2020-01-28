#include "TPPCamera.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Obj.h"
#include "Renderer.h"

TPPCamera::TPPCamera(Game* game)
	:Camera(game)
{
}

void TPPCamera::UpdateActor(float deltaTime) {

	mPitch += mPitchSpeed * deltaTime;

	// -Max << mPitch << Max
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);

	if (game->getMode() == THIRD_PERSON) {
		if (mMode == attachedCam) {
			mRotation = Quaternion::Concatenate( mObj->getRotation(), Quaternion(Vector3::UnitZ,-Math::PiOver2));
			Quaternion q(getSide(), mPitch);

			Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

			Vector3 poss = mObj->getPos() + Vector3(-10, 20, 50);

			Vector3 target = poss + Vector3::Transform(GetForward(), q) * 100;

			Matrix4 view = Matrix4::CreateLookAt(poss, target, up);

			game->GetRenderer()->SetViewMatrix(view);
			//game->getAudioSystem()->SetListener(view);
		}
		else if (mMode == freeCam) {
			Quaternion q(getSide(), mPitch);

			Vector3 up = Vector3::Transform(Vector3::UnitZ, q);

			Vector3 target = pos + Vector3::Transform(GetForward(), q) * 100;


			Matrix4 view = Matrix4::CreateLookAt(pos, target, up);

			game->GetRenderer()->SetViewMatrix(view);
			//game->getAudioSystem()->SetListener(view);

		}
	}

}