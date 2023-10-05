#pragma once
class Vector2;

class Vector3
{
public:
	float x;
	float y;
	float z;


public:
	//�[���x�N�g��
	Vector3();
	//�C�Ӄx�N�g��
	Vector3(float x, float y, float z);

	//�֐�

	//����
	float length()const;
	//���K��
	Vector3& normalize();
	//���K�������
	Vector3 getnormalize() const;
	//����
	float dot(const Vector3& v)const;
	//�O��
	Vector3 cross(const Vector3& v)const;

	//�t�x�N
	Vector3 operator-()const;

	//��r�g

	bool operator==(const Vector3& v) const;
	bool operator!=(const Vector3& v) const;

	//���Z�g

	//�����Z
	Vector3& operator+=(const Vector3& v);
	//�����Z
	Vector3& operator-=(const Vector3& v);
	//�|���Z
	Vector3& operator*=(float s);
	//���Z
	Vector3& operator/=(float s);

	//�����Z
	Vector3 operator+(const Vector3& v) const;
	//�����Z
	Vector3 operator-(const Vector3& v) const;
	//�|���Z
	Vector3 operator*(const float s) const;
	//���Z
	Vector3 operator/(const float s) const;

	operator Vector2() const;
};

Vector3 operator*(const float s, const Vector3& v);
