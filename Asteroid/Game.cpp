// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------
#include "Game.h"
#include "GL/glew.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "MeshComponent.h"
//#include "AudioSystem.h"
#include "ObjFile.h"
#include "Obj.h"
//#include "AudioComponent.h"
#include "InputSystem.h"
#include "PhysWorld.h"
#include "BoxComponent.h"
#include "SkeletalMeshComponent.h"
#include "Animation.h"
#include "Skeleton.h"
#include "FPSCamera.h"
#include "TPPCamera.h"

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, isRunning(true)
	, ticksCount(0)
	, deltaTime(0)
	, isUpdating(false)
{}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO ) != 0) {
		SDL_Log("%s", SDL_GetError());
		return false;
	}
	 
	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(SCREEN_HEIGHT, SCREEN_HEIGHT)) {
		SDL_Log("Failed to initialized renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	/*
	mAudioSystem = new AudioSystem(this);

	if (!mAudioSystem->Initialize()) {
		SDL_Log("Failed to initialize FMOD system...");
		mAudioSystem->Shutdown();
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}*/

	mInputSystem = new InputSystem();
	if (!mInputSystem->Initialize()) {
		SDL_Log("Failed to initalize INPUT SYSTEM");
		return false;
	}

	mInputSystem->setRelativeMode(true);

	LoadData();

	ticksCount = SDL_GetTicks();


	return true;
}

void Game::RunLoop() {
	while (isRunning) {

		ListenEvent();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ListenEvent() {
	mInputSystem->PrepreForUpdate();

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break; 
		}
		mInputSystem->ProcessEvent(event);
	}
	mInputSystem->Update();

	auto state = mInputSystem->getInputState();
	
	ProcessInput(state);
	

	// update actors
	isUpdating = true;
	for (auto actor : actors) {
			actor->listenInput(&state, deltaTime);
	}
	isUpdating = false;


	for (auto actor : pendingActors) {
		actors.emplace_back(actor);
	}
	pendingActors.clear();

}	


void Game::ProcessInput(InputState state) {
	
	if (state.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == EReleased) {
		isRunning = false;
	}

}


void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16));

	deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
	ticksCount = SDL_GetTicks();

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}


	isUpdating = true;
	for (auto actor : actors) {
		
		if (actor->getState() == EActive) {
			actor->Update(deltaTime);
			
		}else if (actor->getState() == EDeactive) {
			deadActor.emplace_back(actor);
			
		}
	}
	isUpdating = false;

	for (auto actor : pendingActors) {
		actor->Update(deltaTime);
		actors.emplace_back(actor);
	}

	
	for (auto actor : deadActor) {
		delete actor;
	}


	deadActor.clear();
	pendingActors.clear();


	// sound
	//mAudioSystem->Update(deltaTime);
}

void Game::GenerateOutput() {

	mRenderer->Draw();
}

void Game::ShutDown() {
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::LoadData() {
	mMode = THIRD_PERSON;
	fpsCam = new FPSCamera(this);
	tppCam = new TPPCamera(this);


	mObjFile = new ObjFile(this);
	mObjFile->Read("Obj/total.obj");
	mObjFile->Read("Obj/Walking.dae");
	mObjFile->Read("Obj/Happy.dae");
	//mObjFile->Read("Obj/r7.dae");

	mObjFile->addObjToGame();

	mObjFile->Load();
	tppCam->attachToObj(mObjFile->getObj("Beta_JointsMesh"));
	fpsCam->attachToObj(mObjFile->getObj("Beta_JointsMesh"));

	mRenderer->SetAmbientLight(Vector3(0.5f, 0.5f, 0.5f));
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.5f, 0.5f, 0.5f);

	//mMusicEvent = mAudioSystem->PlayEvent("event:/Music");
}

void Game::removeSprite(class SpriteComponent* sprite) {
	auto temp = find(mSprite.begin(), mSprite.end(), sprite);
	if (temp != mSprite.end()) {
		mSprite.erase(temp);
	}
}

void Game::removeActor(class Actor* temp1) {
	auto temp = find(actors.begin(), actors.end(), temp1);
	if (temp != actors.end()) {
		actors.erase(temp);
	}
}


void Game::addActor(class Actor* temp) {
	if (isUpdating == true) {
		pendingActors.emplace_back(temp);
	}
	else {
		actors.emplace_back(temp);
	}
}

Animation* Game::getAnimation(string name) {
	for (auto iter : mAnimations) {
		if (strcmp(iter->mName.c_str(), name.c_str()) == 0) {
			return iter;
		}
	}
	return nullptr;
}


Skeleton* Game::getSkeleton(string name) {
	for (auto iter : mSkeleton) {
		if (strcmp(iter->mName.c_str(), name.c_str()) == 0) {
			return iter;
		}
	}
	return nullptr;
}