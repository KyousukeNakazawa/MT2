#pragma once
class Vector3
{
public:
	float x, y, z;

public:
	//コンストラクタ
	Vector3();
	Vector3(float x, float y, float z);

	//メンバ関数
	float Length() const;	//長さを求める
	Vector3& Normalize();	//正規化
	float Dot(const Vector3& v) const;		//内積計算
	Vector3 Cross(const Vector3& v) const;	//外積計算

	//単項演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;

	//代入演算子オーバーロード
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

//二項演算子オーバーロード
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);