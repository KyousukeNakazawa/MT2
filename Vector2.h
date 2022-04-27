#pragma once
class Vector2
{
public:
	float x, y; //x,y����

public:
	//�R���X�g���N�^
	Vector2();					//0�x�N�g���Ƃ��Đ���
	Vector2(float x, float y);	//�������w�肵�Đ���

	//�����o�֐�
	float Length() const;		//�m�����i�����j�����߂�
	Vector2& Normalize();		//���K��
	float Dot(const Vector2& v) const;	//���όv�Z
	float Cross(const Vector2& v) const;	//�O�όv�Z

	//�P�����Z�q�I�[�o�[���[�h
	Vector2 operator+() const;
	Vector2 operator-() const;

	//������Z�q�I�[�o�[���[�h
	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};

//�񍀉��Z�q�I�[�o�[���[�h
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);

