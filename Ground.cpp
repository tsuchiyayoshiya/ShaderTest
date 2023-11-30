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
	fModel_ = Model::Load("Assets\\Ball3.fbx");
	
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
	Transform gt ,bt;

	gt.rotate_.y = 0;
	gt.scale_ = { 8,8,8 };
	gt.position_.y = -1;

	bt.scale_ = { 1,1,1 };
	bt.rotate_.y = 0;
	bt.position_.x = 3;
	
	Model::SetTransform(gModel_, gt);
	Model::Draw(gModel_);

	Model::SetTransform(fModel_, bt);
	Model::Draw(fModel_);
}

//開放
void Ground::Release()
{
}

void Ground::Arrow()
{

}