#pragma once
#include "Vector3.h"
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

struct Sphere {
	Vector3 center;
	float radius;
};

// 球を描画
void SphereDraw(const Sphere& sphere, Camera* camera, const int color) {
	const int kSubdivision = 9;	// 分割数
	const float kLatEvery = static_cast<float>(M_PI) / kSubdivision;	// 緯度分割1つ分の角度(いど)
	const float kLonEvery = (static_cast<float>(M_PI)*2.0f) /kSubdivision;	// 経度分割1つ分の角度(けいど)

	for (int i = 0; i < kSubdivision; ++i) {
		float lat = static_cast<float>(-M_PI) / 2.0f + kLatEvery * i;	//	現在の経度
		for (int j = 0; j < kSubdivision; ++j) {
			float lon = j * kLonEvery;	// 現在の緯度
			// 点を作成
			Vector3 a, b, c;
			a.x = sphere.center.x + cosf(lat) * cosf(lon) * sphere.radius;
			a.y = sphere.center.y + sinf(lat) * sphere.radius;
			a.z = sphere.center.z + cosf(lat) * sinf(lon);

			b.x = sphere.center.x + cosf(lat + kLatEvery) * cosf(lon) * sphere.radius;
			b.y = sphere.center.y + sinf(lat + kLatEvery) * sphere.radius;
			b.z = sphere.center.z + cosf(lat + kLatEvery) * sinf(lon);

			c.x = sphere.center.x + cosf(lat) * cosf(lon + kLonEvery) * sphere.radius;
			c.y = sphere.center.y + sinf(lat) * sphere.radius;
			c.z = sphere.center.z + cosf(lat) * sinf(lon + kLonEvery);

			// スクリーン座標に変換
			Vector3 ndcVertexA = camera->Transform(a, camera->wvpMatrix_);
			Vector3 screenVertexA = camera->Transform(ndcVertexA, camera->viewportMatrix_);

			Vector3 ndcVertexB = camera->Transform(b, camera->wvpMatrix_);
			Vector3 screenVertexB = camera->Transform(ndcVertexB, camera->viewportMatrix_);

			Vector3 ndcVertexC = camera->Transform(c, camera->wvpMatrix_);
			Vector3 screenVertexC = camera->Transform(ndcVertexC, camera->viewportMatrix_);

			// 描画
			//AB
			Novice::DrawLine(
				static_cast<int>(screenVertexA.x), static_cast<int>(screenVertexA.y),
				static_cast<int>(screenVertexB.x), static_cast<int>(screenVertexB.y),
				color
			);
			// BC
			Novice::DrawLine(
				static_cast<int>(screenVertexA.x), static_cast<int>(screenVertexA.y),
				static_cast<int>(screenVertexC.x), static_cast<int>(screenVertexC.y),
				color
			);

		}
	}

}
