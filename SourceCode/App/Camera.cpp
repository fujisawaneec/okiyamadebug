#include "Camera.h"
#include <cmath>
#include"Input.h"

void Camera::Initialize(ID3D12Device* Device)
{
	wt.CreateConstBuffer(Device);
	wt.translation_ = { 0.0f,0.0f,0.0f };
	wt.rotation_ = { 0.0f,0.0f,0.0f };
	wt.scale_ = { 1.0f,1.0f,1.0f };
}

void Camera::Reset()
{
	wt.translation_ = { 0.0f,0.0f,0.0f };
	wt.rotation_ = { 0.0f,0.0f,0.0f };
	wt.scale_ = { 1.0f,1.0f,1.0f };
	setRotate({ 0,0,0 });
	viewProjection_.Initialize();

	cameraRotateX = 0;
	cameraRotateY = 0;
	rotateX = 0;
	rotateY = 0;

	/*if (targetWT)
	{
		interTarget = targetWT->translation_;
		wt.rotation_.y = targetWT->rotation_.y;
	}*/


	targetWT = nullptr;
}

void Camera::Update()
{

	wt.UpdateMatrix(&viewProjection_);

	viewProjection_.SetEye(wt.translation_);

	//ワールド前方ベクトル
	forward = { 0.0f, 0.0f, 1.0f };

	//レールカメラの回転を反映
	forward = forward*wt.matWorld_;

	//視点から前方に適当な距離進んだ位置が注視点
	viewProjection_.SetTarget(viewProjection_.Geteye() + forward);

	//ワールド上方ベクトル
	Vector3 up(0, 1, 0);

	//レールカメラの回転を反映(レールカメラの上方ベクトル)
	viewProjection_.SetUp(up*wt.matWorld_);

	if (targetWT)
	{
		Vector3 offset = { -20.0f,20.0f,-20.0f };



		Vector2 inputnum = Input::GetRStick(true, true);
		cameraRotateY += (float)inputnum.x * cameraDPI;
		rotateY += (float)inputnum.x * cameraDPI;
		if ((cameraRotateX < 0.27f && (float)inputnum.y / SHRT_MAX>0) || (cameraRotateX > -0.6f && (float)inputnum.y / SHRT_MAX < 0))
		{
			cameraRotateX += (float)inputnum.y * cameraDPI;
			rotateX -= (float)inputnum.y * cameraDPI;
		}

		Vector3 cameraPoint = targetWT->translation_;

		cameraPoint.y += 5.0f;
		

		offset.x = offset.x * sinf(cameraRotateY);
		offset.z = offset.z * cosf(cameraRotateY);
		offset.y = offset.y * sinf(-cameraRotateX);



		setRotate({ rotateX,rotateY,0 });
		viewProjection_.SetEye(cameraPoint + offset);
		
		viewProjection_.SetTarget(cameraPoint + forward);



	}


	viewProjection_.Update();

}

ViewProjection* Camera::getView()
{
	return &viewProjection_;
}

Matrix4 Camera::getMatWorld()
{
	return wt.matWorld_;
}

Vector3 Camera::getForwardVec()
{

	return forward.getnormalize();
}


void Camera::setPos(Vector3 pos)
{
	wt.translation_ = pos;
	wt.UpdateMatrix(&viewProjection_);
}

void Camera::setTarget(Vector3 Target)
{
	viewProjection_.SetTarget(Target);
}

void Camera::setRotate(Vector3 rotate)
{
	wt.rotation_ = rotate;
	wt.UpdateMatrix(&viewProjection_);
}

void Camera::setWorldMat(Matrix4 woeldMat)
{
	wt.matWorld_ = woeldMat;
}


