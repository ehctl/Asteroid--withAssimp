#pragma once
#include "BoneTransform.h"
#include <iostream>
#include <vector>

using namespace std;

struct Bone {
		BoneTransform bT;

		std::string Name;

		int parentIndex;
	};

class Skeleton {

public:
	
	Skeleton(class Game* game);

	string getName() { return mName; }

	void setBone(std::vector< Bone > temp) { mBones = temp; }

	void setInvBindPose(std::vector<Matrix4> temp) { mInvBindPose = temp; }

	size_t getBoneSize() { return mBones.size(); }

	Bone getBone(size_t index) { return mBones[index]; }

	std::vector<Bone> getBones() { return mBones; }

	std::vector<Matrix4> getInvBindPose() { return mInvBindPose; }

	//std::vector< Matrix4> getBindPose() { return mBindPose; }

	int getNumBones() { return mBones.size(); }

	//void computeInvBindPoseMatrix(vector<Matrix4>& invPoseMat, vector<Matrix4>& bindPose, vector<int> parentID);

	string mName;

	std::vector< Bone > mBones;

	std::vector<Matrix4> mInvBindPose;

	std::vector<Matrix4> mBonesOffset;

	Matrix4 mRootTransform;
	//std::vector< Matrix4> mBindPose;
};