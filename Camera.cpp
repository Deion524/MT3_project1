﻿#include "Camera.h"
#include <assert.h>
//#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

/*==================================================
				コンストラクタとデストラクタ
==================================================*/
// コンストラクタ
Camera::Camera() {

	// ワールド原点
	worldPos_ = { 0.0,0.0f,0.0f };
	// カメラの位置
	pos_ = { 12.0f,89.0f,43.0f };
	// 拡縮率
	scale_ = { 1.0f,1.0f,1.0f };
	// 角度
	theta_ = { 0.0f,0.0f,0.0f };
	// ワールド行列
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			worldMatrix_.m[i][j] = 1.0f;
		}
	}

	// グリッド線


}

// デストラクタ
Camera::~Camera() {

}


/*==================================================
					行列の積
==================================================*/
Matrix4x4 Camera::Multiply(const Matrix4x4 m1, const Matrix4x4 m2) {

	// 戻り値
	Matrix4x4 result;

	// 4x4行列の積
	// 1行目
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[1][0] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[2][0] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[3][0] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	// 2行目
	result.m[0][1] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[2][1] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[3][1] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	// 3行目
	result.m[0][2] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[1][2] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[3][2] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	// 4行目
	result.m[0][3] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[1][3] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[2][3] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	// 計算結果を返却
	return result;
}


