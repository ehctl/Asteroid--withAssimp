#pragma once
#include "Component.h"
#include "Collision.h"
#include <iostream>

using namespace std;

class BoxComponent : public Component {
public:
	BoxComponent(class Actor* actor);

	void shouldRotate(bool value) { mShouldRotate = value; }

	void setObjWorld(const AABB box) { mObjectBox = box; }

	AABB& getWorldBox()  { return mWorldBox; }

	AABB* getBox() { return &mObjectBox; }

	void OnUpdateWorldTransform() override;

private:
	AABB mObjectBox;
	AABB mWorldBox;
	
	bool mShouldRotate;


};