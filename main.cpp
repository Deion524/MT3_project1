#include <Novice.h>
#include "Camera.h"

const char kWindowTitle[] = "LC1A_09_ジェイムズディアンカイ_MT3_00-00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// インスタンス生成
	Camera* camera = new Camera();

	// 三角形
	Vector3 kLocalVertices[3];
	Vector3 screenVertices[3];
	for (int i = 0; i < 3; ++i) {
		screenVertices[i] = { 0.0f,0.0f,0.0f };
	}

	kLocalVertices[0] = { 200.0f,350.0f,100.0f };
	kLocalVertices[1] = { 300.0f,350.0f,100.0f };
	kLocalVertices[2] = { 250.0f,300.0f,100.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		// カメラ
		camera->Move(keys);
		//camera->GridLine();
		camera->Update();

		// 三角形の頂点の計算
		for (int i = 0; i < 3; ++i) {
			Vector3 ndcVertex = camera->Transform(kLocalVertices[i], camera->wvpMatrix_);
			screenVertices[i] = camera->Transform(ndcVertex, camera->viewportMatrix_);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 三角形の描画
		Novice::DrawTriangle(
			static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
			static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
			static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
			0xFFFFFFFF, kFillModeSolid
		);

		// グリッド線
		camera->GridLineDraw();

		// 行列の中身を描画
		camera->Matrix4x4ScreenPrintf(camera->wvpMatrix_, 16.0f, 16.0f);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// メモリの解放
	delete camera;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
