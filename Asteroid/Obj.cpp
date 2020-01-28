#include "Obj.h"
#include "Game.h"
#include "MeshComponent.h"
#include "VertexArray.h"
#include "Actor.h"
#include "Renderer.h"
#include "BoxComponent.h"
#include "SkeletalMeshComponent.h"
#include "InputSystem.h"
#include "SDL/SDL_scancode.h"
#include "MoveComponent.h"


Obj::Obj(class Game* game, AABB aabb , class  ObjFile* of,const char* Name, vector<float> vert, vector<float> normal, vector<float> textCord, vector<unsigned int> ind)
	:Actor(game)
	, mObjFile(of)
	, mInd(ind)

{
	mPitch = 0;
	mPitchSpeed = 0;
	mMaxPitch = Math::Pi / 3;

	mKind = NCONTROL;
	name = Name;

	mObjFile->addObj(this);
	mMeshComp = new MeshComponent(this);
	mMeshComp->setIsSkeletal(false);
	mMeshComp->SetTexture(game->GetRenderer()->GetTexture("Assets/" + name + ".png"));


	vA = new VertexArray(vert.data() , vert.size() / 3 ,normal.data() , textCord.data() , mInd.data() , mInd.size() );

	BoxComponent*  bc = new BoxComponent(this);
	
	//aabb.Rotate(Quaternion(Vector3::UnitX, Math::PiOver2));

	bc->setObjWorld(aabb);
	mBoxComp = bc;
}

Obj::Obj(class Game* game, AABB aabb, class  ObjFile* of, string Name, vector<float> vert, vector<float> normal, vector<float> textCord, vector<boneData> joint, vector<unsigned int> ind)
	:Actor(game)
	, mObjFile(of)
{
	mScale = 0.2;
	pos = Vector3(0, 0, 10);
	mKind = CONTROL;
	name = Name;

	mObjFile->addObj(this);
	mSkeletalComp = new SkeletalMeshComponent(this);
	mSkeletalComp->setIsSkeletal(true);
	mSkeletalComp->SetTexture(game->GetRenderer()->GetTexture("Assets/default.png"));

	mMoveComp = new MoveComponent(this);

	

	vA = new VertexArray( vert.data(),vert.size() / 3 , normal.data(), textCord.data(), ind.data() , ind.size() , joint.data() );

	BoxComponent*  bc = new BoxComponent(this);
	//aabb.Rotate(Quaternion(Vector3::UnitX, Math::PiOver2));
	bc->setObjWorld(aabb);
	mBoxComp = bc;
}

void Obj::Load() {
	if (mSkeletalComp != nullptr) {
		mSkeletalComp->setAnimation(game->getAnimation("Obj/Happy.dae"));
		mSkeletalComp->setSkeleton(game->getSkeleton(name));
	}
}


void Obj::ActorInput(InputState* state) {
	if (mSkeletalComp != nullptr && mKind == CONTROL) {
		float forwardSpeed = 0.0f;
		float sideSpeed = 0.0f;
		float angularSpeed=0.0f;
		
		auto mousePos = state->mouse.getPosition();
		auto x = mousePos.x / 500;
		auto y = mousePos.y / 500;

		angularSpeed = x * Math::Pi * 8;
		y = -y * Math::Pi * 8;

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
		}/**/

		if ( sideSpeed != 0) {
			mSkeletalComp->setAnimation(game->getAnimation("Obj/Walking.dae"));
		}
		else {
			mSkeletalComp->setAnimation(game->getAnimation("Obj/Happy.dae"));
		}

		// jump 
		if (state->keyboard.getKeyState(SDL_SCANCODE_SPACE) == EPressed) {
			mMoveComp->setJump(true);
			mMoveComp->setPreJump(pos.z);
		}

		mMoveComp->SetForwardSpeed(forwardSpeed);
		mMoveComp->SetSideSpeed(sideSpeed);
		mMoveComp->SetAngularSpeed(angularSpeed);
		mPitchSpeed = 0;

	}
}

void Obj::showVert() {
	for (int i = 0; i < numVert; i++) {
		for (int j = 0; j < 8; j++) {
			//cout << mVert[i * 8 + j] << " ";
		}
		cout << endl;
	}
}


void Obj::Unload() {
	delete vA;
	vA = nullptr;
}

