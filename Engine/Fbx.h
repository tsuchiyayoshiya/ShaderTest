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
//class Texture;//ポインタならこれでOK(ヘッダをインクルードしなくていい)
class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		DWORD		polygonCount;		//マテリアルのポリゴン数
		XMFLOAT4	diffuse;			//拡散反射光（ディフューズ）への反射強度
		XMFLOAT4	ambient;			//環境光（アンビエント）への反射強度
		XMFLOAT4	specular;			//鏡面反射光（スペキュラ）への反射強度
		float		shininess;			//ハイライトの強さ（サイズ）
		Texture* pTexture;			//テクスチャ
	}*pMaterial_;

	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matNormal;
		XMMATRIX	matW;
		XMFLOAT4	diffuseColor;		// ディフューズカラー（マテリアルの色）
		//XMFLOAT4    lightDirection;
		XMFLOAT4    eyePos;
		XMFLOAT4    lightPosition;
		BOOL		isTextured;		// テクスチャ貼ってあるかどうか
		XMFLOAT4    diffuse;
		XMFLOAT4    ambient;
		XMFLOAT4    specular;
		FLOAT       shininess;
	};

	struct VERTEX
	{
		XMVECTOR position;//
		XMVECTOR uv;//ポリゴン数
		XMVECTOR normal;//法線ベクトル
	};

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

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
	void    IntConstantBuffer();	//コンスタントバッファ準備
	void    InitMaterial(fbxsdk::FbxNode* pNode);
	void    InitTexture(fbxsdk::FbxSurfaceMaterial* pMaterial, const DWORD& i);	//テクスチャ準備
	void    Draw(Transform& transform);
	void    Release();
};
