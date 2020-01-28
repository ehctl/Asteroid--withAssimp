#include "BoxComponent.h"
#include "Actor.h"
#include "Game.h"
#include "PhysWorld.h"

BoxComponent::BoxComponent(Actor* actor)
	: Component(actor)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, mShouldRotate(true)
{
	//mOwner->GetGame()->getPhysWorld()->addBoxComp(this);
}

void BoxComponent::OnUpdateWorldTransform() {
	mWorldBox = mObjectBox;

	mWorldBox.mMax *= mOwner->getScale();
	mWorldBox.mMin *= mOwner->getScale();

	if (mShouldRotate) {
		// rotate thuc ra la transform
		mWorldBox.Rotate(mOwner->getRotation());
	}

	mWorldBox.mMax += mOwner->GetPosition();
	mWorldBox.mMin += mOwner->GetPosition();

	/*
	if(mOwner->getName() == "Zumbi_Female")
	cout << mOwner->getName() << " " << mWorldBox.mMin.x << " " << mWorldBox.mMin.y << " " << mWorldBox.mMin.z << " " << mWorldBox.mMax.x << " " << mWorldBox.mMax.y << " " << mWorldBox.mMax.z << endl;
	*/

}