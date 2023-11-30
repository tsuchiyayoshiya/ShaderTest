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
	fModel_ = Model::Load("Assets\\Ball3.fbx");
	
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

//�J��
void Ground::Release()
{
}

void Ground::Arrow()
{

}