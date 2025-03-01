#include "Camera.h"
#include <assert.h>
//#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

#ifdef _DEBUG
#include <imgui.h>
#endif // _DEBUG


/*==================================================
				コンストラクタとデストラクタ
==================================================*/
// コンストラクタ
Camera::Camera() {

	// ワールド原点
	worldPos_ = { 0.0,0.0f,0.0f };
	// 各行列の初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			// ワールド行列
			worldMatrix_.m[i][j] = 0.0f;
			// カメラ行列
			cameraMatrix_.m[i][j] = 0.0f;
			// ビュー行列
			viewMatrix_.m[i][j] = 0.0f;
			// 正射影行列
			projectionMatrix_.m[i][j] = 0.0f;
			// 透視投影行列
			perspectiveDevide_.m[i][j] = 0.0f;
			// ビューポート行列
			viewportMatrix_.m[i][j] = 0.0f;
			// WVP行列
			wvpMatrix_.m[i][j] = 0.0f;
			// スクリーン
			wvppVpMatrix_.m[i][j] = 0.0f;
		}
	}

	// カメラの位置
	pos_ = { 0.0,200.0f,-1.0f };
	// 拡縮率
	scale_ = { 1.0f,1.0f,1.0f };
	// 角度
	theta_ = { 0.0f,0.0f,0.0f };

	// カメラの幅高さ
	width_ = 1280.0f;;
	height_ = 720.0f;
	// 近平面
	nearClip_ = 0.1f;
	// 遠平面
	farClip_ = 1000.0f;
	// 画角
	fovY_ = 1.0f;
	// アスペクト比
	aspectRatio_ = height_ / width_;
	// 最小深度値
	minDepth_ = 0.0f;
	// 最大深度値
	maxDepth_ = 1.0f;

	// グリッド線(横)
	gridLineGreenStart_ = { -width_,0.0f,0.0f };
	gridLineGreenEnd_ = { width_,0.0f,0.0f };
	screenGridLineGreenStart_ = gridLineGreenStart_;
	screenGridLineGreenEnd_ = gridLineGreenEnd_;
	// グリッド線(縦)
	gridLineRedStart_ = { 0.0f,-height_,0.0f };
	gridLineRedEnd_ = { 0.0f,height_,0.0f };
	screenGridLineRedStart_ = gridLineRedStart_;
	screenGridLineRedEnd_ = gridLineRedEnd_;


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
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];
	// 2行目
	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];
	// 3行目
	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];
	// 4行目
	result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
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

	result.m[0][1] = -m1.m[0][1] * m1.m[2][2] * m1.m[3][3] - m1.m[0][2] * m1.m[2][3] * m1.m[3][2] - m1.m[0][3] * m1.m[2][1] * m1.m[3][2] +
		m1.m[0][3] * m1.m[2][2] * m1.m[3][1] + m1.m[0][2] * m1.m[2][1] * m1.m[3][3] + m1.m[0][1] * m1.m[2][3] * m1.m[3][2];

	result.m[0][2] = m1.m[0][1] * m1.m[1][2] * m1.m[3][3] + m1.m[0][2] * m1.m[1][3] * m1.m[3][1] + m1.m[0][3] * m1.m[1][1] * m1.m[3][2] -
		m1.m[0][3] * m1.m[1][2] * m1.m[3][1] - m1.m[0][2] * m1.m[1][1] * m1.m[3][3] - m1.m[0][1] * m1.m[1][3] * m1.m[3][2];

	result.m[0][3] = -m1.m[0][1] * m1.m[1][2] * m1.m[2][3] - m1.m[0][2] * m1.m[1][3] * m1.m[2][1] - m1.m[0][3] * m1.m[1][1] * m1.m[2][2] +
		m1.m[0][3] * m1.m[1][2] * m1.m[2][1] + m1.m[0][2] * m1.m[1][1] * m1.m[2][3] + m1.m[0][1] * m1.m[1][3] * m1.m[2][2];

	// 2行目
	result.m[1][0] = -m1.m[1][0] * m1.m[2][2] * m1.m[3][3] - m1.m[1][2] * m1.m[2][3] * m1.m[3][0] - m1.m[1][3] * m1.m[2][0] * m1.m[3][2] +
		m1.m[1][3] * m1.m[2][2] * m1.m[3][0] + m1.m[1][2] * m1.m[2][0] * m1.m[3][3] + m1.m[1][0] * m1.m[2][3] * m1.m[3][2];

	result.m[1][1] = m1.m[0][0] * m1.m[2][2] * m1.m[3][3] + m1.m[0][2] * m1.m[2][3] * m1.m[3][0] + m1.m[0][3] * m1.m[2][0] * m1.m[3][2] -
		m1.m[0][3] * m1.m[2][2] * m1.m[3][0] - m1.m[0][2] * m1.m[2][0] * m1.m[3][3] - m1.m[0][0] * m1.m[2][3] * m1.m[3][2];

	result.m[1][2] = -m1.m[0][0] * m1.m[1][2] * m1.m[3][3] - m1.m[0][2] * m1.m[1][3] * m1.m[3][0] - m1.m[0][3] * m1.m[1][0] * m1.m[3][2] +
		m1.m[0][3] * m1.m[1][2] * m1.m[3][0] + m1.m[0][2] * m1.m[1][0] * m1.m[3][3] + m1.m[0][0] * m1.m[1][3] * m1.m[3][2];

	result.m[1][3] = m1.m[0][0] * m1.m[1][2] * m1.m[2][3] + m1.m[0][2] * m1.m[1][3] * m1.m[2][0] + m1.m[0][3] * m1.m[1][0] * m1.m[2][2] -
		m1.m[0][3] * m1.m[1][2] * m1.m[2][0] - m1.m[0][2] * m1.m[1][0] * m1.m[2][3] - m1.m[0][0] * m1.m[1][3] * m1.m[2][2];

	// 3行目
	result.m[2][0] = m1.m[1][0] * m1.m[2][1] * m1.m[3][3] + m1.m[1][1] * m1.m[2][3] * m1.m[3][0] + m1.m[1][3] * m1.m[2][0] * m1.m[3][1] -
		m1.m[1][3] * m1.m[2][1] * m1.m[3][0] - m1.m[1][1] * m1.m[2][0] * m1.m[3][3] - m1.m[1][0] * m1.m[2][3] * m1.m[3][1];

	result.m[2][1] = -m1.m[0][0] * m1.m[2][1] * m1.m[3][3] - m1.m[0][1] * m1.m[2][3] * m1.m[3][0] - m1.m[0][3] * m1.m[2][0] * m1.m[3][1] +
		m1.m[0][3] * m1.m[2][1] * m1.m[3][0] + m1.m[0][1] * m1.m[2][0] * m1.m[3][3] + m1.m[0][0] * m1.m[2][3] * m1.m[3][1];

	result.m[2][2] = m1.m[0][0] * m1.m[1][1] * m1.m[3][3] + m1.m[0][1] * m1.m[1][3] * m1.m[3][0] + m1.m[0][3] * m1.m[1][0] * m1.m[3][1] -
		m1.m[0][3] * m1.m[1][1] * m1.m[3][0] - m1.m[0][1] * m1.m[1][0] * m1.m[3][3] - m1.m[0][0] * m1.m[1][3] * m1.m[3][1];

	result.m[2][3] = -m1.m[0][0] * m1.m[1][1] * m1.m[2][3] - m1.m[0][1] * m1.m[1][3] * m1.m[2][0] - m1.m[0][3] * m1.m[1][0] * m1.m[2][1] +
		m1.m[0][3] * m1.m[1][1] * m1.m[2][0] + m1.m[0][1] * m1.m[1][0] * m1.m[2][3] + m1.m[0][0] * m1.m[1][3] * m1.m[2][1];

	// 4行目
	result.m[3][0] = -m1.m[1][0] * m1.m[2][1] * m1.m[3][2] - m1.m[1][1] * m1.m[2][2] * m1.m[3][0] - m1.m[1][2] * m1.m[2][0] * m1.m[3][1] +
		m1.m[1][2] * m1.m[2][1] * m1.m[3][0] + m1.m[1][1] * m1.m[2][0] * m1.m[3][2] + m1.m[1][0] * m1.m[2][2] * m1.m[3][1];

	result.m[3][1] = m1.m[0][0] * m1.m[2][1] * m1.m[3][2] + m1.m[0][1] * m1.m[2][2] * m1.m[3][0] + m1.m[0][2] * m1.m[2][0] * m1.m[3][1] -
		m1.m[0][2] * m1.m[2][1] * m1.m[3][0] - m1.m[0][1] * m1.m[2][0] * m1.m[3][2] - m1.m[0][0] * m1.m[2][2] * m1.m[3][1];

	result.m[3][2] = -m1.m[0][0] * m1.m[1][1] * m1.m[3][2] - m1.m[0][1] * m1.m[1][2] * m1.m[3][0] - m1.m[0][2] * m1.m[1][0] * m1.m[3][1] +
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
Matrix4x4 Camera::MakeXYRotateMatrix(float roll) {

	// 戻り値
	Matrix4x4 result;

	// 行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
		}
	}

	// 回転行列の作成
	result.m[0][0] = cosf(roll);
	result.m[0][1] = sinf(roll);

	result.m[1][0] = -sinf(roll);
	result.m[1][1] = cosf(roll);

	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;

	// 返却する値
	return result;
}

