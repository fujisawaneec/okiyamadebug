#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include"WorldTronsform.h"
#include<vector>
#include<string>
#include"Pipeline.h"
#include"ViewProjection.h"
#include<forward_list>
#include"TextureManager.h"

using namespace DirectX;

using namespace Microsoft::WRL;

using namespace std;

class ParticleManager
{
public:
	struct VertexPos
	{
		XMFLOAT3 pos; // xyz���W
		float scale;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX matBillboard;
	};

	struct Particle
	{
		using XMFLOAT3 = DirectX::XMFLOAT3;

		XMFLOAT3 position = {};

		XMFLOAT3 velocity = {};

		XMFLOAT3 accel = {};

		int frame = 0;

		int num_frame = 0;

		float scale = 1.0f;
		float s_scale = 1.0f;
		float e_scale = 0.0f;
	};

	std::forward_list<Particle> particle;

	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	
	static void PostDraw();

	static ParticleManager* Create(uint32_t Handle);

private:
	static ID3D12Device* device;

	static ID3D12GraphicsCommandList* commandList;

	static PipelineSet ParPipeline;

	TextureData* tex;

	WorldTransform wt;

};
