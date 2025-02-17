#pragma once
#include "Matrix4x4.h"

class Camera{
public:
	Camera();
	~Camera();
public:
	// メンバ関数
	// 正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom,float near,float far);
	// ビューポート行列
	Matrix4x4 MakeViewPortMatrix(float left, float top, float width, float height,float minDepth,float maxDepth);
	// 透視投影行列
	Matrix4x4 MakePerspectiveForMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

private:
	// メンバ変数
};

