#include "Arrow.h"
#include "Engine/Model.h"

//コンストラクタ
Arrow::Arrow(GameObject* parent)
	: GameObject(parent, "Arrow"),hModel_(-1),num(3)
{

}

//初期化
void Arrow::Initialize()
{
	int model[2];
	for(int i = 0;i<num;i++)
	{
	hModel_ = Model::Load("Assets\\Arrow.fbx");
	assert(hModel_ >= model[i]);	  
	}
}

//更新
void Arrow::Update()
{
}

//描画
void Arrow::Draw()
{
	Transform xt,yt;
	 
	xt.scale_ = { 1.5,1,1 };
	xt.rotate_.y = 90;
	xt.position_.y = 0;

	yt.scale_ = { 1.5,1,1 };
	yt.rotate_.z = 90;
	yt.position_.y = 0;

	transform_.position_.x = 1.2f;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	Model::SetTransform(hModel_, xt);
	Model::Draw(hModel_);
	Model::SetTransform(hModel_, yt);
	Model::Draw(hModel_);
}

//開放
void Arrow::Release()
{
}