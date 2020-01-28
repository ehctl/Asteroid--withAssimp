#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "Collision.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

using namespace std;


bool has(string input, string s);

enum Mode {
	staticModel ,
	animModel
};

union Vertex {
	float f;
	int b;

};

struct boneData {
	int jointID[4] = { 0 };
	float jointWeight[4] = { 0.0f };

	void addBoneData(int id, float weight) {
		for (int j = 0; j < 4; j++) {
			if (jointWeight[j] == 0.0f) {
				jointID[j] = id;
				jointWeight[j] = weight;
				return;
			}
		}
	}
};

class ObjFile {
public:
	ObjFile(class Game* game);

	void Read(string fileName);

	void addObj(class Obj* mesh);

	class Obj* getObj(string meshName);

	class Obj* getObj();

	void Load();

	void addObjToGame();

private:
	unordered_map<string, class Obj*> mObj;
	
	vector<string> mBonesName;

	class Game* mGame;
};


