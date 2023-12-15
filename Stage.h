#pragma once
#include "Engine/GameObject.h"
#include "Engine/Quad.h"


struct CBUFF_STAGESCENE
{
    XMFLOAT4	lightPosition;
    XMFLOAT4	eyePosition;

};

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    ID3D11Buffer* pCBStageScene_;
    //Quad* q;
    void InitConstantBuffer();
    XMFLOAT4	lightSourcePosition_;
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void	SetLightPos(XMFLOAT4& _pos) { lightSourcePosition_ = _pos; }
    XMFLOAT4 GetLightPos() { return(lightSourcePosition_); }
};