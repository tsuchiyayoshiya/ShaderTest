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
	hModel_ = Model::Load("Assets\\Arrow.fbx");
	fModel_ = Model::Load("Assets\\Ball.fbx");
	
	assert(hModel_ >= 0);
}

//�X�V
void Ground::Update()
{
	//transform_.rotate_.y += 0.5f;
}

//�`��
void Ground::Draw()
{
	
	
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
	
	Model::SetTransform(gModel_, transform_);
	Model::Draw(gModel_);

	Model::SetTransform(fModel_, transform_);
	Model::Draw(fModel_);
}

//�J��
void Ground::Release()
{
}

void Ground::Arrow()
{

}