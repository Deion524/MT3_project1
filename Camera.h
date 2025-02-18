#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <assert.h>
//#define _USE_MATH_DEFINES
#include <math.h>

class Camera{
public:
	Camera();
	~Camera();
public:
	// メンバ関数
	
	// 行列の積
	Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);
	// 逆行列
	Matrix4x4 Inverse(const Matrix4x4 m1);
	// 拡大縮小行列
	Matrix4x4 MakeScaleMatrix(Vector3 scale);
	// 平行移動行列
	Matrix4x4 Translate(Vector3 translate);
	// 回転行列(Z軸中心)
	Matrix4x4 MakeXYRotateMatrix(float theta);
	// 回転行列(Y軸中心)
	Matrix4x4 MakeXZRotateMatrix(float theta);
	// 回転行列(X軸中心)
	Matrix4x4 MakeYZRotateMatrix(float theta);
	// アフィン行列
	Matrix4x4 MakeAffineMatrix(Vector3 scale, Matrix4x4 rotateMatrix, Vector3 translate);
	// 同時座標に変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	 
	// 正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom,float near,float far);
	// ビューポート行列
	Matrix4x4 MakeViewPortMatrix(float left, float top, float width, float height,float minDepth,float maxDepth);
	// 透視投影行列
	Matrix4x4 MakePerspectiveForMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

private:
	// メンバ変数

	// ワールド原点
	Vector3 worldPos_;
	// ワールド行列
	Matrix4x4 worldMatrix_;
	// ビュー行列
	Matrix4x4 viewMatrix_;
	// 正射影行列
	Matrix4x4 projectionMatrix_;
	// 透視投影行列
	Matrix4x4 perspectiveDevide_;
	// ビューポート行列
	Matrix4x4 viewportMatrix_;
	// スクリーン
	Matrix4x4 wvpVpMatrix_;

	// カメラの位置
	Vector3 pos_;
	// カメラの幅高さ
	float width_;
	float height_;
	// 近平面
	float near_;
	// 遠平面
	float far_;
	// 画角
	float fovY_;
	// アスペクト比
	float aspectRatio_;
	// 最小深度値
	float minDepth_;
	// 最大深度値
	float maxDepth_;

	// グリッド線(横)
	Vector3 gridLineGreenStart_;
	Vector3 gridLineGreenEnd_;
	// グリッド線(縦)
	Vector3 gridLineRedStart_;
	Vector3 gridLineRedEnd_;

};

