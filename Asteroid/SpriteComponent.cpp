#include "SpriteComponent.h"
#include "Component.h"
#include <iostream>
#include "Texture.h"
#include "Game.h"
#include "Actor.h"
#include "Renderer.h"

using namespace std;

SpriteComponent::SpriteComponent(class Actor* actor, int mFps)
	:Component(actor)
	, gFps(16)
	, mFps(mFps)
	, curFrame(1)
	,mTexture(nullptr)
	,mTexWidth(0)
	,mTexHeight(0)
{
	count = mFps / gFps;
	actor->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
	mOwner->GetGame()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(Texture* texture) {
	mTexture = texture;

	mTexWidth = texture->getWidth();
	mTexHeight = texture->getHeight();
}

void SpriteComponent::Draw(Shader* shader) {
	if (mTexture) {
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);

		Matrix4 world = scaleMat * mOwner->GetWorldTransform();
		shader->SetMatrixUniform("uWorldTransform", world);

		mTexture->SetActive();

		glDrawElements(
			GL_TRIANGLES,
			6,
			GL_UNSIGNED_INT,
			nullptr
		);
	}
}