// XZ軸の回転
Matrix4x4 Camera::MakeXZRotateMatrix(float yaw) {

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

	result.m[0][0] = cosf(yaw);
	result.m[2][0] = sinf(yaw);

	result.m[0][2] = -sinf(yaw);
	result.m[2][2] = cosf(yaw);

	// 返却する値
	return result;
}

// YZ軸の回転
Matrix4x4 Camera::MakeYZRotateMatrix(float pitch) {

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

	result.m[1][1] = cosf(pitch);
	result.m[2][1] = -sinf(pitch);

	result.m[1][2] = sinf(pitch);
	result.m[2][2] = cosf(pitch);

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
	rotateXYMatrix = MakeXYRotateMatrix(theta.z);
	// 行列の計算(回転XZ)
	rotateXZMatrix = MakeXZRotateMatrix(theta.y);
	// 行列の計算(回転YZ)
	rotateYZMatrix = MakeYZRotateMatrix(theta.x);
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
			Novice::ScreenPrintf(static_cast<int>(posX + 128.0f * j), static_cast<int>(posY + 32.0f * i), "%0.2f", matrix.m[i][j]);
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
	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearVal / (nearVal - farVal);
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
	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
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
	result.m[2][3] = 1.0f;
	result.m[3][2] = -(nearClip * farClip) / (farClip - nearClip);

	// 返却する値
	return result;
}


