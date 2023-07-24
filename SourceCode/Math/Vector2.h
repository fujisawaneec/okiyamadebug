#pragma once

class Vector3;

class Vector2
{
public:
	float x;
	float y;

public:
	//��x�N�g������
	Vector2();			
	//x,y�������w�肵�Đ���
	Vector2(float x, float y);	

	//�֐�
	
	//����
	float length()const;				
	//���K��
	Vector2& normalize();		
	//���K�������
	Vector2 getnormalize() const;
	//����
	float dot(const Vector2& v)const;	
	//�O��
	float cross(const Vector2& v)const;	

	//�t�x�N
	Vector2 operator-()const;

	//��r�g

	bool operator==(const Vector2& v) const;
	bool operator!=(const Vector2& v) const;

	//���Z�g
	 
	//�����Z
	Vector2& operator+=(const Vector2& v);
	//�����Z
	Vector2& operator-=(const Vector2& v);
	//�|���Z
	Vector2& operator*=(float s);
	//���Z
	Vector2& operator/=(float s);

	//�����Z
	Vector2 operator+(const Vector2& v) const;
	//�����Z
	Vector2 operator-(const Vector2& v) const;
	//�|���Z
	Vector2 operator*(const float s) const;
	//���Z
	Vector2 operator/(const float s) const;

	operator Vector3() const;

};

Vector2 operator*(const float s, const Vector2& v);
