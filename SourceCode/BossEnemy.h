#pragma once
#include"StuructTransform.h"
#include"EnemyNormalBullet.h"
#include"Draw3DLine.h"
#include"Player.h"

enum struct AtkPattern
{
	NONE,
	SIMPLESHOT,
	CHARGE,
	LASER,
	MISSILE
};

enum struct MovePattern
{
	NONE,
	BACK,
	FANSHAPE,
	FLY
};

class BossEnemy : public StuructTransform
{
public:

	

	void SetPlayer(Player* pl)
	{
		player = pl;
	}

	

	void Init();

	void Update();

	void Damege(float dmg);

	void Draw();

	void DrawUI();

	void Bulletremove();
private:

	void AtkTable();

	void MoveTable();

	void BackMove();

	void FanShapeMove();

	void FlyMove();

	void SimpleShot();

	void ChargeAtk();

	void LaserShot();

	void MissileShot();

	void ImGuiSet();

	
	const std::list<std::unique_ptr<EnemyNormalBullet>>& GetBullets() { return Normalbullets_; };



private:
	Player* player;
	//�U���p�^�[��
	AtkPattern BossAtk = AtkPattern::NONE;

	//HP
	std::unique_ptr<Sprite2D> sprite_HPbar;

	WorldTransform HpBar;

	uint32_t HpBarHandle;
	const float MaxHP = 100.0f;
	float HP = 0.0f;

	//�s���p�^�[��
	MovePattern BossMove = MovePattern::NONE;

	const int LongMoveTime = 60 * 6;

	const int MidMoveTime = 60 * 3;

	int MoveTimer = 0;

	float Angle=0;

	Draw3DLine LeserPoint;

	//�e�֘A
	std::list<std::unique_ptr<EnemyNormalBullet>> Normalbullets_;

	//�Ə�����
	XMFLOAT3 TargetPos = { 0,0,0 };

	const int TargetTime = 60 * 2;

	int TargetTimer = 0;

	bool AimMode = false;

	//�ʏ�ˌ�

	const int BurstRate = 5;
	const int BurstNum = 3;
	int BurstTime = BurstNum * BurstRate;

	//�F�m�͈�
	float Lange = 0;
	float LangeMax = 50;
	float LangeMin = 10;



};

