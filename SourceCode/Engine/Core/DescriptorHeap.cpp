#include "DescriptorHeap.h"
#include<cassert>

void DescriptorHeap::Initialize(ID3D12Device* Device)
{
	device = Device;
	HRESULT result = S_FALSE;

	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//�V�F�[�_���猩����悤��
	descHeapDesc.NumDescriptors = static_cast<UINT>(MaxSRV + MaxCBV);
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(descHeap.ReleaseAndGetAddressOf()));//����
	assert(SUCCEEDED(result));

	startCpuHandle = descHeap->GetCPUDescriptorHandleForHeapStart();
	startGpuHandle = descHeap->GetGPUDescriptorHandleForHeapStart();

	incrementSize = static_cast<UINT>(device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));

}

UINT64 DescriptorHeap::CreateSRV(D3D12_SHADER_RESOURCE_VIEW_DESC& desc, ID3D12Resource* resource)
{
	if (SRVCount > MaxSRV)
	{
		assert(0);
	}
	//SRV�q�[�v�̐擪�n���h�����擾
	DescriptorHeapViewHandle handle{};

	//�n���h���̃|�C���^���炵
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<SIZE_T>(SRVCount) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<SIZE_T>(SRVCount) * incrementSize);

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateShaderResourceView(resource, &desc, handle.cpuHandle);
	SRVCount++;

	return handle.gpuHandle.ptr;
}

UINT64 DescriptorHeap::CreateCBV(D3D12_CONSTANT_BUFFER_VIEW_DESC& desc)
{
	if (CBVCount > MaxCBV)
	{
		CBVCount = 0;
	}

	//SRV�q�[�v�̐擪�n���h�����擾
	DescriptorHeapViewHandle handle{};

	//�n���h���̃|�C���^���炵
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<SIZE_T>(MaxSRV + CBVCount) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<SIZE_T>(MaxSRV + CBVCount) * incrementSize);

	// �n���h���̎w���ʒu�ɃV�F�[�_�[���\�[�X�r���[�쐬
	device->CreateConstantBufferView(&desc, handle.cpuHandle);

	CBVCount++;

	return handle.gpuHandle.ptr;
}

DescriptorHeap::DescriptorHeapViewHandle DescriptorHeap::AddSRV()
{
	if (SRVCount > MaxSRV)
	{
		assert(0);
	}
	//SRV�q�[�v�̐擪�n���h�����擾
	DescriptorHeapViewHandle handle{};

	//�n���h���̃|�C���^���炵
	handle.cpuHandle.ptr = startCpuHandle.ptr + (static_cast<SIZE_T>(SRVCount) * incrementSize);
	handle.gpuHandle.ptr = startGpuHandle.ptr + (static_cast<SIZE_T>(SRVCount) * incrementSize);

	SRVCount++;

	return handle;
}


ComPtr<ID3D12DescriptorHeap> DescriptorHeap::GetHeap()
{
	return descHeap;
}