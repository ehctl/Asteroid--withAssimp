#pragma once

#include "Component.h"
#include "Math.h"

class MoveComponent : public Component {
public:
	MoveComponent(class Actor* mOwner);

	~MoveComponent();

	void Update(float deltaTime );

	void Jump(float dis, float deltaTime , Vector3& temp);
	
	float getAngularSpeed() { return angularSpeed; }

	float getForwardSpeed() { return forwardSpeed; }

	float getSideSpeed() { return sideSpeed; }

	void SetAngularSpeed(float aS) { angularSpeed = aS; }

	void SetForwardSpeed(float temp) { forwardSpeed = temp; }

	void SetSideSpeed(float temp) { sideSpeed = temp; }

	void setJump(bool value) { isJumping = value; }

	void setPitchQuaternion(Quaternion pitch) { mPitchQuat = pitch; }

	void setPreJump(float temp) { preJump = temp;  }
protected:
	float angularSpeed;
	float forwardSpeed;
	float sideSpeed;
	float upSpeed;

	bool isJumping;
	float jumpDis;
	float preJump;
	Vector3 fw;
	Vector3 side;
	float fwS;
	float sideS;
	Quaternion mPitchQuat;
};