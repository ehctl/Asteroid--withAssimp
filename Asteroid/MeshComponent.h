#pragma once
#include "Component.h"
#include <cstddef>


class MeshComponent : public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent();

	virtual void Draw(class Shader* shader);

	void SetTexture(class Texture* texture) { mTexture = texture; }

	bool IsSkeletal() { return isSkeletal; }

	void setIsSkeletal(bool value) { isSkeletal = value; }

	void setIsDraw(bool value) { isDraw = value; }
protected:

	Texture* mTexture;

	bool isSkeletal;

	bool isDraw;
};