#include "BallMove.h"
#include "Math.h"
#include "Actor.h"
#include "Game.h"
#include "Collision.h"
#include "PhysWorld.h"


BallMove::BallMove(Actor* actor) 
	:MoveComponent(actor)
{
}

void BallMove::Update(float deltaTime) {

	Vector3 start = mOwner->GetPosition();
	Vector3 forward = mOwner->GetForward();
	Vector3 end = start + 30 * forward;

	LineSegment l(start , end);

	CollisionInfo info;
	if (mOwner->GetGame()->getPhysWorld()->SegmentCast(l, info) && info.mActor != mOwner) {
		Vector3::Reflect(forward, info.mNormal);
		mOwner->RotateToNewForward(forward);
	}

	MoveComponent::Update(deltaTime);
}