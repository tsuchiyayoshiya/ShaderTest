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
	fModel_ = Model::Load("Assets\\Ball.fbx");
	
	assert(gModel_ >= 0);
	assert(fModel_ >= 0);

	

}

//更新
void Ground::Update()
{
	//transform_.rotate_.y += 0.5f;
}

//描画
void Ground::Draw()
{
	Transform xt ,zt;

	xt.rotate_.y = 0;
	xt.scale_ = { 8,8,8 };
	xt.position_.y = -1;

	zt.scale_ = { 1,1,1 };
	zt.rotate_.y = 0;
	zt.position_.y = 2;

	
	
	Model::SetTransform(gModel_, xt);
	Model::Draw(gModel_);

	Model::SetTransform(fModel_, zt);
	Model::Draw(fModel_);
}

//開放
void Ground::Release()
{
}

void Ground::Arrow()
{

}