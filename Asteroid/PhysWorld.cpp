#include "PhysWorld.h"
#include "Game.h"
#include "BoxComponent.h"	
#include <algorithm>

PhysWorld::PhysWorld(Game* game)
	:mGame(game)
{
	game->addPhysWorld(this);
}

PhysWorld::~PhysWorld() {
	mGame->removePhysWorld();
}

void PhysWorld::removeBoxComp(BoxComponent* box) {
	auto iter = std::find(mBoxComp.begin(), mBoxComp.end(), box);
	if (iter != mBoxComp.end()) {
		mBoxComp.erase(iter);
	}
}

bool PhysWorld::modelCollision(AABB& modelBox,string& mode) {
	mode = "";
	for (auto iter : mBoxComp) {
		AABB box = iter->getWorldBox();
		if (box != modelBox) {
			if (Intersect(modelBox, box)) {
				//return true;

			}
		}
	}
	return false;
	
}


bool PhysWorld::SegmentCast(LineSegment& l, CollisionInfo& info) {
	bool collide = false;
	float closetT = Math::Infinity;
	Vector3  tempNor;
	float tempT;
	for (auto box : mBoxComp) {

		if(Intersect(l, box->getWorldBox(), tempT, tempNor)){
			if (tempT < closetT) {
				closetT = tempT;
				info.mPoint = l.mStart + (l.mEnd - l.mStart) * closetT;
				info.mNormal = tempNor;
				info.box = box;
				info.mActor = box->getOwner();
				collide = true;
			}
		}
	}

	return collide;
}



bool compare(BoxComponent* a, BoxComponent* b) {
	return a->getWorldBox().mMin.x < b->getWorldBox().mMin.x  ;
}

// loc bot' intersect test bang cach dung SAT o? truc. x
// co' 1 so' cach' nua~ nhu la` grid , cells ,trees
bool PhysWorld::broadPhase(CollisionInfo& info) {
	
	sort(mBoxComp.begin(), mBoxComp.end(), compare);
	bool collide = false;
	for (size_t i = 0; i < mBoxComp.size() - 1; i++) {
		
		auto box1 = mBoxComp[i]->getWorldBox();
		float max = box1.mMax.x;

		for (size_t j = i + 1; j < mBoxComp.size() - 1; j++) {
			auto box2 = mBoxComp[j]->getWorldBox();
			if ( box2.mMin.x < max ) {
				if (Intersect(box1, box2)) {
					// do smt
					collide = true;
				}
			}

		}

	}
	return collide;
}



