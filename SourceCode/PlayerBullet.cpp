#include "PlayerBullet.h"

std::unique_ptr<ObjModel> PlayerBullet::Premodel;

PlayerBullet::PlayerBullet()
{
	ModelInit(Premodel.get());
	Velocity_ = { 0,0,0 };
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::SetModel(ObjModel* model)
{
	Premodel.reset(model);
}

void PlayerBullet::Initlize(const XMFLOAT3& position, const XMFLOAT3& rota, const XMFLOAT3& velocity)
{
	transform.translation_ = position;
	transform.rotation_ = rota;
	transform.scale_ = { 0.5f,0.5f,0.5f };
	
	Velocity_ = velocity;
}

void PlayerBullet::Update()
{
	transform.translation_ = transform.translation_ + Velocity_;

	St->Update(camera->getView());

	//�f�X�^�C�}�[���Ђ���0�ȉ��ɂȂ�����t���O�𗧂Ă�
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}
}

void PlayerBullet::Draw()
{
	//bullet.Draw();
	St->Draw();
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

XMFLOAT3 PlayerBullet::GetWorldPosition()
{
	return transform.translation_;
}

XMFLOAT3 PlayerBullet::GetScale()
{
	return transform.scale_;
}
