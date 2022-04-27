#pragma once
class Vector2
{
public:
	float x, y; //x,y成分

public:
	//コンストラクタ
	Vector2();					//0ベクトルとして生成
	Vector2(float x, float y);	//成分を指定して生成

	//メンバ関数
	float Length() const;		//ノルム（長さ）を求める
	Vector2& Normalize();		//正規化
	float Dot(const Vector2& v) const;	//内積計算
	float Cross(const Vector2& v) const;	//外積計算

	//単項演算子オーバーロード
	Vector2 operator+() const;
	Vector2 operator-() const;

	//代入演算子オーバーロード
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

//二項演算子オーバーロード
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

