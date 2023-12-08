#pragma once
#include "Engine/GameObject.h"

struct CBUFF_STAGESCENE
{
	XMFLOAT4 lightPosition;
	XMFLOAT4 eyePos;
};


//�����V�[�����Ǘ�����N���X
class Stage : public GameObject
{
	int hModel_;    //���f���ԍ�

	ID3D11Buffer* pCBStageScene_;

	void IntConstantBuffer();
	XMFLOAT4 lightSourcePosition_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

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
