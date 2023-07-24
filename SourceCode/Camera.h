#pragma once
#include <d3d12.h>
#include "WorldTronsform.h"
#include "ViewProjection.h"

using namespace DirectX;

class Camera
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="worldTransform">���[���h���W</param>
	/// <param name="Rot">��]�p(���W�A��)</param>
	void Initialize(XMFLOAT3 worldPos,XMFLOAT3 Rot, ID3D12Device* Device);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �s��ƃx�N�g���̌v�Z(�������s��v�Z�̐�)
	/// </summary>
	XMFLOAT3 VectorMat(XMFLOAT3 vector, XMMATRIX mat);

	/// <summary>
	/// �s��ƃx�N�g���̌v�Z(�������s��v�Z�̐�)
	/// </summary>
	XMFLOAT3 VectorMat(XMMATRIX mat, XMFLOAT3 vector);

	ViewProjection* getView();

	XMMATRIX getMatWorld();

	XMFLOAT3 getForwardVec();

	//���[���h���W���擾
	XMFLOAT3 GetWorldPosition();

	void setPos(XMFLOAT3 pos);

	void setTarget(XMFLOAT3 Target);

	void setRotate(XMFLOAT3 rotate);

	void setWorldMat(XMMATRIX woeldMat);

private:

	ViewProjection viewProjection_;

	//���[���h�ϊ��f�[�^(�K���ǂݍ���)
	WorldTransform wt;

	//�r���[�v���W�F�N�V����

	XMFLOAT3 forward = { 0.0f, 0.0f, 1.0f };

};

const XMFLOAT3 operator+= (XMFLOAT3& v1, const XMFLOAT3& v2);

const XMFLOAT3 operator+(const XMFLOAT3& v1, const XMFLOAT3& v2);

float length(XMFLOAT3& a);
void normalize(XMFLOAT3& a);