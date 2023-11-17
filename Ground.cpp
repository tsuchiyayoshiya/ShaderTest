#include "Ground.h"
#include "Engine/Model.h"
//コンストラクタ
Ground::Ground(GameObject* parent)
	: GameObject(parent, "Ground"), hModel_(-1),fModel_(-1)
{
}

//初期化
void Ground::Initialize()
{
	
	//モデルデータのロード
	gModel_ = Model::Load("Assets\\Ground.fbx");
	hModel_ = Model::Load("Assets\\Arrow.fbx");
	fModel_ = Model::Load("Assets\\Ball.fbx");
	
	assert(hModel_ >= 0);
}

//更新
void Ground::Update()
{
	//transform_.rotate_.y += 0.5f;
}

//描画
void Ground::Draw()
{
	
	
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	
	Model::SetTransform(gModel_, transform_);
	Model::Draw(gModel_);

	Model::SetTransform(fModel_, transform_);
	Model::Draw(fModel_);
}

//開放
void Ground::Release()
{
}

void Ground::Arrow()
{

}