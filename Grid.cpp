#include "Grid.h"
#include "Camera.h"
#include "Novice.h"

/*==================================================
				コンストラクタとデストラクタ
==================================================*/
// コンストラクタ
Grid::Grid() {
	gridStart_ = { 0.0f,0.0f,1.0f };
	gridEnd_ = { 0.0f,0.0f,1.0f };
}

// デストラクタ
Grid::~Grid() {

}


/*==================================================
					更新処理
==================================================*/
// グリッド線
void Grid::GridDraw(Camera* camera) {
	// 縦線
	for (int i = 0; i < kSubdivision_; ++i) {
		gridStart_ = { -kGridHalfWidth_ + kGridEvery_ * i,0.0f,5.5f };
		gridEnd_ = { -kGridHalfWidth_ + kGridEvery_ * i,0.0f,0.5f };
		Vector3 ndcVertex = camera->Transform(gridStart_, camera->wvpMatrix_);
		Vector3 screenStartVertex = camera->Transform(ndcVertex, camera->viewportMatrix_);
		ndcVertex = camera->Transform(gridEnd_, camera->wvpMatrix_);
		Vector3 screenEndVertex = camera->Transform(ndcVertex, camera->viewportMatrix_);

		if (i == kSubdivision_ / 2) {
			color_ = 0x000000FF;
		} else {
			color_ = 0xFFFFFFFF;
		}

		Novice::DrawLine(
			static_cast<int>(screenStartVertex.x), static_cast<int>(screenStartVertex.y),
			static_cast<int>(screenEndVertex.x), static_cast<int>(screenEndVertex.y),
			color_
		);

	}

	// 横線
	for (int i = 0; i < kSubdivision_; ++i) {
		gridStart_ = { -kGridHalfWidth_ ,0.0f,0.5f + 0.5f * i };
		gridEnd_ = { kGridHalfWidth_ ,0.0f,0.5f + 0.5f * i };
		Vector3 ndcVertex = camera->Transform(gridStart_, camera->wvpMatrix_);
		Vector3 screenStartVertex = camera->Transform(ndcVertex, camera->viewportMatrix_);
		ndcVertex = camera->Transform(gridEnd_, camera->wvpMatrix_);
		Vector3 screenEndVertex = camera->Transform(ndcVertex, camera->viewportMatrix_);

		if (i == kSubdivision_ / 2) {
			color_ = 0x000000FF;
		} else {
			color_ = 0xFFFFFFFF;
		}

		Novice::DrawLine(
			static_cast<int>(screenStartVertex.x), static_cast<int>(screenStartVertex.y),
			static_cast<int>(screenEndVertex.x), static_cast<int>(screenEndVertex.y),
			color_
		);

	}
}