#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include<vector>
#include "Transform.h"
#include"Direct3D.h"
#include"Transform.h"
#include"Camera.h"
#include"Texture.h"

using std::vector;

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")
//class Texture;//�|�C���^�Ȃ炱���OK(�w�b�_���C���N���[�h���Ȃ��Ă���)
class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		DWORD		polygonCount;		//�}�e���A���̃|���S����
		XMFLOAT4	diffuse;			//�g�U���ˌ��i�f�B�t���[�Y�j�ւ̔��ˋ��x
		XMFLOAT4	ambient;			//�����i�A���r�G���g�j�ւ̔��ˋ��x
		XMFLOAT4	specular;			//���ʔ��ˌ��i�X�y�L�����j�ւ̔��ˋ��x
		float		shininess;			//�n�C���C�g�̋����i�T�C�Y�j
		Texture* pTexture;			//�e�N�X�`��
	}*pMaterial_;

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMMATRIX	matW;
		XMFLOAT4	diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
		//XMFLOAT4    lightDirection;
		XMFLOAT4    eyePos;
		XMFLOAT4    lightPosition;
		BOOL		isTextured;		// �e�N�X�`���\���Ă��邩�ǂ���
		XMFLOAT4    diffuse;
		XMFLOAT4    ambient;
		XMFLOAT4    specular;
		FLOAT       shininess;
	};

	struct VERTEX
	{
		XMVECTOR position;//
		XMVECTOR uv;//�|���S����
		XMVECTOR normal;//�@���x�N�g��
	};

	int vertexCount_;	//���_��
	int polygonCount_;	//�|���S����
	int materialCount_;	//�}�e���A���̌�

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	MATERIAL* pMaterialList_;
	vector<int>index_Count_;

public:
	Fbx();
	HRESULT Load(std::string fileName);
	void    InitVertex(fbxsdk::FbxMesh* mesh);
	void    InitIndex(fbxsdk::FbxMesh* mesh);
	void    IntConstantBuffer();	//�R���X�^���g�o�b�t�@����
	void    InitMaterial(fbxsdk::FbxNode* pNode);
	void    InitTexture(fbxsdk::FbxSurfaceMaterial* pMaterial, const DWORD& i);	//�e�N�X�`������
	void    Draw(Transform& transform);
	void    Release();
};
