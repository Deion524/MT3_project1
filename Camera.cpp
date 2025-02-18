#include "Camera.h"

/*==================================================
				コンストラクタとデストラクタ
==================================================*/
// コンストラクタ
Camera::Camera() {

	// ワールド原点
	worldPos_ = { 0.0,0.0f,0.0f };
	// カメラの位置
	pos_ = { 0.0f,0.0f,0.0f };
	// ワールド行列
	//worldMatrix_=MakeAffineMatrix()
	// グリッド線
	

}

// デストラクタ
Camera::~Camera() {

}

/*==================================================
					行列の積
==================================================*/
Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2) {

	// 戻り値
	Matrix4x4 result;

	// 4x4行列の積
	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

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
Matrix4x4 Inverse(const Matrix4x4 m1) {

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
Matrix4x4 MakeScaleMatrix(Vector3 scale) {

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
Matrix4x4 Translate(Vector3 translate) {

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

	result.m[0][0] = translate.x;
	result.m[0][1] = translate.y;
	result.m[0][2] = translate.z;

	// 返却する値
	return result;
}

/*==================================================
					回転行列
==================================================*/
// XY軸の回転
Matrix4x4 MakeXYRotateMatrix(float theta) {

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
Matrix4x4 MakeXZRotateMatrix(float theta) {

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
Matrix4x4 MakeYZRotateMatrix(float theta) {

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
Matrix4x4 MakeAffineMatrix(Vector3 scale, Matrix4x4 rotateMatrix, Vector3 translate) {

	// 戻り値
	Matrix4x4 scaleMatrix;
	Matrix4x4 translateMatrix;
	Matrix4x4 resultMatrix;

	// 各行列の中身を初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			scaleMatrix.m[i][j] = 0.0f;
			translateMatrix.m[i][j] = 0.0f;
			resultMatrix.m[i][j] = 0.0f;
		}
	}
	// 行列の計算(拡縮)
	resultMatrix.m[0][0] = scale.x;
	resultMatrix.m[1][1] = scale.y;
	resultMatrix.m[2][2] = scale.z;
	resultMatrix.m[3][3] = 1.0f;

	// 行列の計算(移動)
	resultMatrix.m[0][0] = 1.0f;
	resultMatrix.m[1][1] = 1.0f;
	resultMatrix.m[2][2] = 1.0f;
	resultMatrix.m[3][3] = 1.0f;

	resultMatrix.m[0][0] = translate.x;
	resultMatrix.m[0][1] = translate.y;
	resultMatrix.m[0][2] = translate.z;

	// アフィン変換(拡縮、回転)
	// 1行目
	resultMatrix.m[0][0] = scaleMatrix.m[0][0] * rotateMatrix.m[0][0] + scaleMatrix.m[1][0] * rotateMatrix.m[0][1] + scaleMatrix.m[2][0] * rotateMatrix.m[0][2] + scaleMatrix.m[3][0] * rotateMatrix.m[0][3];
	resultMatrix.m[0][1] = scaleMatrix.m[0][0] * rotateMatrix.m[1][0] + scaleMatrix.m[1][0] * rotateMatrix.m[1][1] + scaleMatrix.m[2][0] * rotateMatrix.m[1][2] + scaleMatrix.m[3][0] * rotateMatrix.m[1][3];
	resultMatrix.m[0][2] = scaleMatrix.m[0][0] * rotateMatrix.m[2][0] + scaleMatrix.m[1][0] * rotateMatrix.m[2][1] + scaleMatrix.m[2][0] * rotateMatrix.m[2][2] + scaleMatrix.m[3][0] * rotateMatrix.m[2][3];
	resultMatrix.m[0][3] = scaleMatrix.m[0][0] * rotateMatrix.m[3][0] + scaleMatrix.m[1][0] * rotateMatrix.m[3][1] + scaleMatrix.m[2][0] * rotateMatrix.m[3][2] + scaleMatrix.m[3][0] * rotateMatrix.m[3][3];
	// 2行目
	resultMatrix.m[1][0] = scaleMatrix.m[0][1] * rotateMatrix.m[0][0] + scaleMatrix.m[1][1] * rotateMatrix.m[0][1] + scaleMatrix.m[2][1] * rotateMatrix.m[0][2] + scaleMatrix.m[3][1] * rotateMatrix.m[0][3];
	resultMatrix.m[1][1] = scaleMatrix.m[0][1] * rotateMatrix.m[1][0] + scaleMatrix.m[1][1] * rotateMatrix.m[1][1] + scaleMatrix.m[2][1] * rotateMatrix.m[1][2] + scaleMatrix.m[3][1] * rotateMatrix.m[1][3];
	resultMatrix.m[1][2] = scaleMatrix.m[0][1] * rotateMatrix.m[2][0] + scaleMatrix.m[1][1] * rotateMatrix.m[2][1] + scaleMatrix.m[2][1] * rotateMatrix.m[2][2] + scaleMatrix.m[3][1] * rotateMatrix.m[2][3];
	resultMatrix.m[1][3] = scaleMatrix.m[0][1] * rotateMatrix.m[3][0] + scaleMatrix.m[1][1] * rotateMatrix.m[3][1] + scaleMatrix.m[2][1] * rotateMatrix.m[3][2] + scaleMatrix.m[3][1] * rotateMatrix.m[3][3];
	// 3行目
	resultMatrix.m[2][0] = scaleMatrix.m[0][2] * rotateMatrix.m[0][0] + scaleMatrix.m[1][2] * rotateMatrix.m[0][1] + scaleMatrix.m[2][2] * rotateMatrix.m[0][2] + scaleMatrix.m[3][2] * rotateMatrix.m[0][3];
	resultMatrix.m[2][1] = scaleMatrix.m[0][2] * rotateMatrix.m[1][0] + scaleMatrix.m[1][2] * rotateMatrix.m[1][1] + scaleMatrix.m[2][2] * rotateMatrix.m[1][2] + scaleMatrix.m[3][2] * rotateMatrix.m[1][3];
	resultMatrix.m[2][2] = scaleMatrix.m[0][2] * rotateMatrix.m[2][0] + scaleMatrix.m[1][2] * rotateMatrix.m[2][1] + scaleMatrix.m[2][2] * rotateMatrix.m[2][2] + scaleMatrix.m[3][2] * rotateMatrix.m[2][3];
	resultMatrix.m[2][3] = scaleMatrix.m[0][2] * rotateMatrix.m[3][0] + scaleMatrix.m[1][2] * rotateMatrix.m[3][1] + scaleMatrix.m[2][2] * rotateMatrix.m[3][2] + scaleMatrix.m[3][2] * rotateMatrix.m[3][3];
	// 4行目
	resultMatrix.m[3][0] = scaleMatrix.m[0][3] * rotateMatrix.m[0][0] + scaleMatrix.m[1][3] * rotateMatrix.m[0][1] + scaleMatrix.m[2][3] * rotateMatrix.m[0][2] + scaleMatrix.m[3][3] * rotateMatrix.m[0][3];
	resultMatrix.m[3][1] = scaleMatrix.m[0][3] * rotateMatrix.m[1][0] + scaleMatrix.m[1][3] * rotateMatrix.m[1][1] + scaleMatrix.m[2][3] * rotateMatrix.m[1][2] + scaleMatrix.m[3][3] * rotateMatrix.m[1][3];
	resultMatrix.m[3][2] = scaleMatrix.m[0][3] * rotateMatrix.m[2][0] + scaleMatrix.m[1][3] * rotateMatrix.m[2][1] + scaleMatrix.m[2][3] * rotateMatrix.m[2][2] + scaleMatrix.m[3][3] * rotateMatrix.m[2][3];
	resultMatrix.m[3][3] = scaleMatrix.m[0][3] * rotateMatrix.m[3][0] + scaleMatrix.m[1][3] * rotateMatrix.m[3][1] + scaleMatrix.m[2][3] * rotateMatrix.m[3][2] + scaleMatrix.m[3][3] * rotateMatrix.m[3][3];

	// アフィン変換(拡縮、回転)
	// 1行目
	resultMatrix.m[0][0] = resultMatrix.m[0][0] * translateMatrix.m[0][0] + resultMatrix.m[1][0] * translateMatrix.m[0][1] + resultMatrix.m[2][0] * translateMatrix.m[0][2] + resultMatrix.m[3][0] * translateMatrix.m[0][3];
	resultMatrix.m[0][1] = resultMatrix.m[0][0] * translateMatrix.m[1][0] + resultMatrix.m[1][0] * translateMatrix.m[1][1] + resultMatrix.m[2][0] * translateMatrix.m[1][2] + resultMatrix.m[3][0] * translateMatrix.m[1][3];
	resultMatrix.m[0][2] = resultMatrix.m[0][0] * translateMatrix.m[2][0] + resultMatrix.m[1][0] * translateMatrix.m[2][1] + resultMatrix.m[2][0] * translateMatrix.m[2][2] + resultMatrix.m[3][0] * translateMatrix.m[2][3];
	resultMatrix.m[0][3] = resultMatrix.m[0][0] * translateMatrix.m[3][0] + resultMatrix.m[1][0] * translateMatrix.m[3][1] + resultMatrix.m[2][0] * translateMatrix.m[3][2] + resultMatrix.m[3][0] * translateMatrix.m[3][3];
	// 2行目
	resultMatrix.m[1][0] = resultMatrix.m[0][1] * translateMatrix.m[0][0] + resultMatrix.m[1][1] * translateMatrix.m[0][1] + resultMatrix.m[2][1] * translateMatrix.m[0][2] + resultMatrix.m[3][1] * translateMatrix.m[0][3];
	resultMatrix.m[1][1] = resultMatrix.m[0][1] * translateMatrix.m[1][0] + resultMatrix.m[1][1] * translateMatrix.m[1][1] + resultMatrix.m[2][1] * translateMatrix.m[1][2] + resultMatrix.m[3][1] * translateMatrix.m[1][3];
	resultMatrix.m[1][2] = resultMatrix.m[0][1] * translateMatrix.m[2][0] + resultMatrix.m[1][1] * translateMatrix.m[2][1] + resultMatrix.m[2][1] * translateMatrix.m[2][2] + resultMatrix.m[3][1] * translateMatrix.m[2][3];
	resultMatrix.m[1][3] = resultMatrix.m[0][1] * translateMatrix.m[3][0] + resultMatrix.m[1][1] * translateMatrix.m[3][1] + resultMatrix.m[2][1] * translateMatrix.m[3][2] + resultMatrix.m[3][1] * translateMatrix.m[3][3];
	// 3行目
	resultMatrix.m[2][0] = resultMatrix.m[0][2] * translateMatrix.m[0][0] + resultMatrix.m[1][2] * translateMatrix.m[0][1] + resultMatrix.m[2][2] * translateMatrix.m[0][2] + resultMatrix.m[3][2] * translateMatrix.m[0][3];
	resultMatrix.m[2][1] = resultMatrix.m[0][2] * translateMatrix.m[1][0] + resultMatrix.m[1][2] * translateMatrix.m[1][1] + resultMatrix.m[2][2] * translateMatrix.m[1][2] + resultMatrix.m[3][2] * translateMatrix.m[1][3];
	resultMatrix.m[2][2] = resultMatrix.m[0][2] * translateMatrix.m[2][0] + resultMatrix.m[1][2] * translateMatrix.m[2][1] + resultMatrix.m[2][2] * translateMatrix.m[2][2] + resultMatrix.m[3][2] * translateMatrix.m[2][3];
	resultMatrix.m[2][3] = resultMatrix.m[0][2] * translateMatrix.m[3][0] + resultMatrix.m[1][2] * translateMatrix.m[3][1] + resultMatrix.m[2][2] * translateMatrix.m[3][2] + resultMatrix.m[3][2] * translateMatrix.m[3][3];
	// 4行目
	resultMatrix.m[3][0] = resultMatrix.m[0][3] * translateMatrix.m[0][0] + resultMatrix.m[1][3] * translateMatrix.m[0][1] + resultMatrix.m[2][3] * translateMatrix.m[0][2] + resultMatrix.m[3][3] * translateMatrix.m[0][3];
	resultMatrix.m[3][1] = resultMatrix.m[0][3] * translateMatrix.m[1][0] + resultMatrix.m[1][3] * translateMatrix.m[1][1] + resultMatrix.m[2][3] * translateMatrix.m[1][2] + resultMatrix.m[3][3] * translateMatrix.m[1][3];
	resultMatrix.m[3][2] = resultMatrix.m[0][3] * translateMatrix.m[2][0] + resultMatrix.m[1][3] * translateMatrix.m[2][1] + resultMatrix.m[2][3] * translateMatrix.m[2][2] + resultMatrix.m[3][3] * translateMatrix.m[2][3];
	resultMatrix.m[3][3] = resultMatrix.m[0][3] * translateMatrix.m[3][0] + resultMatrix.m[1][3] * translateMatrix.m[3][1] + resultMatrix.m[2][3] * translateMatrix.m[3][2] + resultMatrix.m[3][3] * rotateMatrix.m[3][3];

	// 返却する値
	return resultMatrix;
}

/*==================================================
				Vector3を同時座標系に変換
==================================================*/
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

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
