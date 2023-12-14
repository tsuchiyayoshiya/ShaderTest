#include "Stage.h"
#include "Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_(-1)
{
}


void Stage::IntConstantBuffer()
{
	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CBUFF_STAGESCENE);
	cb.Usage = D3D11_USAGE_DEFAULT;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.CPUAccessFlags = 0;
	// コンスタントバッファの作成
	//HRESULT hr;
	//hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pCBStageScene_);
	//if (FAILED(hr))
	//{
	//	MessageBox(NULL, "コンスタントバッファの作成に失敗しました", "エラー", MB_OK);
	//}
}

//初期化
void Stage::Initialize()
{
	hModel_ = Model::Load("Assets\\Donut.fbx");
	//モデルデータのロード
	//hModel_ = Model::Load("Assets\\BoxDefault.fbx");
	//hModel_ = Model::Load("Assets\\Arrow.fbx");
	assert(hModel_ >= 0);
}

//更新
void Stage::Update()
{

	transform_.rotate_.y += 0.5f;
	CBUFF_STAGESCENE cb;
	Direct3D::pContext_->UpdateSubresource(pCBStageScene_,
		0, NULL, &cb, 0, 0);
	cb.lightPosition = lightSourcePosition_;
	cb.eyePos ;

	Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);
	Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);
}

//描画
void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Stage::Release()
{
}
