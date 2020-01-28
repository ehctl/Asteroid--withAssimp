#include "Animation.h"
#include <fstream>
#include <sstream>
#include "pugixml.hpp"
#include "Skeleton.h"
#include "Game.h"

Animation::Animation(Game* game) {
	game->addAnimation(this);
}

void Animation::getGlobalPoseAtTime(vector<Matrix4>& outPose, Skeleton* skeleton, float inTime) {
	int currFrame = static_cast<int>(inTime / frameDuration) ;
	
	int nextFrame;
	if (currFrame == numFrames ) {
		nextFrame = 0;
	}
	else {
		nextFrame = currFrame + 1;
	}


	float pct = inTime / frameDuration - currFrame;

	Matrix4 root;
	root = BoneTransform::Interpolate(mInfo[0][currFrame], mInfo[0][nextFrame], pct);

	outPose[0] = root;

	auto bones = skeleton->getBones();
	for (int i = 1; i < skeleton->getNumBones() ; i++) {
		Matrix4 localMat = BoneTransform::Interpolate(mInfo[i][currFrame], mInfo[i][nextFrame], pct);

		outPose[i] =  outPose[bones[i].parentIndex]  * localMat  ;
	}

}