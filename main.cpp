#include "DxLib.h"
//#include "Vector2.h"
#include "Vector3.h"

//関数プロトタイプ
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

int SetCameraPositionAndTragetAndUpVec(const Vector3& cameraPos, const Vector3& cameraTarget, const Vector3& cameraUp);

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "GC1A_15_ナカザワキョウスケ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1024;

// ウィンドウ縦幅
const int WIN_HEIGHT = 576;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	SetUseZBuffer3D(true);
	SetWriteZBuffer3D(true);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	//クリップ面　近　遠
	SetCameraNearFar(1.0f, 1000.0f);	//カメラの有効範囲を設定
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);	//画面の中心にカメラの中心を合わせる
	Vector3 cameraPosition(0.0f, 0.0f, -30.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);
	SetCameraPositionAndTragetAndUpVec(
		cameraPosition, cameraTarget, cameraUp
	);

	Vector3 A(3, -1, 2);
	Vector3 B(1, 5, -4);
	Vector3 C(-1, 7, 6);

	Vector3 AB = B - A;
	Vector3 AC = C - A;
	Vector3 BC = C - B;
	Vector3 BA = A - B;
	Vector3 CA = A - C;
	Vector3 CB = B - C;

	Vector3 n = AB;
	n.Cross(BC);
	n.Normalize();

	Vector3 position(0, 0, 0);				//位置
	Vector3 velocity(0.0f, 0.0f, 0.5f);		//速度
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; ++i) {
			oldkeys[i] = keys[i];
		}

		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		Vector3 g = (A + B + C) / 3;
		Vector3 v = cameraPosition - g;
		v.Normalize();

		unsigned color = GetColor(255, 255, 255);

		if (v.Dot(n) > 0) {
			color = GetColor(255, 0, 0);
		}

		//描画
		ClearDrawScreen();	//画面を消去
		DrawLine3D(A, B, color);
		DrawLine3D(B, C, color);
		DrawLine3D(C, A, color);


		Vector3 nA = n + (A - g);
		Vector3 nB = n + (B - g);
		Vector3 nC = n + (C - g);

		DrawLine3D(A, nA, 0x00ff00);
		DrawLine3D(B, nB, 0x00ff00);
		DrawLine3D(C, nC, 0x00ff00);

		//DrawSphere3D(position, 80.0f, 32, 0xff0000, 0xffffff, true);

		/*Vector2 a(3, 2);
		Vector2 b(-2, 4);

		Vector2 a1 = a + b;
		Vector2 a2 = a - b;
		Vector2 a3 = 2 * a;
		Vector2 a4 = a - 2 * b;

		DrawFormatString(10, 10, 0xffffff, "a1.x%f a1.y:%f a2.x:%f a2.y%f", a1.x, a1.y, a2.x, a2.y);*/

		// 描画処理
		//DrawCircle(position, 16, GetColor(128, 255, 128));

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}

//オーバーロード関数
////表示位置にベクトルを指定できるようにする
//int DrawCircle(Vector2 vec, int r, unsigned int color) {
//	return DrawCircle(static_cast<int>(vec.x), static_cast<int>(vec.y), r, color);
//}

int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag) {
	VECTOR centerPos = { CenterPos.x, CenterPos.y, CenterPos.z };

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color) {
	VECTOR p1 = { Pos1.x, Pos1.y, Pos1.z };
	VECTOR p2 = { Pos2.x, Pos2.y, Pos2.z };

	return DrawLine3D(p1, p2, Color);
}

//DxLib => int SetCameraPositionAndTragetAndUpVec(VECTOR Position, VECTOR Target, VECTOR Up);
int SetCameraPositionAndTragetAndUpVec(const Vector3& cameraPos, const Vector3& cameraTarget, const Vector3& cameraUp) {
	VECTOR position = { cameraPos.x, cameraPos.y, cameraPos.z };
	VECTOR target = { cameraTarget.x, cameraTarget.y, cameraTarget.z };
	VECTOR up = { cameraUp.x, cameraUp.y, cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}