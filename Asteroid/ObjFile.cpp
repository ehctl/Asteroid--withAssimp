#include "ObjFile.h"
#include "Obj.h"
#include "Game.h"
#include <cstring>
#include "Setting.h"
#include "SkeletalMeshComponent.h"
#include "BoneTransform.h"

ObjFile::ObjFile(Game* game)
	:mGame(game)
{
}

void ObjFile::addObjToGame() {
	for (auto i : mObj) {
		mGame->addObj(i.second);
	}
}

void ObjFile::addObj(Obj* mesh) {
	mObj.emplace(mesh->getName(), mesh);
}

Obj* ObjFile::getObj(string meshName) {
	auto temp = mObj.find(meshName);
	if (temp != mObj.end()) {
		return temp->second;
	}
	return nullptr;
}

void ObjFile::Load() {
	for (auto i : mObj) {
		i.second->Load();
	}
}

Obj* ObjFile::getObj() {
	for (auto iter : mObj) {
		return iter.second;
	}
}

int searchInd(vector<string> name, string temp) {
	for (int i = 0; i < name.size(); i++) {
		if (strcmp(name[i].c_str(), temp.c_str()) == 0) {
			return i;
		}
	}
	// dhs lai co the co' nhung joint khong co trong danh sach =)) hack vl ^^
	return -1;
}


bool has(string input, string s) {
	for (int i = 0; i < input.length(); i++) {
		if (input[i] == s[0] ) return true;
	}
	return false;
}
void transformMat(Matrix4& mat1, aiMatrix4x4& mat2) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat1.mat[i][j] = mat2[i][j];
		}
	}
}

void getName(aiNode* node, vector<string>& name, vector<string>& check) {
	string nameT = node->mName.data;
	if (searchInd(check, nameT) != -1) {
		name.emplace_back(nameT);
		for (int i = 0; i < node->mNumChildren; i++) {
			getName(node->mChildren[i], name, check);
		}
	}
}

void jointHerarchy(vector< Bone>& bones, aiNode* node, vector< string>& jointName) {
	if (strcmp(node->mName.C_Str(), "RootNode") != 0) {
		int jointInd = searchInd(jointName, static_cast<string>(node->mName.data));
		if (jointInd != -1) {
			int parentInd = searchInd(jointName, static_cast<string>(node->mParent->mName.data));
			Bone b = Bone();
			b.Name = node->mName.data;
			b.parentIndex = parentInd;
			transformMat(b.bT.matrix, node->mTransformation);
			bones.emplace_back(b);
			for (int i = 0; i < node->mNumChildren; i++) {
				jointHerarchy(bones, node->mChildren[i], jointName);
			}
		}
	}
	else {
		jointHerarchy(bones, node->mChildren[0], jointName);
	}
}


void computeInvBindPoseMat(vector<Matrix4>& InvBindPose, vector<Bone>& bones) {
	InvBindPose[0] = bones[0].bT.matrix;

	for (size_t i = 1; i < bones.size(); i++) {
		Matrix4 global =  bones[i].bT.matrix * InvBindPose[bones[i].parentIndex]   ;

		InvBindPose[i] = global;
	}

	for (int i = 0; i < InvBindPose.size(); i++) {
		InvBindPose[i].Invert();
	}

}

