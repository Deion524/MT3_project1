#pragma once
#include "Vector3.h"

// 前方宣言
class Camera;

class Grid{
public:
	Grid();
	~Grid();
public:
	// メンバ関数
	void GridDraw(Camera*camera);

private:
	// メンバ変数
	Vector3 gridStart_;
	Vector3 gridEnd_;
	const float kGridHalfWidth_ = 500.0f;													// グリッドの半分の幅
	const int kSubdivision_ = 10;															// 分割数
	const float kGridEvery_ = (kGridHalfWidth_ * 2.0f) / static_cast<float>(kSubdivision_);	// グリッド線一つ分の長さ
	int color_ = 0xFFFFFFFF;

};

