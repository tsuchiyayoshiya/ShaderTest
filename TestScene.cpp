#include "TestScene.h"
#include"Engine/Input.h"
#include "Engine/SceneManager.h"
#include"Stage.h"
#include"Ground.h"
#include"Arrow.h"
#include"Engine/Camera.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{
	Camera::SetPosition(XMVECTOR{ 3, 5, -5, 0 });
	Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
	//Instantiate<Stage>(this);
	Instantiate<Ground>(this);
	Instantiate<Arrow>(this);
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