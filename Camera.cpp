#include "Camera.h"
#include <math.h>
#include <assert.h>

/*==================================================
				コンストラクタとデストラクタ
==================================================*/
// コンストラクタ
Camera::Camera() {

}

// デストラクタ
Camera::~Camera() {

}

/*==================================================
					正射影行列
==================================================*/
Matrix4x4 Camera::MakeOrthographicMatrix(float left, float top, float right, float bottom, float near, float far) {

	// 戻り値
	Matrix4x4 result;

	// 中身の初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}
	// 中身を代入
	result.m[0][0] = 2.0f / (right - left);
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[2][2] = 1.0f / (far - near);
	result.m[0][3] = (left + right) / (left - right);
	result.m[1][3] = (top + bottom) / (bottom - top);
	result.m[2][3] = near / (near - far);
	result.m[3][3] = 1.0f;

	// 返却する値
	return result;
}

/*==================================================
					ビューポート行列
==================================================*/
Matrix4x4 Camera::MakeViewPortMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {

	// 戻り値
	Matrix4x4 result;

	// 中身の初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}
	// 中身を代入
	result.m[0][0] = width / 2.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[2][2] = maxDepth - minDepth;
	result.m[0][3] = left + width / 2.0f;
	result.m[1][3] = top + height / 2.0f;
	result.m[2][3] = minDepth;
	result.m[3][3] = 1.0f;

	// 返却する値
	return result;

}

/*==================================================
					透視投影行列
==================================================*/
Matrix4x4 MakePerspectiveForMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}
	// 透視投影行列の作成
	result.m[0][0] = (1.0f / aspectRatio) * (1.0f / tanf(fovY / 2.0f));
	result.m[1][1] = 1.0f / tanf(fovY / 2.0f);
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[3][2] = 1.0f;
	result.m[2][3] = -(nearClip * farClip) / (farClip - nearClip);

	// 返却する値
	return result;
}
