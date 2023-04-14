#include "WorldTronsform.h"



void WorldTransform::CreateConstBuffer(ID3D12Device* device)
{
	HRESULT result;
	D3D12_HEAP_PROPERTIES cbHeapProp{};

	cbHeapProp.Type = D3D12_HEAP_TYPE_UPLOAD;	//GPU�ւ̓]���p

	D3D12_RESOURCE_DESC cbResourceDesc{};
	//���\�[�X�ݒ�
	cbResourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	cbResourceDesc.Width = (sizeof(ConstBufferDataWorldTransformB0) + 0xff) & ~0Xff;	//256�o�C�g�A���C�����g
	cbResourceDesc.Height = 1;
	cbResourceDesc.DepthOrArraySize = 1;
	cbResourceDesc.MipLevels = 1;
	cbResourceDesc.SampleDesc.Count = 1;
	cbResourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	
	//�萔�o�b�t�@�̐���
	result = device->CreateCommittedResource(
		&cbHeapProp,		//�q�[�v�ݒ�
		D3D12_HEAP_FLAG_NONE,
		&cbResourceDesc,	//���\�[�X�ݒ�
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0)
	);
	assert(SUCCEEDED(result));


}

void WorldTransform::Map()
{
	HRESULT result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
	
}

void WorldTransform::UpdateMatrix(XMMATRIX view, XMMATRIX projection,XMFLOAT3 camerapos)
{
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation_.z);
	matRot *= XMMatrixRotationX(rotation_.x);
	matRot *= XMMatrixRotationY(rotation_.y);
	matTrans = XMMatrixTranslation(translation_.x, translation_.y, translation_.z);

	// ���[���h�s��̍���
	matWorld_ = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld_ *= matScale;          // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld_ *= matRot;            // ���[���h�s��ɉ�]�𔽉f
	matWorld_ *= matTrans;          // ���[���h�s��ɕ��s�ړ��𔽉f

	//// �e�s��̎w�肪����ꍇ�́A�|���Z����
	//if (parent_) {
	//	matWorld_ *= parent_->matWorld_;
	//}

	// �萔�o�b�t�@�ɏ�������
	constMap->color = color;
	//constMap->matWorld = matWorld_ * view * projection;
	constMap->viewproj = view * projection;
	constMap->world = matWorld_;
	constMap->cameraPos = camerapos;
	
}

void WorldTransform::UpdateMatrixBill(ViewProjection* camera)
{
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation_.z);
	matRot *= XMMatrixRotationX(rotation_.x);
	matRot *= XMMatrixRotationY(rotation_.y);
	matTrans = XMMatrixTranslation(translation_.x, translation_.y, translation_.z);

	// ���[���h�s��̍���
	matWorld_ = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld_ *= matScale;          // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld_ *= matRot;            // ���[���h�s��ɉ�]�𔽉f
	matWorld_ *= matTrans;          // ���[���h�s��ɕ��s�ړ��𔽉f

	XMVECTOR eyePosition = XMLoadFloat3(&camera->Geteye());

	XMVECTOR targetPosition = XMLoadFloat3(&camera->Gettarget());

	XMVECTOR upVector = XMLoadFloat3(&camera->Getup());

	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);

	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	XMVECTOR cameraAxisX;

	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);

	cameraAxisX = XMVector3Normalize(cameraAxisX);

	XMVECTOR cameraAxisY;

	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);

	XMMATRIX matCameraRot;

	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);

	XMMATRIX matView = XMMatrixTranspose(matCameraRot);

	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);

	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);

	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);

	matView.r[3] = translation;

	matBillboard.r[0] = cameraAxisX;
	matBillboard.r[1] = cameraAxisY;
	matBillboard.r[2] = cameraAxisZ;
	matBillboard.r[3] = XMVectorSet(0, 0, 0, 1);

	//// �e�s��̎w�肪����ꍇ�́A�|���Z����
	//if (parent_) {
	//	matWorld_ *= parent_->matWorld_;
	//}

	// �萔�o�b�t�@�ɏ�������
	constMap->viewproj = matView * camera->GetMatProjection();
	constMap->world = matBillboard;
	constBuffB0->Unmap(0, nullptr);
	

}

void WorldTransform::UpdateSpriteMatrix(XMMATRIX projection)
{
	XMMATRIX matScale, matRot, matTrans;

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale_.x, scale_.y, 1.0f);
	matRot = XMMatrixIdentity();
	matRot *= XMMatrixRotationZ(rotation_.z);
	matRot *= XMMatrixRotationX(0.0f);
	matRot *= XMMatrixRotationY(0.0f);
	matTrans = XMMatrixTranslation(translation_.x, translation_.y, 0.0f);

	// ���[���h�s��̍���
	matWorld_ = XMMatrixIdentity(); // �ό`�����Z�b�g
	matWorld_ *= matScale;          // ���[���h�s��ɃX�P�[�����O�𔽉f
	matWorld_ *= matRot;            // ���[���h�s��ɉ�]�𔽉f
	matWorld_ *= matTrans;          // ���[���h�s��ɕ��s�ړ��𔽉f

	//// �e�s��̎w�肪����ꍇ�́A�|���Z����
	//if (parent_) {
	//    matWorld_ *= parent_->matWorld_;
	//}

	// �萔�o�b�t�@�ɏ�������
	constMap->color = color;
	constMap->world = matWorld_ * projection;

}