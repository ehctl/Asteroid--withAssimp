#pragma once
// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "SDL/SDL_image.h"
#include "SDL/SDL.h"
#include "Setting.h"
#include "SoundEvent.h"
#include "Animation.h"
#include <unordered_map>
struct vectorEx {
	int x;
	int y;
};

enum mode {
	THIRD_PERSON ,
	FIRST_PERSON
};
class Game {
public:
	Game();
	bool Initialize();

	void RunLoop();

	void ShutDown();

	class Texture* getTexture(const std::string& file);

	void addSprite(class SpriteComponent* sprite) { mSprite.emplace_back(sprite); }

	void removeSprite(class SpriteComponent* temp);

	void addActor(class Actor* temp);

	void removeActor(class Actor* temp);


	void removeAsteroid(class Actor* temp);

	bool LoadShaders();

	class Renderer* GetRenderer() { return mRenderer; }

	class CameraActor* GetCameraActor() { return mCameraActor; }

	void addObjFile(class ObjFile* of) { mObjFile = of; }

	ObjFile* getObjFile() { return mObjFile; }

	void addObj(class Obj* obj) { mObj.emplace_back(obj); }

	class AudioSystem* getAudioSystem() { return nullptr; }


	class Obj* getModel() { return mModel; }

	void addPhysWorld(class PhysWorld* pw) { mPhysWorld = pw; }

	class PhysWorld* getPhysWorld() { return mPhysWorld; }

	void removePhysWorld() { delete mPhysWorld; }
	
	void addAnimation(class Animation* anim) { mAnimations.emplace_back(anim); }

	void addSkeleton(class Skeleton* skel) { mSkeleton.emplace_back(skel); }

	class Animation* getAnimation(string name);

	class Skeleton* getSkeleton(string name);

	mode getMode() { return mMode; }

	void setMode(mode Mode) { mMode = Mode; }
private:
	void ListenEvent();
	void UpdateGame();
	bool isRunning;
	void GenerateOutput();
	void LoadData();
	void ProcessInput(struct InputState state);


	std::vector <class Actor*> actors;
	std::vector <class Actor*> pendingActors;
	std::vector <class Actor*> deadActor;
	std::vector <class SpriteComponent*> mSprite;
	std::map <std::string, class Texture*> mTexture;
	SDL_Window* mWindow;
	Uint32 ticksCount;
	float deltaTime;
	bool isUpdating;

	SDL_GLContext mContext;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
	class Renderer* mRenderer;
	class CameraActor* mCameraActor;

	class ObjFile* mObjFile;

	std::vector<class Obj*> mObj;

	//class AudioSystem* mAudioSystem;

	//class SoundEvent mMusicEvent;

	class InputSystem* mInputSystem;

	class Obj* mModel;

	mode mMode;

	class FPSCamera* fpsCam;

	class TPPCamera* tppCam;

	class PhysWorld* mPhysWorld;

	vector< class Animation*> mAnimations;

	vector< class Skeleton*> mSkeleton;
};
	