/*==================================================
					移動処理
==================================================*/
void Camera::Move(char* keys) {
	// 上下に移動
	if (keys[DIK_W]) {
		pos_.y += 6.0f;
	} else if (keys[DIK_S]) {
		pos_.y -= 6.0f;
	}
	// 左右に移動
	if (keys[DIK_D]) {
		pos_.x += 6.0f;
	} else if (keys[DIK_A]) {
		pos_.x -= 6.0f;
	}
}


/*==================================================
				デバッグウィンドウ
==================================================*/
void Camera::DebugWindow() {
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat("Translate X ", &pos_.x, 2.0f, -1000.0f, 1000.0f, "%0.2f");
	ImGui::DragFloat("Translate Y ", &pos_.y, 2.0f, -1000.0f, 1000.0f, "%0.2f");
	ImGui::DragFloat("Translate Z ", &pos_.z, 2.0f, -1000.0f, 1000.0f, "%0.2f");
	ImGui::DragFloat("FovY ", &fovY_, 0.1f, -100.0f, 100.0f, "%0.2f");
	ImGui::SliderFloat("Pitch", &theta_.x, -10.0f, 10.0f, "%0.2f");
	ImGui::SliderFloat("Yaw", &theta_.y, -10.0f, 10.0f, "%0.2f");
	ImGui::SliderFloat("Roll", &theta_.z, -10.0f, 10.0f, "%0.2f");
	ImGui::End();
#endif // _DEBUG

}

/*==================================================
					更新処理
==================================================*/
void Camera::Update() {

	// レンダリングパイプライン(wvppVp行列作成)
	// ワールド
	worldMatrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
	// カメラ
	cameraMatrix_ = MakeAffineMatrix(scale_, theta_, pos_);
	// ビュー
	viewMatrix_ = Inverse(cameraMatrix_);
	// 同時クリップ
	perspectiveDevide_ = MakePerspectiveForMatrix(fovY_, aspectRatio_, nearClip_, farClip_);
	// 正規化デバイス
	projectionMatrix_ = MakeOrthographicMatrix(-width_ / 2.0f, height_ / 2.0f, width_ / 2.0f, -height_ / 2.0f, nearClip_, farClip_);
	// ビューポート
	viewportMatrix_ = MakeViewPortMatrix(0, 0, width_, height_, minDepth_, maxDepth_);
	// スクリーン
	wvppVpMatrix_ = Multiply(viewMatrix_, perspectiveDevide_);
	wvppVpMatrix_ = Multiply(wvppVpMatrix_, projectionMatrix_);
	wvppVpMatrix_ = Multiply(wvppVpMatrix_, viewportMatrix_);

	// WVP行列
	//wvpMatrix_ = Multiply(worldMatrix_, Multiply(viewMatrix_, projectionMatrix_));
	wvpMatrix_ = Multiply(viewMatrix_, Multiply(perspectiveDevide_, projectionMatrix_));

}

/*==================================================
				グリッド線の描画処理
==================================================*/
void Camera::GridLineDraw() {
	// 横線(緑)
	Novice::DrawLine(
		static_cast<int>(screenGridLineGreenStart_.x), static_cast<int>(screenGridLineGreenStart_.y),
		static_cast<int>(screenGridLineGreenEnd_.x), static_cast<int>(screenGridLineGreenEnd_.y),
		0x00FF00FF
	);
	// 縦線(赤)
	Novice::DrawLine(
		static_cast<int>(screenGridLineRedStart_.x), static_cast<int>(screenGridLineRedStart_.y),
		static_cast<int>(screenGridLineRedEnd_.x), static_cast<int>(screenGridLineRedEnd_.y),
		0x00FF00FF
	);
}