void ObjFile::Read(string Name) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(Name, aiProcessPreset_TargetRealtime_Fast );

	if (!scene) {
		cout << "Failed to load file " + Name << endl;
	}

	if (scene->HasAnimations()) {
		vector<string> boneName;

		vector<string> check(scene->mAnimations[0]->mNumChannels);
		for (size_t j = 0; j < check.size(); j++) {
			check[j] = scene->mAnimations[0]->mChannels[j]->mNodeName.data;
		}

		getName(scene->mRootNode->mChildren[0], boneName, check);
		mBonesName = boneName;
		boneName.clear();
	}

	for (int j = 0; j < scene->mNumAnimations; j++) {
		auto temp = scene->mAnimations[j];
		Animation* anim = new Animation(mGame);
		anim->mName = temp->mName.data;
		anim->mName = Name;
		anim->mDuration = temp->mDuration * temp->mTicksPerSecond;
		anim->frameDuration = temp->mChannels[0]->mPositionKeys[1].mTime - temp->mChannels[0]->mPositionKeys[0].mTime;
		anim->numBones = temp->mNumChannels;
		anim->numFrames = temp->mChannels[0]->mNumPositionKeys;
		vector< vector< BoneTransform>> info(temp->mNumChannels);
		for (int m = 0; m < anim->numBones; m++) {
			int jointInd = searchInd(mBonesName, temp->mChannels[m]->mNodeName.data);

			vector<BoneTransform> bf;
			for (int k = 0; k < anim->numFrames; k++) {
				BoneTransform b = BoneTransform();

				b.position.x = temp->mChannels[m]->mPositionKeys[k].mValue.x;
				b.position.y = temp->mChannels[m]->mPositionKeys[k].mValue.y;
				b.position.z = temp->mChannels[m]->mPositionKeys[k].mValue.z;

				b.rotation.x = temp->mChannels[m]->mRotationKeys[k].mValue.x;
				b.rotation.y = temp->mChannels[m]->mRotationKeys[k].mValue.y;
				b.rotation.z = temp->mChannels[m]->mRotationKeys[k].mValue.z;
				b.rotation.w = temp->mChannels[m]->mRotationKeys[k].mValue.w;

				auto mat = aiMatrix4x4(temp->mChannels[m]->mScalingKeys[k].mValue, temp->mChannels[m]->mRotationKeys[k].mValue, temp->mChannels[m]->mPositionKeys[k].mValue);
				transformMat(b.matrix, mat);

				bf.emplace_back(b);
			}
			info[jointInd] = bf;
		}

		for (int i = 1; i < anim->numFrames; i++) {
			info[0][i] = info[0][0];
		}

		anim->mInfo = info;
		info.clear();

	}

	if ( scene->mNumMeshes != 1 ) {
		for (int i = 0; i < scene->mNumMeshes; i++) {
			//cout << scene->mNumMeshes << endl;
			//cout << scene->mMeshes[i]->mName.data << endl;
			aiMesh* mesh = scene->mMeshes[i];

			vector<float> vert(mesh->mNumVertices * 3);
			for (int j = 0; j < mesh->mNumVertices; j++) {
				vert[j * 3 + 0] = mesh->mVertices[j].x;
				vert[j * 3 + 1] = mesh->mVertices[j].y;
				vert[j * 3 + 2] = mesh->mVertices[j].z;

			}

			vector<float> normal(vert.size());
			for (int j = 0; j < mesh->mNumVertices; j++) {
				normal[j * 3 + 0] = mesh->mNormals[j].x;
				normal[j * 3 + 1] = mesh->mNormals[j].y;
				normal[j * 3 + 2] = mesh->mNormals[j].z;
			}

			vector<float> text(mesh->mNumVertices * 2);
			for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
				text[j * 2 + 0] = mesh->mTextureCoords[0][j].x;
				text[j * 2 + 1] = -mesh->mTextureCoords[0][j].y;
			}

			vector<unsigned int> faceArray(mesh->mNumFaces * 3);
			for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
				faceArray[t * 3 + 0] = mesh->mFaces[t].mIndices[0];
				faceArray[t * 3 + 1] = mesh->mFaces[t].mIndices[1];
				faceArray[t * 3 + 2] = mesh->mFaces[t].mIndices[2];
			}


			if (scene->HasAnimations()) {

				vector< boneData > bone(mesh->mNumVertices);
				vector< Matrix4> boneOffset(mBonesName.size());
				for (int j = 0; j < mesh->mNumBones; j++) {
					for (int k = 0; k < mesh->mBones[j]->mNumWeights; k++) {
						int jointInd = searchInd(mBonesName, mesh->mBones[j]->mName.data);

						int vertInd = mesh->mBones[j]->mWeights[k].mVertexId;
						float weight = mesh->mBones[j]->mWeights[k].mWeight;

						bone[vertInd].addBoneData(jointInd, weight);

						transformMat(boneOffset[jointInd], mesh->mBones[j]->mOffsetMatrix);
					}
				}

				Skeleton* skel = new Skeleton(mGame);

				vector<Bone> bones;
				jointHerarchy(bones, scene->mRootNode, mBonesName);

				vector< Matrix4> boneO(boneOffset.size());
				boneO[0] = boneOffset[0];


				vector<Matrix4> InvBindPose(bones.size());
				computeInvBindPoseMat(InvBindPose, bones);
				skel->mName = mesh->mName.data;
				skel->mBones = bones;
				skel->mInvBindPose = InvBindPose;
				skel->mBonesOffset = boneOffset;
				transformMat(skel->mRootTransform, scene->mRootNode->mTransformation);
				skel->mRootTransform.Invert();

				AABB a = AABB(Vector3(), Vector3());
				Obj* obj = new Obj(mGame, a, this, mesh->mName.C_Str(), vert, normal, text, bone, faceArray);
			}
			else {
				AABB a = AABB(Vector3(), Vector3());

				Obj* obj = new Obj(mGame, a, this, mesh->mName.C_Str(), vert, normal, text, faceArray);

			}

		}
	}
	
}