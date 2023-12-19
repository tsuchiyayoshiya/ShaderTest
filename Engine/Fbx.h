#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>

using std::vector;



#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")
//class Texture;//�|�C���^�Ȃ炱���OK(�w�b�_���C���N���[�h���Ȃ��Ă���)

class Texture;

enum RENDER_STATE
{
	RENDER_DIRLIGHT,
	RENDER_PNTLIGHT,
};

class Fbx
{
	//�}�e���A��
	struct MATERIAL
	{
		DWORD		polygonCount;		//�}�e���A���̃|���S����
		XMFLOAT4	diffuse;			//�g�U���ˌ��i�f�B�t���[�Y�j�ւ̔��ˋ��x
		XMFLOAT4	ambient;			//�����i�A���r�G���g�j�ւ̔��ˋ��x
		XMFLOAT4	specular;			//���ʔ��ˌ��i�X�y�L�����j�ւ̔��ˋ��x
		Texture* pTexture;	
				//�e�N�X�`��
	}*pMaterial_;

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;//wvp
		XMMATRIX	matW;//wvp
		XMMATRIX	matNormal;//���[���h�ϊ������̂��
		XMFLOAT4	diffuseColor;
		XMFLOAT4	ambientColor;
		XMFLOAT4	specularColor;
		FLOAT		shininess;
		BOOL		isTextured;
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
	vector<int>indexCount_;

	void    InitVertex(fbxsdk::FbxMesh* mesh);
	void    InitIndex(fbxsdk::FbxMesh* mesh);
	void    IntConstantBuffer();	//�R���X�^���g�o�b�t�@����
	void    InitMaterial(fbxsdk::FbxNode* pNode);
	RENDER_STATE state_;
	Texture* pToonTex_;

public:
	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};
