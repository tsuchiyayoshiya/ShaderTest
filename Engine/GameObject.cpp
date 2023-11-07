#include "GameObject.h"
#include"SphereCollider.h"
GameObject::GameObject()
{

}

GameObject::GameObject(GameObject* parent, const std::string& name):childList_(0), pParent_(parent), objectName_(name), pCollider_(nullptr)
{
	state_ = { 0, 1, 1, 0 };
	if (parent != nullptr)
		this->transform_.pParent_ = &(parent->transform_);
}

GameObject::~GameObject()
{

}
//�폜���邩�ǂ���
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

//�������폜����
void GameObject::KillMe()
{
	state_.dead = 1;
}

void GameObject::UpdateSub()
{
	Update();
	RoundRodin(GetRootJob());
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����UpdateSub���Ă�
	{
		(*itr)->UpdateSub();
	}
	for (auto it = childList_.begin(); it != childList_.end();)
	{
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GameObject::DrawSub()
{
	Draw();
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����DrawSub���Ă�
	{
		(*itr)->DrawSub();
	}
}

void GameObject::ReleaseSub()
{
	
	for (auto itr = childList_.begin(); itr != childList_.end(); itr++)//���ׂĂ̎q����ReleaseSub���Ă�
	{
		
		(*itr)->ReleaseSub();//*itr�̃����[�X���Ă�
		SAFE_DELETE(*itr);//*itr������
	}
	Release();
}

void GameObject::SetPosition(XMFLOAT3 position_)
{
	transform_.position_ = position_;

}

GameObject* GameObject::FindChildObject(std::string _objName)
{
	if (_objName == this->objectName_)
	{
		return(this);//������_objName�̃I�u�W�F�N�g�������玩���̃|�C���^��Ԃ�
	}
	else
	{
		for (auto e:childList_)
		{
			GameObject* obj = e->FindChildObject(_objName);
			if (obj != nullptr)
				return obj;
		}
	}
	return nullptr;
}
/// <summary>
/// �ċN�Ăяo����RootJob��T���Ă��̃A�h���X��Ԃ��֐�
/// </summary>
/// <returns>�߂�l��RootJob�̃A�h���X(GameObject* �^)</returns>
GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
		return this;

	return pParent_->GetRootJob();

}

GameObject* GameObject::FindObject(std::string _objName)
{
	return GetRootJob()->FindChildObject(_objName);
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	if (pTarget == this ||pTarget->pCollider_ == nullptr)
		return;//�������g�A���̓^�[�Q�b�g�ɃR���C�_�[���A�^�b�`����Ă��Ȃ�

	//�����ƃ^�[�Q�b�g�̋��� <= R1+R2�Ȃ�
	/*XMVECTOR v{transform_.position_.x - pTarget->transform_.position_.x,
	           transform_.position_.y - pTarget->transform_.position_.y,
	           transform_.position_.z - pTarget->transform_.position_.z ,0};
	XMVECTOR dist = XMVector3Dot(v, v);*/
	float dist = (transform_.position_.x - pTarget->transform_.position_.x) * (transform_.position_.x - pTarget->transform_.position_.x)
		+ (transform_.position_.y - pTarget->transform_.position_.y) * (transform_.position_.y - pTarget->transform_.position_.y)
		+ (transform_.position_.z - pTarget->transform_.position_.z) * (transform_.position_.z - pTarget->transform_.position_.z);
	float rDist = (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius()) + (this->pCollider_->GetRadius() + pTarget->pCollider_->GetRadius());
	//���������ƃ^�[�Q�b�g���Ԃ����Ă�����
	if (dist <= rDist)
	{
		//onCollosion(pTarget)���Ăяo��
		OnCollision(pTarget);
	}
	
	
	
}

void GameObject::RoundRodin(GameObject* pTarget)
{
	if (pCollider_ == nullptr)
		return;
	if (pTarget->pCollider_ != nullptr)//�����ƃ^�[�Q�b�g
		Collision(pTarget);
	//�����̎q���S���ƃ^�[�Q�b�g
	for (auto itr : pTarget->childList_)
		RoundRodin(itr);
}

string GameObject::GetObjectName()
{
	return objectName_;
}

