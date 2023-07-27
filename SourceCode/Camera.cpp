#include "Camera.h"
#include <cmath>

void Camera::Initialize(XMFLOAT3 worldPos, XMFLOAT3 Rot, ID3D12Device* Device)
{
	wt.CreateConstBuffer(Device);
	wt.translation_ = worldPos;
	wt.rotation_ = Rot;
	wt.scale_ = { 1.0f,1.0f,1.0f };
}

void Camera::Update()
{

	wt.UpdateMatrix(&viewProjection_);

	viewProjection_.SetEye(wt.translation_);

	//���[���h�O���x�N�g��
	forward = { 0.0f, 0.0f, 1.0f };

	//���[���J�����̉�]�𔽉f
	forward = VectorMat(forward, wt.matWorld_);

	//���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_.SetTarget(viewProjection_.Geteye() + forward);

	//���[���h����x�N�g��
	DirectX::XMFLOAT3 up(0, 1, 0);

	//���[���J�����̉�]�𔽉f(���[���J�����̏���x�N�g��)
	viewProjection_.SetUp(VectorMat(up, wt.matWorld_));


	viewProjection_.Update();

}

XMFLOAT3 Camera::VectorMat(XMFLOAT3 vector, XMMATRIX mat)
{
	XMFLOAT3 changeVector = { 0,0,0 };

	changeVector.x = vector.x * mat.r[0].m128_f32[0] + vector.y * mat.r[1].m128_f32[0] + vector.z * mat.r[2].m128_f32[0] + 0.0f * mat.r[3].m128_f32[0];
	changeVector.y = vector.x * mat.r[0].m128_f32[1] + vector.y * mat.r[1].m128_f32[1] + vector.z * mat.r[2].m128_f32[1] + 0.0f * mat.r[3].m128_f32[1];
	changeVector.z = vector.x * mat.r[0].m128_f32[2] + vector.y * mat.r[1].m128_f32[2] + vector.z * mat.r[2].m128_f32[2] + 0.0f * mat.r[3].m128_f32[2];

	return changeVector;
}

XMFLOAT3 Camera::VectorMat(XMMATRIX mat, XMFLOAT3 vector)
{
	XMFLOAT3 changeVector = { 0,0,0 };

	changeVector.x = mat.r[0].m128_f32[0] * vector.x + mat.r[0].m128_f32[1] * vector.y + mat.r[0].m128_f32[2] * vector.z + mat.r[0].m128_f32[3] * 0.0f;
	changeVector.y = mat.r[1].m128_f32[0] * vector.x + mat.r[1].m128_f32[1] * vector.y + mat.r[1].m128_f32[2] * vector.z + mat.r[1].m128_f32[3] * 0.0f;
	changeVector.z = mat.r[2].m128_f32[0] * vector.x + mat.r[2].m128_f32[1] * vector.y + mat.r[2].m128_f32[2] * vector.z + mat.r[2].m128_f32[3] * 0.0f;

	return changeVector;
}

ViewProjection* Camera::getView()
{
	return &viewProjection_;
}

XMMATRIX Camera::getMatWorld()
{
	return wt.matWorld_;
}

XMFLOAT3 Camera::getForwardVec()
{
	normalize(forward);

	return forward;
}

XMFLOAT3 Camera::GetWorldPosition()
{
	XMFLOAT3 worldpos;

	//���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldpos.x = wt.matWorld_.r[3].m128_f32[0];
	worldpos.y = wt.matWorld_.r[3].m128_f32[1];
	worldpos.z = wt.matWorld_.r[3].m128_f32[2];

	return worldpos;
}

void Camera::setPos(XMFLOAT3 pos)
{
	wt.translation_ = pos;
	wt.UpdateMatrix(&viewProjection_);
}

void Camera::setTarget(XMFLOAT3 Target)
{
	viewProjection_.SetTarget(Target);
}

void Camera::setRotate(XMFLOAT3 rotate)
{
	wt.rotation_ = rotate;
	wt.UpdateMatrix(&viewProjection_);
}

void Camera::setWorldMat(XMMATRIX woeldMat)
{
	wt.matWorld_ = woeldMat;
}

const XMFLOAT3 operator+= (XMFLOAT3& v1, const XMFLOAT3& v2)
{

	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;

	return v1;
}

const XMFLOAT3 operator+(const XMFLOAT3& v1, const XMFLOAT3& v2)
{
	DirectX::XMFLOAT3 temp(v1);
	return temp += v2;
}

float length(XMFLOAT3& a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}

void normalize(XMFLOAT3& a)
{
	float len = length(a);
	if (len != 0)
	{
		a.x /= len;
		a.y /= len;
		a.z /= len;
		return;
	}

	return;
}