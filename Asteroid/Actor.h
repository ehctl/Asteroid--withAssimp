#pragma once
#include <iostream>
#include <vector>

#include "Math.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Collision.h"

using namespace std;

enum State {
	EActive,
	EPause,
	EDeactive
};

class Actor {
public:
	Actor(class Game* game);

	virtual ~Actor();

	class Game* GetGame() { return game; }

	void addComponent(class Component* comp);

	void removeComponent(class Component* comp);
	
	void removeAllComponent();

	template <class T>
	T findComponent(class Component* comp);

	std::vector<class Component*> getComponent() { return mComponent; }

	void listenInput(struct InputState* state,float deltaTime);

	void setTexture(class Texture* temp) { mTexture.emplace_back(temp); }


	class Texture* getTexture(int index) { return mTexture[index]; }

	void setRect(int x, int y);

	Vector3 getPos() { return pos; }

	virtual void checkInput(float deltaTime) {}

	void SetScale(float scale) { mScale = scale; }

	float getScale() { return mScale; }

	Vector3 GetPosition()  { return pos; }

	void SetPosition(Vector3 temp);	

	void setCenterPosition(Vector2 temp);

	Quaternion getRotation() { return mRotation; }
	
	void SetRotation(Quaternion temp) {  mRotation = temp; }

	Vector3 GetForward() { return Vector3::Transform(Vector3::UnitX, mRotation); }

	Vector3 getSide() { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	Vector3 getUp() { return Vector3::Transform(Vector3::UnitY, mRotation); }

	State getState() { return mState; }

	void setState(State temp) { mState = temp; }

	void setCircle(class CircleComponent* temp) { circle = temp;  }

	class CircleComponent* getCircle() { return circle;  }

	void ComputeWorldTransform();

	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	void RotateToNewForward(Vector3& forward);

	virtual void Update(float deltatime);
	virtual void ActorInput(struct InputState* state) {}
	virtual void UpdateActor(float deltaTime) {}
	virtual class  VertexArray* getVertArr() { return vA; }
	virtual void Load() {};
	virtual string getName() { return name; }

	class BoxComponent* getBoxComponent() { return mBoxComp; }

	void setKind(string value) { kind = value; }

	string getKind() { return kind; }

	class Obj* getModel() { return mModel; }

	float getPitch() { return mPitch; }
protected:
	class Game* game;
	State mState;
	std::vector <class Component*> mComponent;
	std::vector <class Texture*> mTexture;	
	Vector3 pos;	
	class CircleComponent* circle;
	float angle;
	Quaternion mRotation;

	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;
	float mScale;

	class VertexArray* vA;

	string name;

	string kind;

	class BoxComponent* mBoxComp;

	class Obj* mModel;

	class MoveComponent* mMoveComp;

	float mPitch;
	float mPitchSpeed;
	float mMaxPitch;
};

