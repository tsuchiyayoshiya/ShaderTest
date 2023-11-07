#include "SceneManager.h"
#include"../TestScene.h"
#include"Model.h"
#include"Input.h"
//�R���X�g���N�^
SceneManager::SceneManager(GameObject* parent)
	: GameObject(parent, "SceneManager")
{

}

SceneManager::~SceneManager()
{
}

//������
void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate< TestScene>(this);
	
}

//�X�V
void SceneManager::Update()
{
	//�V�[����؂�ւ���
	//���݂̃V�[���ƁA�l�N�X�g�V�[�����ʂ�������؂�ւ�
	
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		auto scene = childList_.begin();
		(*scene)->ReleaseSub();
		SAFE_DELETE(*scene);
		childList_.clear();
		//���[�h�����S�f�[�^��S�폜
		Model::Release();
		//��Еt������
		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		
		}
		currentSceneID_ = nextSceneID_;
	}
	//���݂̃V�[���̐ՕЕt��
	//�V�����V�[���̏���
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}
/// <summary>
/// �w�肵���V�[����
/// </summary>
/// <param name="_next"></param>
void SceneManager::ChangeScene(SCENE_ID _next)
{
	nextSceneID_ = _next;
	
}