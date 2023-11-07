#include "Input.h"

namespace Input
{
	LPDIRECTINPUT8   pDInput = nullptr;
	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;//�f�o�C�X�I�u�W�F�N�g
	BYTE keyState[256] = { 0 };//���݂̊e�L�[�̏��
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), 
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8, 
			(VOID**)&pDInput, nullptr);
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState, keyState,sizeof(BYTE)* 256);


		pKeyDevice->Acquire();
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
	}

	bool IsKey(int keyCode)
	{
		if (keyState[keyCode] & 0x80)// 1000 0000��10�i���ɂ���(128) 16�i��0x80�ł�����
		{
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (keyState[keyCode] & 0x80 && (~prevKeyState[keyCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//�������͉����ĂāA���͉����ĂȂ����
		if ((~keyState[keyCode] & 0x80) && prevKeyState[keyCode] & 0x80)
		{
			return true;
		}
		return false;
	}



	void Release()
	{
		SAFE_RELEASE(pDInput);
	}
}