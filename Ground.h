#pragma once
#include "Engine/GameObject.h"


//�����V�[�����Ǘ�����N���X
class Ground : public GameObject
{
	int hModel_;    //���f���ԍ�
	int fModel_;
	int gModel_ = -1;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Ground(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Arrow();
};