/*==================================================
					逆行列
==================================================*/
Matrix4x4 Camera::Inverse(const Matrix4x4 m1) {

	// 戻り値
	Matrix4x4 result;

	// 逆行列の計算
	// 1行目
	result.m[0][0] = m1.m[1][1] * m1.m[2][2] * m1.m[3][3] + m1.m[1][2] * m1.m[2][3] * m1.m[3][1] + m1.m[1][3] * m1.m[2][1] * m1.m[3][2] -
		m1.m[1][3] * m1.m[2][2] * m1.m[3][1] - m1.m[1][2] * m1.m[2][1] * m1.m[3][3] - m1.m[1][1] * m1.m[2][3] * m1.m[3][2];

	result.m[1][0] = -m1.m[0][1] * m1.m[2][2] * m1.m[3][3] - m1.m[0][2] * m1.m[2][3] * m1.m[3][2] - m1.m[0][3] * m1.m[2][1] * m1.m[3][2] +
		m1.m[0][3] * m1.m[2][2] * m1.m[3][1] + m1.m[0][2] * m1.m[2][1] * m1.m[3][3] + m1.m[0][1] * m1.m[2][3] * m1.m[3][2];

	result.m[2][0] = m1.m[0][1] * m1.m[1][2] * m1.m[3][3] + m1.m[0][2] * m1.m[1][3] * m1.m[3][1] + m1.m[0][3] * m1.m[1][1] * m1.m[3][2] -
		m1.m[0][3] * m1.m[1][2] * m1.m[3][1] - m1.m[0][2] * m1.m[1][1] * m1.m[3][3] - m1.m[0][1] * m1.m[1][3] * m1.m[3][2];

	result.m[3][0] = -m1.m[0][1] * m1.m[1][2] * m1.m[2][3] - m1.m[0][2] * m1.m[1][3] * m1.m[2][1] - m1.m[0][3] * m1.m[1][1] * m1.m[2][2] +
		m1.m[0][3] * m1.m[1][2] * m1.m[2][1] + m1.m[0][2] * m1.m[1][1] * m1.m[2][3] + m1.m[0][1] * m1.m[1][3] * m1.m[2][2];

	// 2行目
	result.m[0][1] = -m1.m[1][0] * m1.m[2][2] * m1.m[3][3] - m1.m[1][2] * m1.m[2][3] * m1.m[3][0] - m1.m[1][3] * m1.m[2][0] * m1.m[3][2] +
		m1.m[1][3] * m1.m[2][2] * m1.m[3][0] + m1.m[1][2] * m1.m[2][0] * m1.m[3][3] + m1.m[1][0] * m1.m[2][3] * m1.m[3][2];

	result.m[1][1] = m1.m[0][0] * m1.m[2][2] * m1.m[3][3] + m1.m[0][2] * m1.m[2][3] * m1.m[3][0] + m1.m[0][3] * m1.m[2][0] * m1.m[3][2] -
		m1.m[0][3] * m1.m[2][2] * m1.m[3][0] - m1.m[0][2] * m1.m[2][0] * m1.m[3][3] - m1.m[0][0] * m1.m[2][3] * m1.m[3][2];

	result.m[2][1] = -m1.m[0][0] * m1.m[1][2] * m1.m[3][3] - m1.m[0][2] * m1.m[1][3] * m1.m[3][0] - m1.m[0][3] * m1.m[1][0] * m1.m[3][2] +
		m1.m[0][3] * m1.m[1][2] * m1.m[3][0] + m1.m[0][2] * m1.m[1][0] * m1.m[3][3] + m1.m[0][0] * m1.m[1][3] * m1.m[3][2];

	result.m[3][1] = m1.m[0][0] * m1.m[1][2] * m1.m[2][3] + m1.m[0][2] * m1.m[1][3] * m1.m[2][0] + m1.m[0][3] * m1.m[1][0] * m1.m[2][2] -
		m1.m[0][3] * m1.m[1][2] * m1.m[2][0] - m1.m[0][2] * m1.m[1][0] * m1.m[2][3] - m1.m[0][0] * m1.m[1][3] * m1.m[2][2];

	// 3行目
	result.m[0][2] = m1.m[1][0] * m1.m[2][1] * m1.m[3][3] + m1.m[1][1] * m1.m[2][3] * m1.m[3][0] + m1.m[1][3] * m1.m[2][0] * m1.m[3][1] -
		m1.m[1][3] * m1.m[2][1] * m1.m[3][0] - m1.m[1][1] * m1.m[2][0] * m1.m[3][3] - m1.m[1][0] * m1.m[2][3] * m1.m[3][1];

	result.m[1][2] = -m1.m[0][0] * m1.m[2][1] * m1.m[3][3] - m1.m[0][1] * m1.m[2][3] * m1.m[3][0] - m1.m[0][3] * m1.m[2][0] * m1.m[3][1] +
		m1.m[0][3] * m1.m[2][1] * m1.m[3][0] + m1.m[0][1] * m1.m[2][0] * m1.m[3][3] + m1.m[0][0] * m1.m[2][3] * m1.m[3][1];

	result.m[2][2] = m1.m[0][0] * m1.m[1][1] * m1.m[3][3] + m1.m[0][1] * m1.m[1][3] * m1.m[3][0] + m1.m[0][3] * m1.m[1][0] * m1.m[3][1] -
		m1.m[0][3] * m1.m[1][1] * m1.m[3][0] - m1.m[0][1] * m1.m[1][0] * m1.m[3][3] - m1.m[0][0] * m1.m[1][3] * m1.m[3][1];

	result.m[3][2] = -m1.m[0][0] * m1.m[1][1] * m1.m[2][3] - m1.m[0][1] * m1.m[1][3] * m1.m[2][0] - m1.m[0][3] * m1.m[1][0] * m1.m[2][1] +
		m1.m[0][3] * m1.m[1][1] * m1.m[2][0] + m1.m[0][1] * m1.m[1][0] * m1.m[2][3] + m1.m[0][0] * m1.m[1][3] * m1.m[2][1];

	// 4行目
	result.m[0][3] = -m1.m[1][0] * m1.m[2][1] * m1.m[3][2] - m1.m[1][1] * m1.m[2][2] * m1.m[3][0] - m1.m[1][2] * m1.m[2][0] * m1.m[3][1] +
		m1.m[1][2] * m1.m[2][1] * m1.m[3][0] + m1.m[1][1] * m1.m[2][0] * m1.m[3][2] + m1.m[1][0] * m1.m[2][2] * m1.m[3][1];

	result.m[1][3] = m1.m[0][0] * m1.m[2][1] * m1.m[3][2] + m1.m[0][1] * m1.m[2][2] * m1.m[3][0] + m1.m[0][2] * m1.m[2][0] * m1.m[3][1] -
		m1.m[0][2] * m1.m[2][1] * m1.m[3][0] - m1.m[0][1] * m1.m[2][0] * m1.m[3][2] - m1.m[0][0] * m1.m[2][2] * m1.m[3][1];

	result.m[2][3] = -m1.m[0][0] * m1.m[1][1] * m1.m[3][2] - m1.m[0][1] * m1.m[1][2] * m1.m[3][0] - m1.m[0][2] * m1.m[1][0] * m1.m[3][1] +
		m1.m[0][2] * m1.m[1][1] * m1.m[3][0] + m1.m[0][1] * m1.m[1][2] * m1.m[2][0] + m1.m[0][0] * m1.m[1][2] * m1.m[3][1];

	result.m[3][3] = m1.m[0][0] * m1.m[1][1] * m1.m[2][2] + m1.m[0][1] * m1.m[1][2] * m1.m[2][0] + m1.m[0][2] * m1.m[1][0] * m1.m[2][1] -
		m1.m[0][2] * m1.m[1][1] * m1.m[2][0] - m1.m[0][1] * m1.m[1][0] * m1.m[2][2] - m1.m[0][0] * m1.m[1][2] * m1.m[2][1];

	// 計算結果を返却
	return result;
}


