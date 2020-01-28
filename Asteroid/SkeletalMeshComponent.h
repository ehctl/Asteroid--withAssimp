#pragma once

#include "MeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"

#include <iostream>

struct MatrixPalette {

	Matrix4 mEntry[96];
};



class SkeletalMeshComponent : public MeshComponent {
public:
	SkeletalMeshComponent(class Actor* actor);

	void setAnimation(class Animation* animation) { mAnimation = animation; }

	void setSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	void ComputeMatrixPallete(bool value = true);

	float PlayAnimation(class Animation* anim, float playRate = 1);

	void Update(float deltaTime) override;

	void Draw(class Shader* shader) override;

	void setAnimTime(float animTime) { mAnimTime = animTime; }
private:
	float mAnimRate;

	float mAnimTime;

	class Animation* mAnimation;

	class Skeleton* mSkeleton;

	MatrixPalette mMatrixPalette;

	int count;
};