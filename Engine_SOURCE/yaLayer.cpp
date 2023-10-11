﻿#include "yaLayer.h"
#include "yaRenderer.h"
#include "yaTransform.h"

namespace md
{
	// z값 정렬 작성중
	//static bool CompareGameObjectByZAxis(GameObject* a, GameObject* b)
	//{
	//	Transform* aTr = a->GetComponent<Transform>();
	//	Transform* bTr = b->GetComponent<Transform>();

	//	if (aTr->GetPosition().z <= bTr->GetPosition().z)
	//	{
	//		return true;
	//	}

	//	return false;
	//}

	Layer::Layer()
	{
	}

	Layer::~Layer()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
			{
				continue;
			}

			delete obj;
			obj = nullptr;
		}
	}

	void Layer::Initalize()
	{
		
	}

	void Layer::Update()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
			{
				continue;
			}
			if (false == obj->IsNeedToProcess())
			{
				continue;
			}

			obj->Update();
		}
	}

	void Layer::FixedUpdate()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
			{
				continue;
			}
			if (false == obj->IsNeedToProcess())
			{
				continue;
			}

			obj->FixedUpdate();
		}

		// sort z axis
		//std::vector<GameObject*> mGameObjects;
		//std::sort(mGameObjects.begin(), mGameObjects.end(), CompareGameObjectByZAxis);
	}

	void Layer::Render()
	{
		for (GameObject* obj : mGameObjects)
		{
			if (nullptr == obj)
			{
				continue;
			}
			if (false == obj->IsNeedToProcess())
			{
				continue;
			}

			obj->Render();
		}
	}

	void Layer::Destroy()
	{
		std::set<GameObject*> deleteObjects;
		// 삭제할 오브젝트들을 전부 찾아온다.
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->GetState() == GameObject::eState::Dead)
			{
				deleteObjects.insert(gameObj);
			}
		}

		// 지워야할 오브젝트들 게임 오브젝트 모음안에서 삭제
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			std::set<GameObject*>::iterator deleteIter
				= deleteObjects.find(*iter);

			if (deleteIter != deleteObjects.end())
			{
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		// 삭제할 오브젝트들을 실제 램(메모리)에서 삭제
		for (GameObject* gameObj : deleteObjects)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}
		
	std::vector<GameObject*> Layer::GetDontDestroyGameObjects()
	{
		std::vector<GameObject*> donts;
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end()
			; )
		{
			if ( (*iter)->IsDontDestroy() == true )
			{
				donts.push_back((*iter));
				iter = mGameObjects.erase(iter);
			}
			else
			{
				iter++;
			}
		}

		return donts;
	}
	void Layer::SetLayerType(eLayerType _layerType)
	{ 
		mLayerType = _layerType;

		SetName(EnumToWString(mLayerType));
	}
}
