#include "Ground.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Ground::Ground(GameObject* parent)
	: GameObject(parent, "Ground"), hModel_(-1),fModel_(-1)
{
}

//������
void Ground::Initialize()
{
	
	//���f���f�[�^�̃��[�h
	gModel_ = Model::Load("Assets\\Ground.fbx");
	fModel_ = Model::Load("Assets\\Ball.fbx");
	
	assert(gModel_ >= 0);
	assert(fModel_ >= 0);

	

}

//�X�V
void Ground::Update()
{
	//transform_.rotate_.y += 0.5f;
}

//�`��
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

//�J��
void Ground::Release()
{
}

void Ground::Arrow()
{

}