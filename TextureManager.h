#pragma once
#include"DirectXCommon.h"
#include<memory>
#include<DirectXTex.h>
#include <DirectXMath.h>
#include<string>

using namespace std;

using namespace Microsoft::WRL;

using namespace DirectX;

struct TextureData
{
	//�e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;

	//�f�X�N�v���^�q�[�v
	ComPtr <ID3D12DescriptorHeap> srvHeap;

	//GPU�f�X�N�v���^�n���h��
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle{};

	//����
	size_t width = 0;
	//�c��
	size_t height = 0;

	//�J���[
	XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	string path;

	uint32_t textureHandle;
};

class TextureManager
{

public:

	void StaticInitialize(DirectXCommon* dxcommon);
	
	uint32_t LoadTexture(const std::string& path);

	static uint32_t Load(const std::string& path);

	static TextureData* GetTextureData(uint32_t handle);

	static TextureManager* GetInstance();

	void DeleteInstance();

private:

	DirectXCommon* dxCommon;

	D3D12_HEAP_PROPERTIES textureHeapProp{};

};

