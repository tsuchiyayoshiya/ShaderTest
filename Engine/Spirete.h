#pragma once
#include <DirectXMath.h>
#include "Direct3D.h"
#include "Texture.h"
#include<vector>
using namespace DirectX;

#define SAFE_DELETE_ARRAY(p) if(p != nullptr){ delete p; p = nullptr;}

class Spirete
{
	
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matW;
	};

	//���_���
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
	};
	UINT64 vertexNum;//���_��
	std::vector<VERTEX> vertices_;//���_���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@�̃A�h���X������

	UINT64 indexNum;//�C���f�b�N�X��
	std::vector<int> index_;//�C���f�b�N�X���

	//�����o�ϐ����������R���X�g���N�^�ŏ�����
	ID3D11Buffer* pIndexBuffer_;//�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;

public:
	Spirete();
	~Spirete();
	//void
	HRESULT Initialize();
	void Draw(XMMATRIX& worldMatrix);
	void Release();

private:
	
	virtual void InitVertexData(); //���_���̏���
	HRESULT CreateVertexBuffer();//���_�o�b�t�@���쐬

	virtual void InitIndexData();//�C���f�b�N�X���̏���
	HRESULT CreateIndexBuffer();//�C���f�b�N�X�o�b�t�@���쐬

	HRESULT CreateConstantBuffer();//�R���X�^���g�o�b�t�@�쐬

	HRESULT LoadTexture();//�e�N�X�`�������[�h


	void PassDataTcCB(DirectX::XMMATRIX& worldMatrix);//�R���X�^���g�o�b�t�@�Ɋe�����n��
	void SetBufferToPipeline();//�e�o�b�t�@���p�C�v���C���ɃZ�b�g
};


