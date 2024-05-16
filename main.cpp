#include <Novice.h>
#include <imgui.h>
#include "Vector3Math.h"
#include "MatrixMath.h"
#include "MakeMatrix.h"
#include "Draw.h"

const char kWindowTitle[] = "LE2B_17_ナガイ_コハク_MT3_2_0 点と線の距離";

struct Line {
	Vector3 origin; //始点
	Vector3 diff; //終点の差分ベクトル
};

struct Ray {
	Vector3 origin; //始点
	Vector3 diff; //終点の差分ベクトル
};

struct Segment {
	Vector3 origin; //始点
	Vector3 diff; //終点の差分ベクトル
};

//正射影ベクトルの生成
Vector3 Project(const Vector3& v1, const Vector3& v2);

//最近接点の生成
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Segment segment{ {-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f} };

	Vector3 point{ -1.5f,0.6f,0.6f };

	Vector3 project = Project(Vector3Math::Subtract(point, segment.origin), segment.diff);
	Vector3 closestPoint = ClosestPoint(point, segment);

	Sphere pointSphere{ point,0.01f };
	Sphere closestPointSphere{ closestPoint,0.01f };

	//ウィンドウサイズ
	float kWindowWidth = 1280.0f;
	float kWindowHeight = 720.0f;

	Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

	Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

	Draw draw;

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

		draw.Pipeline(cameraTranslate, cameraRotate, kWindowWidth, kWindowHeight);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("Debug");
		ImGui::InputFloat3("Point", &point.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Segment origin", &segment.origin.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Segment diff", &segment.diff.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat3("Project", &project.x, "%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::End();

		draw.DrawGrid();

		draw.DrawLine(segment.origin, Vector3Math::Add(segment.origin, segment.diff), WHITE);

		draw.DrawSphere(pointSphere, RED);

		draw.DrawSphere(closestPointSphere, BLACK);

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

//正射影ベクトルの生成
Vector3 Project(const Vector3& v1, const Vector3& v2) {

	float dot = Vector3Math::Dot(v1, v2);

	float norm = powf(Vector3Math::Length(v2), 2.0f);

	Vector3 result = {
		dot / norm * (v2.x),
		dot / norm * (v2.y),
		dot / norm * (v2.z),
	};

	return result;
}

//最近接点の生成
Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {

	Vector3 project = Project(Vector3Math::Subtract(point, segment.origin), segment.diff);

	Vector3 result;

	result.x = segment.origin.x + project.x;
	result.y = segment.origin.y + project.y;
	result.z = segment.origin.z + project.z;

	return result;
}