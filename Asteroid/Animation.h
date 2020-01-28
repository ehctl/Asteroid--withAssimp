#pragma once
#include "BoneTransform.h"
#include "SkeletalMeshComponent.h"

using namespace std;

class Animation {
public:
	Animation(class Game* game);

	void getGlobalPoseAtTime(vector<Matrix4>& outPoses, class Skeleton* inSkeleton, float inTime);

	float getDuration() { return mDuration; }

	string getName() { return mName; }

	int getNumBones() { return numBones; }
	
	///
	
	string mName;

	size_t numBones;

	size_t numFrames;

	float mDuration;

	float frameDuration;

	vector< vector< BoneTransform > > mInfo;

	int count;
}; 