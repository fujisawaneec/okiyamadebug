#pragma once

#define DIRECTINPUT_VERSION	0x0800
#include<dinput.h>
#include<Xinput.h>

#include<wrl.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment (lib, "xinput.lib")

#include <DirectXMath.h>

using namespace DirectX;

class Input
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


public:

	static Input* GetInstance();

	static void Init(HINSTANCE hinstance, HWND hwnd);

	static void InputUpdate();

	static bool GetKey(BYTE _key);

	static bool GetPressKey(BYTE _key);

	static bool GetReleaseKey(BYTE _key);

	//�p�b�h�ɐڑ�����Ă邩
	static bool GetPadConnect();

	//�p�b�h�̃{�^����������Ă��邩
	static bool GetPadButton(UINT button);

	//�p�b�h�̃{�^�������ꂽ�u�Ԃ�
	static bool GetPadButtonUp(UINT button);

	//�p�b�h�̃{�^���������ꂽ�u�Ԃ�
	static bool GetPadButtonDown(UINT button);

	//�p�b�h�̍��X�e�B�b�N
	static XMFLOAT2 GetPadLStick();

	//�p�b�h�̉E�X�e�B�b�N
	static XMFLOAT2 GetPadRStick();

	//���g���K�[���������񂾏u�Ԃ�
	static bool GetLTriggerDown();

	//���g���K�[��������Ă��邩
	static bool GetLTrigger();


	//�E�g���K�[���������񂾏u�Ԃ�
	static bool GetRTriggerDown();


	//�E�g���K�[��������Ă��邩
	static bool GetRTrigger();

	/// <summary>
	/// ���X�e�B�b�N���͂𓾂�
	/// </summary>
	/// <param name="useWASD">WASD�L�[���X�e�B�b�N�Ɍ����Ăď�������</param>
	/// <param name="useArrow">���L�[���X�e�B�b�N�Ɍ����Ăď�������</param>
	/// <returns>���͗�</returns>
	static XMFLOAT2 GetLStick(bool useWASD, bool useArrow);

	/// <summary>
	/// �E�X�e�B�b�N���͂𓾂�
	/// </summary>
	/// <param name="useWASD">WASD�L�[���X�e�B�b�N�Ɍ����Ăď�������</param>
	/// <param name="useArrow">���L�[���X�e�B�b�N�Ɍ����Ăď�������</param>
	/// <returns>���͗�</returns>
	static XMFLOAT2 GetRStick(bool useWASD, bool useArrow);



private:

	void Initialize(HINSTANCE hinstance, HWND hwnd);

	ComPtr<IDirectInput8>directInput;
	ComPtr<IDirectInputDevice8>keyboard;

	XINPUT_STATE xInputState;
	XINPUT_STATE OldxInputState;

	bool isConnectPad = false;

	BYTE key[256] = {};
	BYTE oldkey[256] = {};

};

const DirectX::XMFLOAT2 operator+= (DirectX::XMFLOAT2& v1, const DirectX::XMFLOAT2& v2);

const DirectX::XMFLOAT2 operator+(const DirectX::XMFLOAT2& v1, const DirectX::XMFLOAT2& v2);

float length2(DirectX::XMFLOAT2& a);
void normalize2(DirectX::XMFLOAT2& a);