#include "mdAnimationFunctionTestScene.h"
#include "yaObject.h"
#include "yaCameraScript.h"
#include "yaMeshData.h"
#include "yaResources.h"
#include "yaInput.h"
#include "yaBoneAnimator.h"

namespace md
{
	AnimationFunctionTestScene::AnimationFunctionTestScene()
		: Scene(eSceneType::AnimationFunctionTestScene)
	{
	}

	AnimationFunctionTestScene::~AnimationFunctionTestScene()
	{
	}
	void AnimationFunctionTestScene::Initalize()
	{
		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->SetName(L"MainCamera");
		cameraObj->SetPosition(Vector3(0.0f, 10.0f, -50.0f));
		cameraObj->SetLayerType(eLayerType::Camera);
		Camera* cameraComp = cameraObj->AddComponent<Camera>();
		cameraComp->SetCameraType(Camera::eCameraType::NoneUI);
		cameraObj->AddComponent<CameraScript>();
		renderer::mainCamera = cameraComp;

		{
			GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Light);
			directionalLight->SetName(L"directionalLight");

			directionalLight->SetPosition(Vector3(-0.0f, 0.0f, 0.0f));
			directionalLight->SetRotation(Vector3(0.0f, 0.0f, 0.0f));

			Light* lightComp = directionalLight->AddComponent<Light>();
			lightComp->SetType(eLightType::Directional);
			lightComp->SetDiffuse(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetSpecular(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			lightComp->SetAmbient(Vector4(0.15f, 0.15f, 0.15f, 1.0f));
		}

		MeshData* meshData = MeshData::LoadFromFbx(L"fbx\\Zombie.fbx");
		std::shared_ptr<Mesh> mesh = meshData->GetMesh();

		mesh->AddAnimationClip(L"Idle", 0, 79);
		mesh->AddAnimationClip(L"Walk", 81, 120);
		mesh->AddAnimationClip(L"Stun", 122, 170);
		mesh->AddAnimationClip(L"NoveltySleep", 171, 257);
		mesh->AddAnimationClip(L"BasicAttack", 259, 300);
		mesh->AddAnimationClip(L"GetHitFromTheFront", 302, 348);

		m_Player = meshData->Instantiate(eLayerType::Player);

		m_Player->SetScale(Vector3(5.0f, 5.0f, 5.0f));
		m_Player->SetName(L"Player");

		BoneAnimator* playerAnimator = m_Player->GetComponent<BoneAnimator>();
		playerAnimator->ChangeAnimation(4);
		//playerAnimator->SetAnimationLoop(4, true);
		playerAnimator->GetCompleteEventRef(L"Idle") = std::bind(&AnimationFunctionTestScene::ChangeAnimTo4, this);
		playerAnimator->GetCompleteEventRef(L"NoveltySleep") = std::bind(&AnimationFunctionTestScene::ChangeAnimTo1, this);

		Scene::Initalize();
	}

	void AnimationFunctionTestScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::NUM_1))
		{
			if (m_Player)
			{
				m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(1);
			}
		}
		if (Input::GetKeyDown(eKeyCode::NUM_2))
		{
			if (m_Player)
			{
				m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(2);
			}
		}
		if (Input::GetKeyDown(eKeyCode::NUM_3))
		{
			if (m_Player)
			{
				m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(3);
			}
		}
		if (Input::GetKeyDown(eKeyCode::NUM_4))
		{
			if (m_Player)
			{
				m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(4);
			}
		}
		if (Input::GetKeyDown(eKeyCode::NUM_5))
		{
			if (m_Player)
			{
				m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(5);
			}
		}
		if (Input::GetKeyDown(eKeyCode::NUM_6))
		{
			if (m_Player)
			{
				m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(6);
			}
		}

		Scene::Update();
	}

	void AnimationFunctionTestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void AnimationFunctionTestScene::Render()
	{
		Scene::Render();
	}

	void AnimationFunctionTestScene::Destroy()
	{
		Scene::Destroy();
	}
	void AnimationFunctionTestScene::ChangeAnimTo1()
	{
		m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(1);
	}
	void AnimationFunctionTestScene::ChangeAnimTo4()
	{
		m_Player->GetComponent<BoneAnimator>()->ChangeAnimation(4);
	}
}
