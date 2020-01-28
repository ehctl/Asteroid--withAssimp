#pragma once
#include <iostream>
#include <vector>

#include <GL\glew.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Math.h"
#include "Setting.h"


class Component {
public:
	Component(class Actor*  mOwner);	

	~Component();

	virtual void Draw(SDL_Renderer* temp) {}

	virtual void Update(float deltaTime) {}

	virtual void OnUpdateWorldTransform() {}

	Actor* getOwner() { return mOwner; }


protected:
	class Actor* mOwner;
};


#pragma once