/*==================================================
					拡大縮小行列
==================================================*/
Matrix4x4 Camera::MakeScaleMatrix(Vector3 scale) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}

	// 拡縮の計算
	result.m[0][0] = scale.x;
	result.m[1][1] = scale.y;
	result.m[2][2] = scale.z;
	result.m[3][3] = 1.0f;

	// 返却する値
	return result;
}


/*==================================================
					平行移動行列
==================================================*/
Matrix4x4 Camera::Translate(Vector3 translate) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}

	// 平行移動行列の作成
	result.m[0][0] = 1.0f;
	result.m[1][1] = 1.0f;
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	// 返却する値
	return result;
}


/*==================================================
					回転行列
==================================================*/
// XY軸の回転
Matrix4x4 Camera::MakeXYRotateMatrix(float theta) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}

	// 回転行列の作成
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = cosf(theta);
	result.m[1][0] = sinf(theta);

	result.m[0][1] = -sinf(theta);
	result.m[1][1] = cosf(theta);

	// 返却する値
	return result;
}

// XZ軸の回転
Matrix4x4 Camera::MakeXZRotateMatrix(float theta) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}

	// 回転行列の作成
	result.m[1][1] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[0][0] = cosf(theta);
	result.m[2][0] = -sinf(theta);

	result.m[0][2] = sinf(theta);
	result.m[2][2] = cosf(theta);

	// 返却する値
	return result;
}

// YZ軸の回転
Matrix4x4 Camera::MakeYZRotateMatrix(float theta) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}

	// 回転行列の作成
	result.m[0][0] = 1.0f;
	result.m[3][3] = 1.0f;

	result.m[1][1] = cosf(theta);
	result.m[2][1] = sinf(theta);

	result.m[1][2] = -sinf(theta);
	result.m[2][2] = cosf(theta);

	// 返却する値
	return result;
}


