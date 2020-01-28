#include "Actor.h"
#include "Game.h"
#include "Texture.h"
#include "Component.h"
#include "InputSystem.h"

Actor::Actor(class Game* game)
	:game(game)
	, mState(EActive)
	, mRecomputeWorldTransform(true)
	, kind("actor")
{
	mScale = 7;
	pos = Vector3(0.0f,0.0f,0.0f);

	// ta phai rotate de phu` hop. voi mau~ 3D
	// vi vay nen ta phai thay doi lai cac axis 
	// y' = -z , z' = y ( vi no' quay theo chieu kim dong ho` )

	mRotation = Quaternion(Vector3::UnitX,Math::PiOver2);
	//mRotation = Quaternion(Vector3::UnitY, Math::PiO);
	game->addActor(this);
}


void Actor::RotateToNewForward(Vector3& forward) {
	float dot = Vector3::Dot(forward, Vector3::UnitX);

	float angle = Math::Acos(dot);


	if (dot > 0.9999f) {
		mRotation = Quaternion::Identity;
	}
	else if (dot < -0.9999f) {
		mRotation = Quaternion(Vector3::UnitZ, Math::Pi);
	}
	else {
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		mRotation = Quaternion(axis, angle);
	}

}


void Actor::Update(float deltatime) {
	//cout << name << endl;
	//ComputeWorldTransform();
	
	for (auto comp : mComponent) {
		comp->Update(deltatime);
	}
	UpdateActor(deltatime);
	
	ComputeWorldTransform();
}


void Actor::ComputeWorldTransform() {
	if (mRecomputeWorldTransform) {
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(pos);
	}

	for (auto comp : mComponent) {
		comp->OnUpdateWorldTransform();
	}
}


Actor::~Actor() {
	game->removeActor(this);
}


void Actor::addComponent(class Component* temp) {
	mComponent.emplace_back(temp);
}


template <class T>
T Actor::findComponent(class Component* temp) {
	auto temp_comp = find(mComponent.begin(), mComponent.end(), temp);
	if (temp_comp != mComponent.end()) {
		return temp_comp;
	}
}

void Actor::removeComponent(class Component*  temp) {
	auto temp_comp = find(mComponent.begin(), mComponent.end(), temp);
	if (temp_comp != mComponent.end()) {
		mComponent.erase(temp_comp);
	}
}

void Actor::removeAllComponent() {
	mComponent.clear();
}

void Actor::listenInput(InputState* state,float deltaTime) {
	if (mState == EActive) {
		
		//for (auto iter : game->) {
			ActorInput(state);
		//}
	}
}

void Actor::setRect(int x, int y) {
	pos.x = x;
	pos.y = y;

}

void Actor::SetPosition(Vector3 temp) {
	pos.x = temp.x;
	pos.y = temp.y;
	pos.z = temp.z;
}



