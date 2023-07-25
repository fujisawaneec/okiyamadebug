#pragma once
#include "StuructTransform.h"
using namespace DirectX;
class PlayerBullet:public StuructTransform
{
public:
	PlayerBullet();
	~PlayerBullet();

	static void SetModel(ObjModel* _model);

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�������W</param>
	/// <param name="velocity">���x</param>
	void Initlize(const XMFLOAT3& position, const XMFLOAT3& rota, const XMFLOAT3& velocity);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw();

	bool IsDead()const { return isDead_; }

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();

	XMFLOAT3 GetWorldPosition();
	XMFLOAT3 GetScale();

private:

	static std::unique_ptr<ObjModel> Premodel;

	//���f��
	//StuructTransform bullet;
	

	//�e�N�X�`���n���h��


	//���x
	XMFLOAT3 Velocity_;

	//����<frm>
	static const int32_t kLifeTime = 60 * 5;

	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;

	//�f�X�t���O
	bool isDead_ = false;

};
