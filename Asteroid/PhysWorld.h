#pragma once
#include <iostream>
#include <vector>
#include "Collision.h"

using namespace std;

struct CollisionInfo {
	Vector3 mPoint;

	Vector3 mNormal;

	class BoxComponent* box;

	class Actor* mActor;
};


class PhysWorld {
public:
	PhysWorld(class Game* game);
	~PhysWorld();

	void addBoxComp(class BoxComponent* box) { mBoxComp.emplace_back(box); }

	void removeBoxComp(class BoxComponent* box);

	bool modelCollision(AABB& modelBox,string& mode);

	bool SegmentCast(LineSegment& l, CollisionInfo& info);

	bool broadPhase(CollisionInfo& info);

	vector<class BoxComponent*> getBoxComp() { return mBoxComp; }

	
private:
	class Game* mGame;

	vector<class BoxComponent*> mBoxComp;
};