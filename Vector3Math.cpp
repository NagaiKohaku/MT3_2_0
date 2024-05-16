#include "Vector3Math.h"
#include "math.h"

//加算
Vector3 Vector3Math::Add(const Vector3& v1, const Vector3& v2) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;

}

//減算
Vector3 Vector3Math::Subtract(const Vector3& v1, const Vector3& v2) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;

}

//スカラー倍
Vector3 Vector3Math::Multiply(float scalar, const Vector3& v) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;

	return result;

}

//内積
float Vector3Math::Dot(const Vector3& v1, const Vector3& v2) {

	float result = 0.0f;

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;

}

//長さ(ノルム)
float Vector3Math::Length(const Vector3& v) {

	float result = 0.0f;

	result = sqrtf(Dot(v, v));

	return result;

}


//正規化
Vector3 Vector3Math::Normalize(const Vector3& v) {

	Vector3 result{ 0.0f,0.0f,0.0f };

	result.x = v.x / Length(v);
	result.y = v.y / Length(v);
	result.z = v.z / Length(v);

	return result;

}
