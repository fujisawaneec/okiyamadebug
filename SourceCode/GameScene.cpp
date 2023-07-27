#include "GameScene.h"
#include"FbxLoader.h"
#include"StuructTransform.h"


void GameScene::Init(DxWindow* dxwindow, DirectXCommon* dxcommon)
{
	
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dxwindow->GetHwnd(), dxcommon);

	input = new Input();
	input->Initialize(dxwindow->GetHInstance(), dxwindow->GetHwnd());

	spritecommon = new SpriteCommon();
	spritecommon->Initialize(dxcommon);

	texturemanager = TextureManager::GetInstance();
	texturemanager->StaticInitialize(dxcommon);
	uint32_t blank = texturemanager->LoadTexture("Resources/white1x1.png");
	light = LightGroup::Create();
	OBJ3D::SetLight(light);
	camera.Initialize({}, {},dxcommon->GetDevice());
	Object3D::SetCamera(camera.getView());
	Draw3DLine::SetCamera(&camera);

	StuructTransform::SetStruct(&camera, spritecommon, texturemanager);

	//テクスチャ読み込み
	skydome_model = ObjModel::LoadFromOBJ("skydome");
	field_model = ObjModel::LoadFromOBJ("ground");
	
	a3d.Init();
	a2d.Init();

	//3Dモデル周り

	
	skydome = OBJ3D::Create(&skydome_wt);
	skydome->SetModel(skydome_model);

	field = OBJ3D::Create(&field_wt);
	field->SetModel(field_model);

	boss.Init();

	player.SetInput(input);
	player.Init();

	boss.SetPlayer(&player.transform);
	player.SetEnemy(&boss.transform);


	//スプライト周り


	//パーティクル周り

	int scenenum = 0;

	float ambientColor[3] = { 1,1,1 };

	float lightDir0[3] = { 0,0,-1 };
	float lightColor0[3] = { 1,0,0 };

	float litX = 0.0f;
	float litY = 0.0f;
	float litZ = 0.0f;

	float pointLightPos[3] = { litX,litY,litZ };
	float pointLightColor[3] = { 1,1,1 };

	float pointLightAtten[3] = { 0.3f,0.1f,0.1f };

	light->SetDirLightActive(0, true);
	light->SetPointLightActive(0, false);


	light->SetPointLightPos(0, XMFLOAT3(pointLightPos));
	light->SetPointLightColor(0, XMFLOAT3(pointLightColor));
	light->SetPointLightAtten(0, XMFLOAT3(pointLightAtten));

	//float a = 0.2f;

	//field->Wt->translation_.y = -5.0f;

}

void GameScene::Update()
{

	input->InputUpdate();
	imGuiManager->Begin();
	static XMVECTOR lightDir = { 0,1,5,0 };

	cameraX = camera.GetWorldPosition().x;
	cameraZ = camera.GetWorldPosition().z;



	XMFLOAT2 inputnum = input->GetRStick(true, true);
	cameraRotateY += (float)inputnum.x * cameraDPI;
	rotateY += (float)inputnum.x * cameraDPI;
	if ((cameraRotateX < 0.27f && (float)inputnum.y / SHRT_MAX>0) || (cameraRotateX > -0.6f && (float)inputnum.y / SHRT_MAX < 0))
	{
		cameraRotateX += (float)inputnum.y *cameraDPI ;
		rotateX -= (float)inputnum.y * cameraDPI;
	}

	light->Update();

	XMFLOAT3 cameraPos = XMFLOAT3(player.GetPos().x - (flontVec.x * cameraDistance),
		player.GetPos().y - (flontVec.y * cameraDistance)+5.0f,
		player.GetPos().z - (flontVec.z * cameraDistance));

	XMFLOAT3 cameraVec = XMFLOAT3((cameraPos.x + (flontVec.x * cameraDistance)), (cameraPos.y + (flontVec.y * cameraDistance)), (cameraPos.z + (flontVec.z * cameraDistance)));

	camera.setPos(XMFLOAT3((sinf(cameraRotateY) * 20 + player.GetPos().x), (sinf(-cameraRotateX) * 20 + player.GetPos().y + 5), (cosf(cameraRotateY) * 20 + player.GetPos().z)));
	camera.setRotate({ rotateX,rotateY,0 });
	camera.Update();
	skydome->Update(camera.getView());
	field->Update(camera.getView());
	player.Update();
	boss.Update();



	imGuiManager->End();
}

void GameScene::Draw(DirectXCommon* dxcommon)
{


	OBJ3D::PreDraw(dxcommon->GetCommandList());

	skydome->Draw();
	field->Draw();
	a2d.SetColor({ 1.0f,0,1.0f,1.0f });
	a3d.Draw(player.GetPos(), XMFLOAT3(boss.transform.translation_.x, boss.transform.translation_.y + boss.transform.scale_.y * 2.0f, boss.transform.translation_.z));
	a2d.Draw(player.GetPos(), boss.transform.translation_);

	player.Draw();
	boss.Draw();
	//ParticleManager::PreDraw(dxcommon->GetCommandList());

	// 3Dオブクジェクトの描画
	//particleMan->Draw();


	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	//ParticleManager::PostDraw();

	spritecommon->PreDraw();

	player.DrawUI();

	//sprite->Draw({ 0,0 });
	//sprite2->DrawClip({ 80.0f,180.0f }, { 200.0f,100.0f }, {});

	spritecommon->PostDraw();

	

	imGuiManager->Draw();
}


