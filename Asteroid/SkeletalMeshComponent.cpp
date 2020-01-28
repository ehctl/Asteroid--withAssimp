#include "SkeletalMeshComponent.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

#include "Obj.h"
#include "VertexArray.h"
#include "Skeleton.h"
#include "Animation.h"

SkeletalMeshComponent::SkeletalMeshComponent(Actor* actor)
	:MeshComponent(actor)
	, mAnimRate(0.4)
	, count(0)
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
	mOwner->GetGame()->GetRenderer()->AddSkeletalMeshComp(this);
}

void SkeletalMeshComponent::ComputeMatrixPallete(bool value) {
	vector<Matrix4> invBindPose = mSkeleton->getInvBindPose();
	Matrix4 rootTrans = mSkeleton->mRootTransform;
	vector<Matrix4> currPose(mAnimation->getNumBones());

	mAnimation->getGlobalPoseAtTime(currPose, mSkeleton, mAnimTime);

	for (size_t i = 0; i < invBindPose.size(); i++) {
		mMatrixPalette.mEntry[i] =  currPose[i] *  mSkeleton->mBonesOffset[i] ;
		mMatrixPalette.mEntry[i].Transpose();
	}
}

void SkeletalMeshComponent::Draw(Shader* shader) {

	if (mOwner->getVertArr() && isDraw) {
		
		if (mOwner->getKind() == "model") {
			shader->SetMatrixUniform("uWorldTransform", mOwner->getModel()->GetWorldTransform());
		}
		else {
			shader->SetMatrixUniform("uWorldTransform", mOwner->GetWorldTransform());
		}

		shader->SetFloatUniform("uSpecPower", 100);

		shader->SetMatrixUniforms("uMatrixPalette", &mMatrixPalette.mEntry[0] , 96);
		
		if (mTexture) {
			mTexture->SetActive();
		}


		VertexArray* va = mOwner->getVertArr();
		va->SetActive();
		glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
	}

}

float SkeletalMeshComponent::PlayAnimation(Animation* anim, float playRate) {

	mAnimation = anim;
	mAnimTime = 0;
	mAnimRate = playRate;

	if (!mAnimation) { return 0.0f; }

	return mAnimation->getDuration();
}


void SkeletalMeshComponent::Update(float deltaTime) {
	mAnimTime += deltaTime * mAnimRate;

	while (mAnimTime > mAnimation->getDuration()) { mAnimTime -= mAnimation->getDuration(); }

	ComputeMatrixPallete();

}