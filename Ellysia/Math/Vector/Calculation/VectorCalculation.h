#pragma once
#include <Math/Vector/Vector3.h>
#include <Math/Matrix/Matrix/Matrix4x4.h>
#include <cassert>

//Vector3

//足し算
Vector3 Add(Vector3 v1, Vector3 v2);

//引き算
Vector3 Subtract(Vector3 v1, Vector3 v2);

namespace vector {
	Vector3 Transform(const Vector3 vector, const Matrix4x4 matrix);
}