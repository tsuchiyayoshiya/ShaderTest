#pragma once

#include <d3d11.h>
#include <assert.h>
//�����J Direct3D�̊e�@�\���g����悤�ɂȂ�
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr;}
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

enum SHADER_TYPE
{
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX,
};

namespace Direct3D

{
	extern ID3D11Device* pDevice_;		//�f�o�C�X
	extern ID3D11DeviceContext* pContext_;		//�f�o�C�X�R���e�L�X�g 
	
	//������
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[����
	HRESULT InitShader();
	HRESULT InitShader2D();
	HRESULT InitShader3D();

	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

};