/*==================================================
					アフィン変換
==================================================*/
Matrix4x4 Camera::MakeAffineMatrix(Vector3 scale, Vector3 theta, Vector3 translate) {

	// 戻り値
	Matrix4x4 scaleMatrix;
	Matrix4x4 rotateXYMatrix;
	Matrix4x4 rotateXZMatrix;
	Matrix4x4 rotateYZMatrix;
	Matrix4x4 rotateMatrix;
	Matrix4x4 translateMatrix;
	Matrix4x4 resultMatrix;

	// 各行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			scaleMatrix.m[i][j] = 0.0f;
			rotateXYMatrix.m[i][j] = 0.0f;
			rotateXZMatrix.m[i][j] = 0.0f;
			rotateYZMatrix.m[i][j] = 0.0f;
			translateMatrix.m[i][j] = 0.0f;
			resultMatrix.m[i][j] = 0.0f;
		}
	}
	// 行列の計算(拡縮)
	scaleMatrix.m[0][0] = scale.x;
	scaleMatrix.m[1][1] = scale.y;
	scaleMatrix.m[2][2] = scale.z;
	scaleMatrix.m[3][3] = 1.0f;

	// 行列の計算(回転XY)
	rotateXYMatrix.m[2][2] = 1.0f;
	rotateXYMatrix.m[3][3] = 1.0f;
	rotateXYMatrix.m[0][0] = cosf(theta.z);
	rotateXYMatrix.m[1][0] = sinf(theta.z);
	rotateXYMatrix.m[0][1] = -sinf(theta.z);
	rotateXYMatrix.m[1][1] = cosf(theta.z);
	// 行列の計算(回転XZ)
	rotateXZMatrix.m[1][1] = 1.0f;
	rotateXZMatrix.m[3][3] = 1.0f;
	rotateXZMatrix.m[0][0] = cosf(theta.y);
	rotateXZMatrix.m[2][0] = -sinf(theta.y);
	rotateXZMatrix.m[0][2] = sinf(theta.y);
	rotateXZMatrix.m[2][2] = cosf(theta.y);
	// 行列の計算(回転YZ)
	rotateYZMatrix.m[0][0] = 1.0f;
	rotateYZMatrix.m[3][3] = 1.0f;
	rotateYZMatrix.m[1][1] = cosf(theta.x);
	rotateYZMatrix.m[2][1] = sinf(theta.x);
	rotateYZMatrix.m[1][2] = -sinf(theta.x);
	rotateYZMatrix.m[2][2] = cosf(theta.x);
	// 回転行列の結合
	rotateMatrix = Multiply(rotateXYMatrix, Multiply(rotateXZMatrix, rotateYZMatrix));

	// 行列の計算(移動)
	translateMatrix.m[0][0] = 1.0f;
	translateMatrix.m[1][1] = 1.0f;
	translateMatrix.m[2][2] = 1.0f;
	translateMatrix.m[3][3] = 1.0f;

	translateMatrix.m[3][0] = translate.x;
	translateMatrix.m[3][1] = translate.y;
	translateMatrix.m[3][2] = translate.z;

	// アフィン変換(拡縮、回転)
	resultMatrix = Multiply(scaleMatrix, rotateMatrix);

	// アフィン変換(+移動)
	resultMatrix = Multiply(resultMatrix, translateMatrix);

	// 返却する値
	return resultMatrix;
}


/*==================================================
				Vector3を同時座標系に変換
==================================================*/
Vector3 Camera::Transform(const Vector3& vector, const Matrix4x4& matrix) {

	// 戻り値
	Vector3 result;

	// 計算
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + 1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + 1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + 1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + 1.0f * matrix.m[3][3];

	// アサーションチェック
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	// 返却する値
	return result;
}


/*==================================================
				行列の中身を描画
==================================================*/
void Camera::Matrix4x4ScreenPrintf(Matrix4x4 matrix, float posX, float posY) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			Novice::ScreenPrintf(static_cast<int>(posX + 128.0f * j), static_cast<int>(posY + 32.0f * i), "%0.2f", matrix.m[j][i]);
		}
	}
}


/*==================================================
					正射影行列
==================================================*/
Matrix4x4 Camera::MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearVal, float farVal) {

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
	result.m[2][2] = 1.0f / (farVal - nearVal);
	result.m[0][3] = (left + right) / (left - right);
	result.m[1][3] = (top + bottom) / (bottom - top);
	result.m[2][3] = nearVal / (nearVal - farVal);
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
Matrix4x4 Camera::MakePerspectiveForMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {

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
