#include "Model.h"

namespace Model
{
	
	std::vector<ModelData*>modelList;
}

int Model::Load(std::string fileName)
	{
		ModelData* pData;
		pData = new ModelData;
		pData->fileName_ = fileName;
		pData->pFbx_ = nullptr;
		//filename�������Ȃ�ǂ܂Ȃ�
		for (auto& e : modelList)
		{
			if (e->fileName_ == fileName)
			{
				pData->pFbx_ = e->pFbx_;
				break;
			}
		}
		
		if (pData->pFbx_ == nullptr)
		{
			pData->pFbx_ = new Fbx;
			pData->pFbx_->Load(fileName);
		}
		modelList.push_back(pData);
		return(modelList.size() - 1);
		//�ǂ�ō��

	}

	void Model::SetTransform(int hModel, Transform transfome)
	{
		modelList[hModel]->transfome_ = transfome;
		//���f���ԍ���modekList�̃C���f�b�N�X
	}

	void Model::Draw(int hModel)
	{
		//���f���ԍ���modekList�̃C���f�b�N�X
		modelList[hModel]->pFbx_->Draw(modelList[hModel]->transfome_);
	}

	void Model::Release()
	{
		bool isReffered = false;
		for (int i = 0; i < modelList.size(); i++)
		{
			for (int j = i + 1; j < modelList.size(); j++)
			{
				if (modelList[i]->pFbx_ == modelList[j]->pFbx_)
				{
					isReffered = true;
					break;
				}
			}
			if (isReffered == false)
			{
				SAFE_DELETE(modelList[i]->pFbx_);
			}
			SAFE_DELETE(modelList[i]);
		}
		modelList.clear();
	}

