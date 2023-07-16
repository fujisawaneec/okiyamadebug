#pragma once
#include<ObjModel.h>
#include<OBJ3D.h>
#include<WorldTronsform.h>
#include<Camera.h>
#include<Input.h>



class Player
{
public:
	void SetStruct(ObjModel* _model,OBJ3D* _obj,Camera* _camera,Input* _input);

	void Init();

	void Update();

	void Draw();

	XMFLOAT3 GetPos()
	{
		return player->Wt->translation_;
	}

private:
	Input* input;

	
	float move_speed;
	XMFLOAT3 moveVec;
	

	Camera* camera;

	OBJ3D* player = nullptr;
	ObjModel* player_model = nullptr;

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
