#include "VertexBuffer.h"

void VertexBuffer::Create(ID3D12Device* device, size_t length, size_t singleSize, const void* data)
{
	// �q�[�v�ݒ�
	D3D12_HEAP_PROPERTIES heapProp{};
	//���\�[�X�ݒ�
	D3D12_RESOURCE_DESC resDesc{};

	//���_�f�[�^�S�̂̃T�C�Y = ���_�f�[�^�T�C�Y����̃T�C�Y * ���_�f�[�^�̗v�f��
	UINT sizeVB = static_cast<UINT>(singleSize * length);

	//���_�o�b�t�@�̐ݒ�
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;//GPU�ւ̓]���p
	//���\�[�X�ݒ�
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeVB;
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.SampleDesc.Count = 1;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// ���\�[�X�𐶐�
	HRESULT result = device->CreateCommittedResource(
		&heapProp,
		D3D12_HEAP_FLAG_NONE,
		&resDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(vertBuff.ReleaseAndGetAddressOf()));

	// ���_�o�b�t�@�r���[�̐ݒ�
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = static_cast<UINT>(length * singleSize);
	vbView.StrideInBytes = static_cast<UINT>(singleSize);

	result = vertBuff->Map(0, nullptr, &bufferMappedPtr);

	// �}�b�s���O����
	if (data != nullptr)
	{
		// ���_�f�[�^���}�b�s���O��ɐݒ�
		memcpy(bufferMappedPtr, data, length * singleSize);
	}

}

D3D12_VERTEX_BUFFER_VIEW VertexBuffer::GetView() const
{
	return vbView;
}

ID3D12Resource* VertexBuffer::GetResource()
{
	return vertBuff.Get();
}

void VertexBuffer::Update(void* data)
{
	if (data == nullptr)
	{
		return;
	}

	// ���_�f�[�^���}�b�s���O��ɐݒ�
	memcpy(bufferMappedPtr, data, vbView.SizeInBytes);
}
