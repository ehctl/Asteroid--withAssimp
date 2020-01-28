#pragma once
#include "Component.h"
#include "Shader.h"


class SpriteComponent : public Component {
public:
	SpriteComponent(class Actor* mActor, int gFps);

	~SpriteComponent();

	virtual void Draw(Shader* shader);

	void SetTexture(class Texture* texture);

	void setFps(float x) { mFps = x; }

protected:
	class Texture* mTexture;
	float mFps;
	float gFps;
	int curFrame;
	int count;
	int mTexWidth;
	int mTexHeight;
};
