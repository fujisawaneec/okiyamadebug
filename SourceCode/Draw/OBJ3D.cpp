#include "OBJ3D.h"
#include"DxWindow.h"
#include<string>
#include <DirectXTex.h>
#include <d3dcompiler.h>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

#pragma comment(lib, "d3dcompiler.lib")

ID3D12Device* OBJ3D::device = nullptr;
ID3D12GraphicsCommandList* OBJ3D::commandList;
PipelineSet OBJ3D::ObjPipeline;
LightGroup* OBJ3D::lightGroup = nullptr;



OBJ3D::OBJ3D()
{

	color = { 1,1,1,1 };

	scale = { 1,1,1 };

	rotation = { 0,0,0 };

	position = { 0.0f,0,0 };

	matWorld = XMMatrixIdentity();
}

void OBJ3D::StaticInitialize(ID3D12Device* device, int window_width, int window_height)
{
	assert(device);

	OBJ3D::device = device;
	ObjModel::SetDevice(device);

	ObjPipeline = Pipeline::CreateModelPipline(device);
}

void OBJ3D::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	commandList = cmdList;

	
}


OBJ3D* OBJ3D::Create()
{
	OBJ3D* obj = new OBJ3D();
	if (obj == nullptr) {
		return nullptr;
	}

	// ������
	if (!obj->Initialize()) {
		delete obj;
		assert(0);
		return nullptr;
	}

	float scale_val = 10;
	obj->Wt.scale_ = { scale_val ,scale_val ,scale_val };

	return obj;
}

bool OBJ3D::Initialize()
{
	Wt.CreateConstBuffer(device);
	
	return true;
}

void OBJ3D::Update(ViewProjection* camera)
{
	

	Wt.color = color;
	
	Wt.UpdateMatrix(camera);
	
}

void OBJ3D::Draw()
{
	commandList->SetPipelineState(ObjPipeline.pipelineState.Get());
	commandList->SetGraphicsRootSignature(ObjPipeline.rootSignature.Get());
	// �v���~�e�B�u�`��̐ݒ�R�}���h
	commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST); // �O�p�`���X�g
	
	if (model == nullptr) return;

	commandList->SetGraphicsRootConstantBufferView(0, Wt.constBuffB0->GetGPUVirtualAddress());
	lightGroup->Draw(commandList, 3);
	model->Draw(commandList, 1);
}

