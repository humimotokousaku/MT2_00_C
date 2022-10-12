#include <Novice.h>
#include <stdio.h>

const char kWindowTitle[] = "LC1B_26_フミモトコウサク";
// 構造体
struct Matrix2x2 {
	float m[2][2];
};

struct Vector2 {
	float x;
	float y;
};

// 関数
// 行列の加法
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result{};
	result.m[0][0] = matrix1.m[0][0] + matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] + matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] + matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] + matrix2.m[1][1];
	return result;
}
// 行列の減法
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result{};
	result.m[0][0] = matrix1.m[0][0] - matrix2.m[0][0];
	result.m[0][1] = matrix1.m[0][1] - matrix2.m[0][1];
	result.m[1][0] = matrix1.m[1][0] - matrix2.m[1][0];
	result.m[1][1] = matrix1.m[1][1] - matrix2.m[1][1];
	return result;
}
// 行列の積
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 result{};
	result.m[0][0] = matrix1.m[0][0] * matrix2.m[0][0] + (matrix1.m[0][1] * matrix2.m[1][0]);
	result.m[0][1] = matrix1.m[0][0] * matrix2.m[0][1] + (matrix1.m[0][1] * matrix2.m[1][1]);
	result.m[1][0] = matrix1.m[1][0] * matrix2.m[0][0] + (matrix1.m[1][1] * matrix2.m[1][0]);
	result.m[1][1] = matrix1.m[1][0] * matrix2.m[0][1] + (matrix1.m[1][1] * matrix2.m[1][1]);
	return result;
}
// ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 result{};
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1];
	return result;
}
// 計算結果をScreenPrintfで描画
static const int kRowHeight = 20;
static const int kColumnWidth = 44;
// 行列
void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			if (column == 0) {
				Novice::ScreenPrintf(
					x + column * kColumnWidth, y + row * kRowHeight,
					"%.2f",
					matrix.m[row][column]);
			}
			if (column == 1) {
				Novice::ScreenPrintf(
					x + column * kColumnWidth * 1.25, y + row * kRowHeight,
					"%.2f",
					matrix.m[row][column]);
			}

		}
	}
}
// ベクトル
void VectorScreenPrintf(int x, int y, Vector2 vector) {
	Novice::ScreenPrintf(x, y, "%.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth * 1.5f, y, "%.2f", vector.y);
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// 宣言
	// 行列
	Matrix2x2 matrix1{};
	matrix1.m[0][0] = 1.0f;
	matrix1.m[0][1] = 2.0f;
	matrix1.m[1][0] = 3.0f;
	matrix1.m[1][1] = 4.0f;
	Matrix2x2 matrix2{};
	matrix2.m[0][0] = 5.0f;
	matrix2.m[0][1] = 6.0f;
	matrix2.m[1][0] = 7.0f;
	matrix2.m[1][1] = 8.0f;
	// ベクトル
	Vector2 v = { 10,20 };

	Matrix2x2 resultAdd;
	Matrix2x2 resultSubtract;
	Matrix2x2 resultMultiply;
	Vector2 resultVector;
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
		resultAdd = Add(matrix1, matrix2);
		resultSubtract = Subtract(matrix1, matrix2);
		resultMultiply = Multiply(matrix1, matrix2);
		resultVector = Multiply(v, matrix1);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(10, kRowHeight * 0, resultAdd);
		MatrixScreenPrintf(10, kRowHeight * 2 + 10, resultSubtract);
		MatrixScreenPrintf(10, kRowHeight * 4 + 20, resultMultiply);
		VectorScreenPrintf(0, kRowHeight * 6 + 30, resultVector);
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
