#pragma once
#include"Input.h"
#include"PlayerBullet.h"
#include"StuructTransform.h"
#include"ParticleManager.h"


class Player : public StuructTransform
{
public:
	void SetEnemy(WorldTransform* enemy)
	{
		boss = enemy;
	}

	void Init();

	void Reset();

	void Update();

	void Damege(float dmg);

	void Draw();

	void DrawUI();

	bool Death()
	{
		if (HP <= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	XMFLOAT3 GetPos()
	{
		return St->Wt.translation_;
	}
	XMFLOAT3 GetUnderPos()
	{
		XMFLOAT3 UnderPos = GetPos();
		UnderPos.y -= St->Wt.scale_.y;
		return UnderPos;
	}

	const std::list<std::unique_ptr<PlayerBullet>>& GetBullets() { return bullets_; };
private:

	/// <summary>
	/// �U��
	/// </summary>
	void Attack(XMFLOAT3 flont);

	void Move();

	void Jump(XMFLOAT3 front);

	void Dash(XMFLOAT3 front);

	void EN();

	void LockOn();

	bool ScLock(WorldTransform* prewt);

	XMFLOAT2 WorldToMonitor(XMFLOAT3 pos);


	void ImGuiSet();


private:
	WorldTransform* boss;
	
	float move_speed;

	bool BoostMode = false;

	XMFLOAT3 moveVec;

	//HUD����----------
	std::unique_ptr<Sprite2D> sprite_Reticle;
	std::unique_ptr<Sprite2D> sprite_Lock;
	std::unique_ptr<Sprite2D> sprite_HPbar;
	std::unique_ptr<Sprite2D> sprite_CoverHPbar;
	std::unique_ptr<Sprite2D> sprite_ENGauge;
	std::unique_ptr<Sprite2D> sprite_CoverENGaugebar;

	uint32_t reticleHandle;
	uint32_t LockHandle;
	uint32_t HpBarHandle;

	//----------------

	XMFLOAT2 Lock2DPos = { 0,0 };

	//�e�֘A
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

	const float MaxHP = 20.0f;
	float HP = 0.0f;


	int bulletCT = 0;

	const int MAXBulletCT = 5;

	const int firelate = 15;

	int latetime;

	bool Locked = false;

	//�N�C�b�N�_�b�V������

	float dashspeed = 0.0f;

	const float DashSpeadNum = 5.0f;

	XMFLOAT3 DashVec = { 0,0,0 };

	bool DashFlag = false;

	int DashTimer = 0;
	const int DashTime = 20;

	//�W�����vand�󒆎���

	bool OnGround = false;

	float Upspeed = 0.0f;

	XMFLOAT3 JumpVec = { 0,0,0 };

	const float AirUpSpead = 0.5f;

	const float UpSpeadNum = 2.0f;

	bool JumpFlag = false;

	int JumpTimer = 0;
	const int JumpTime = 20;

	//�u�[�X�g�Q�[�W�I�ȉ���-------
	const float ENGaugeSize = 15.0f;

	int ENGauge = 0;

	const int ENMAXGauge = 1000;

	const int DashUseGauge = 200;

	const int JumpUseGauge = 100;

	const int AirUseGauge = 7;

	bool UseEN = false;

	int RegenENCoolTimer = 0;

	const int RegenENCoolTime = 60;

	const int RegenEN = 3;

	const int RecoveryENGauge = 1;

	bool OverHeat = false;

	int OverHeatENCoolTimer = 0;

	const int OverHeatENCoolTime = 250;

	bool InfEN = false;

	//--------

	/// <summary>
	/// �s��ƃx�N�g���̌v�Z(�������s��v�Z�̐�)
	/// </summary>
	XMFLOAT3 VectorMat(XMFLOAT3 vector, XMMATRIX mat);

	/// <summary>
	/// �s��ƃx�N�g���̌v�Z(�������s��v�Z�̐�)
	/// </summary>
	XMFLOAT3 VectorMat(XMMATRIX mat, XMFLOAT3 vector);

};

const DirectX::XMFLOAT3 operator*=(DirectX::XMFLOAT3& v, float s);

const DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& v, float s);

const DirectX::XMFLOAT3 operator*(float s, const DirectX::XMFLOAT3& v);

const DirectX::XMFLOAT3 operator-= (DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2);

const DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& v1, const DirectX::XMFLOAT3& v2);


