#include "Stage.h"
#include "Engine/Model.h"
//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_(-1)
{
}


void Stage::IntConstantBuffer()
{
	CBUFF_STAGESCENE cb;
	cb.lightPosition = lightSourcePosition_;
	//Direct3D::pContext_->UpdateSubresource(pCBStageScene_, 0, NULL, &cb, 1, 1);

	Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pCBStageScene_);
	Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pCBStageScene_);
}

//初期化
void Stage::Initialize()
{
	//モデルデータのロード
	//hModel_ = Model::Load("Assets\\BoxDefault.fbx");
	//hModel_ = Model::Load("Assets\\Arrow.fbx");
	//assert(hModel_ >= 0);
}

//更新
void Stage::Update()
{
	transform_.rotate_.y += 0.5f;
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

void Stage::Arrow()
{

}