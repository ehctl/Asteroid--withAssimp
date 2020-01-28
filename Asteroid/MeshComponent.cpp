#include "MeshComponent.h"
#include "Shader.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Texture.h"

#include "Obj.h"
#include "VertexArray.h"
MeshComponent::MeshComponent(Actor* owner)
	:Component(owner)
	,isDraw(true)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent() {
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader) {
	if (mOwner->getVertArr() && isDraw) {
		shader->SetMatrixUniform("uWorldTransform",mOwner->GetWorldTransform());
			
		shader->SetFloatUniform("uSpecPower", 100);
		if (mTexture) {
			mTexture->SetActive();
		}

		//cout << mOwner->getName() << endl;

		VertexArray* va = mOwner->getVertArr();
		va->SetActive();
		glDrawElements(GL_TRIANGLES, va->GetNumIndices() , GL_UNSIGNED_INT, nullptr);
	}
}