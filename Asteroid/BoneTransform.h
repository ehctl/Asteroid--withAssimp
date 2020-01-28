#pragma once
#include "Math.h"
#include "ObjFile.h"

struct BoneTransform {
public:
	static Matrix4 Interpolate(BoneTransform& a, BoneTransform& b, float f);

	Matrix4 toMatrix();
	Vector3 position;
	Quaternion rotation;
	Matrix4 matrix;
};