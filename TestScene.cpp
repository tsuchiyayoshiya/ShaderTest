#include "TestScene.h"
#include"Engine/Input.h"
#include "Engine/SceneManager.h"
#include"Stage.h"
#include"Ground.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	//Instantiate<Stage>(this);
	Instantiate<Ground>(this);
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}