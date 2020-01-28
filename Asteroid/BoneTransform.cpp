#include "BoneTransform.h"

Matrix4 BoneTransform::toMatrix() {
	
	return matrix;
}

Matrix4 BoneTransform::Interpolate(BoneTransform& a, BoneTransform& b, float f) {

	Quaternion q = Quaternion::Slerp(a.rotation, b.rotation , f);
	Vector3 t = Vector3::Lerp(a.position, b.position, f);

	Matrix4 mat = Matrix4::createFromTrans(t) * Matrix4::createFromQuater(q);

	return mat;
}

