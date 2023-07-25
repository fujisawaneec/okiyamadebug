#pragma once
#include <DirectXCommon.h>
#include <DxWindow.h>
#include"ViewProjection.h"
#include <Object3D.h>
#include <Input.h>
#include"ImGuiManager.h"
#include"imgui.h"
#include "TextureManager.h"
#include <SpriteCommon.h>
#include <Model.h>
#include <Sprite2D.h>
#include <LightGroup.h>
#include <ParticleManager.h>
#include"CollisionPrimitive.h"
#include"Collision.h"
#include <OBJ3D.h>
#include <ObjModel.h>
#include <Player.h>
#include <Camera.h>



class GameScene
{

private:
	Input* input = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	SpriteCommon* spritecommon = nullptr;
	TextureManager* texturemanager;


public:

	void Init(DxWindow* dxwindow,DirectXCommon* dxcommon);

	void Update();

	void Draw(DirectXCommon* dxcommon);

	void Finalize()
	{

		delete input;
		imGuiManager->Finalize();
		delete imGuiManager;
		delete spritecommon;
		texturemanager->DeleteInstance();
		delete light;

		delete model1;
		delete objec1;

		delete skydome_model;
		delete skydome;
		delete field_model;
		delete field;
		delete particleMan;

		delete sprite;
		delete sprite2;
	}

private:

	Player player;

	float rotateX = 0;

	float cameraX = 0;
	float cameraZ = 0;
	float rotateY = 0;

	float cameraRotateX = 0;
	float cameraRotateY = 9.45f;

	float cameraDPI = 0.05f;


private:
	Camera camera;
	LightGroup* light = nullptr;
	

	uint32_t tex1;
	uint32_t tex2;
	uint32_t tex3;
	uint32_t tex4;

	Model* model1 = nullptr;
	Object3D* objec1 = nullptr;

	ObjModel* skydome_model = nullptr;
	OBJ3D* skydome = nullptr;

	ObjModel* field_model = nullptr;
	OBJ3D* field = nullptr;


	Sprite2D* sprite = nullptr;
	Sprite2D* sprite2 = nullptr;

	ParticleManager* particleMan = nullptr;

	WorldTransform atm;
	WorldTransform wt3;
	WorldTransform wt4;
	WorldTransform p1;

	WorldTransform skydome_wt;
	WorldTransform field_wt;


	XMFLOAT3 eye;
	XMFLOAT3 flontVec = { 0,0,1.0f };
	float cameraDistance = 20.0f;

};

