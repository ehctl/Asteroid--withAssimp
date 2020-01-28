#pragma once
#include "Game.h"
#include "MoveComponent.h"
#include "Actor.h"
#include "Setting.h"
#include "Obj.h"
#include "Collision.h"
#include "BoxComponent.h"
#include "PhysWorld.h"
#include "ObjFile.h"


MoveComponent::MoveComponent(class Actor* temp)
	:Component(temp)
	, forwardSpeed(0.0f)
	, jumpDis(JUMP_DIS)
	, isJumping(false)
{}

MoveComponent::~MoveComponent()
{
	mOwner->removeComponent(this);
}

void MoveComponent::Jump(float dis  , float deltaTime, Vector3& temp) {

	if(isJumping) {
		jumpDis -= 2 * dis * deltaTime;	

		temp += mOwner->getUp() * deltaTime * jumpDis;

		if (temp.z < preJump) {
			temp.z = preJump;
			isJumping = false;
			jumpDis = dis;
		}

	}

}

void MoveComponent::Update(float deltaTime) {	


	if (!Math::NearZero(angularSpeed)) {
		Quaternion rot = mOwner->getRotation(); 
		Quaternion y(Vector3::UnitZ, angularSpeed * deltaTime);
		rot = Quaternion::Concatenate(rot, y);
		mOwner->SetRotation(rot);
	}


	Vector3 temp = mOwner->GetPosition();		
	
	Vector3 mFW, mSide;
	float mFWS, mSideS;


	if (isJumping) {
		if (fw == Vector3::Zero && side == Vector3::Zero && fwS == 0 && sideS == 0)
		{
			fw = mOwner->GetForward();
			side = mOwner->getSide();
			fwS = forwardSpeed;
			sideS = sideSpeed;
		}

		mFW = fw;  mSide = side, mFWS = fwS, mSideS = sideS;
	}
	else {

		fw = side = Vector3::Zero;
		fwS = sideS = 0;

		mFW = mOwner->GetForward();     
		mSide = mOwner->getSide();
		mFWS = forwardSpeed;
		mSideS = sideSpeed;
	}


	// we cannot move while jumping
	//auto modelBox = mOwner->getBoxComponent()->getOwner()->getBoxComponent()->getWorldBox() ;

	string mode;


	temp += mFW * deltaTime * mFWS;		
	//if(mOwner->GetGame()->getPhysWorld()->modelCollision(modelBox, mode)) temp -= mFW * deltaTime * mFWS;

	temp += mSide * deltaTime * mSideS;
	//if (mOwner->GetGame()->getPhysWorld()->modelCollision(modelBox, mode)) temp -= mSide * deltaTime * mSideS;

	Jump(JUMP_DIS, deltaTime, temp);


	mOwner->SetPosition(temp);

}

