#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"

class Camera{
public:
	Camera();
	~Camera();
public:
	// メンバ関数
	
	// 行列の積
	Matrix4x4 Multiply(Matrix4x4 m1, Matrix4x4 m2);
	// 逆行列
	Matrix4x4 Inverse(Matrix4x4 m1);
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
	Matrix4x4 MakeAffineMatrix(Vector3 scale, Vector3 theta, Vector3 translate);
	// 同時座標に変換
	Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
	// スクリーンに行列の中身を描画
	void Matrix4x4ScreenPrintf(Matrix4x4 matrix, float posX, float posY);
	 
	// 正射影行列
	Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom,float nearVal,float farVal);
	// ビューポート行列
	Matrix4x4 MakeViewPortMatrix(float left, float top, float width, float height,float minDepth,float maxDepth);
	// 透視投影行列
	Matrix4x4 MakePerspectiveForMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//private:
public:
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
	// 拡縮率
	Vector3 scale_;
	// 角度
	Vector3 theta_;

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

