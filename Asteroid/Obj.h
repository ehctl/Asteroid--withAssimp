#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Actor.h"
#include "Collision.h"
#include "ObjFile.h"


using namespace std;

enum animKind {
	CONTROL ,
	NCONTROL
};


class Obj : public  Actor{
public:
	Obj(class Game* game,AABB ab, class  ObjFile* of,const char*  name, vector<float> vert, vector<float> normal, vector<float> textCord, vector<unsigned int> ind);
	Obj(class Game* game, AABB ab ,class  ObjFile* of, string name, vector<float> vert, vector<float> normal, vector<float> textCord,vector<boneData> mJoint , vector<unsigned int> ind);
	~Obj() {}

	void ActorInput(InputState* state) override;

	void Load();

	void Unload();

	string getName() { return name; }

	unsigned int getNumVert() { return numVert; }
	unsigned int getNumInd() { return numInd; }

	class MeshComponent* getMeshComp() { return mMeshComp; }

	class SkeletalMeshComponent* getSkeletalComp() { return mSkeletalComp; }

	void showVert();

	void setAnimKind(animKind value) { mKind = value; }

private:
	class ObjFile* mObjFile;


	vector<unsigned int> mInd;
	unsigned numVert;
	unsigned numInd;

	class MeshComponent* mMeshComp;

	animKind mKind;

	class SkeletalMeshComponent* mSkeletalComp;

};