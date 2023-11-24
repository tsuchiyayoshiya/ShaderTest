#include "TestScene.h"
#include"Engine/Input.h"
#include "Engine/SceneManager.h"
#include"Stage.h"
#include"Ground.h"
#include"Arrow.h"
#include"Engine/Camera.h"

//コンストラクタ
TestScene::TestScene(GameObject* parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Camera::SetPosition(XMVECTOR{ 3, 5, -5, 0 });
	Camera::SetTarget(XMVECTOR{ 0, 0, 0, 0 });
	//Instantiate<Stage>(this);
	Instantiate<Ground>(this);
	Instantiate<Arrow>(this);
}

//更新
void TestScene::Update()
{
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}