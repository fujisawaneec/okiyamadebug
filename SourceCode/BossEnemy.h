#pragma once
#include"StuructTransform.h"
#include"EnemyNormalBullet.h"
#include"Draw3DLine.h"
#include"Player.h"

class BossEnemy : public StuructTransform
{
public:

	enum AtkPattern
	{
		NONE,
		SIMPLESHOT,
		CHARGE,
		LASER,
		MISSILE
	};
	enum MovePattern
	{
		BACK,
		FANSHAPE,
		FLY
	};

	void SetPlayer(Player* pl)
	{
		player = pl;
	}

	

	void Init();

	void Update();

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



	
	const std::list<std::unique_ptr<EnemyNormalBullet>>& GetBullets() { return Normalbullets_; };



private:
	Player* player;
	//攻撃パターン
	AtkPattern BossAtk;
	//行動パターン
	MovePattern BossMove;

	Draw3DLine LeserPoint;

	//弾関連
	std::list<std::unique_ptr<EnemyNormalBullet>> Normalbullets_;

	XMFLOAT3 TargetPos = { 0,0,0 };

	const int TargetTime = 60 * 2;

	int TargetTimer = 0;

	bool AimMode = false;

	const int BurstRate = 5;
	const int BurstNum = 3;
	int BurstTime = BurstNum * BurstRate;

	//認知範囲
	float Lange = 0;
	float LangeMax = 50;
	float LangeMin = 10;

};

