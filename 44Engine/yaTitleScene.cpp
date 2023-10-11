#include "yaTitleScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaTexture.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaSpriteRenderer.h"
#include "yaGridScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaLight.h"
#include "yaPaintShader.h"
#include "yaParticleSystem.h"
#include "yaMeshData.h"
#include "yaRigidBody.h"
#include "yaCollider3D.h"
#include "mdDetourManager.h"

#include "mdUIBase.h"


namespace md
{
	TitleScene::TitleScene()
		: Scene(eSceneType::TitleScene)
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initalize()
	{
	

		// Main Camera Game Object
		GameObject* cameraObj = object::Instantiate<GameObject>(eLayerType::Camera);
		cameraObj->SetName(L"MainCamera");
		cameraObj->SetPosition(Vector3(0.0f, 10.0f, -50.0f));
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
		
		Scene::Initalize();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::N))
		{
			SceneManager::LoadScene(eSceneType::PlayScene);
		}

		Scene::Update();
	}
	void TitleScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
}


//{
//	GameObject* player = object::Instantiate<GameObject>(eLayerType::Player);
//	player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
//	player->GetComponent<Transform>()->SetScale(Vector3(500.0f, 500.0f, 500.0f));
//	player->SetName(L"SkyBox");
//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
//	mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
//	mr->SetMaterial(Resources::Find<Material>(L"SkyBoxMaterial"), 0);
//}


//{
//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
//	directionalLight->SetName(L"PointLight");

//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

//	Light* lightComp = directionalLight->AddComponent<Light>();
//	lightComp->SetType(eLightType::Point);
//	lightComp->SetRadius(20.0f);
//	lightComp->SetDiffuse(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
//	lightComp->SetSpecular(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
//	lightComp->SetAmbient(Vector4(0.15f, 0.15f, 0.15f, 1.0f));
//}

//{
//	GameObject* directionalLight = object::Instantiate<GameObject>(eLayerType::Player);
//	directionalLight->SetName(L"PointLight");

//	directionalLight->GetComponent<Transform>()->SetPosition(Vector3(-15.0f, 0.0f, 0.0f));

//	Light* lightComp = directionalLight->AddComponent<Light>();
//	lightComp->SetType(eLightType::Point);
//	lightComp->SetRadius(30.0f);
//	lightComp->SetDiffuse(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
//	lightComp->SetSpecular(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
//	lightComp->SetAmbient(Vector4(0.15f, 0.15f, 0.15f, 1.0f));
//}

//fbx
//{
	//MeshData* meshData = MeshData::LoadFromFbx(L"fbx\\Monster.fbx");
	//std::shared_ptr<Mesh> mesh = Resources::Load<Mesh>(L"Monster.mesh", L"Monster.mesh");
	// 

	//MeshData* newMeshData = new MeshData();
	//newMeshData->Load(L"..\\Resources\\MeshData\\House.meshdata");
	//GameObject* player = newMeshData->Instantiate();


	//newMeshData->

	//GameObject* player = meshData->Instantiate();
	// 
	// 
	//player->SetName(L"Monster");
	//	}
//Resources::Insert<Texture>(L"PositionTarget", pos);
//Resources::Insert<Texture>(L"NormalTarget", normal);
//Resources::Insert<Texture>(L"AlbedoTarget", albedo);
//Resources::Insert<Texture>(L"SpecularTarget", specular);
//Resources::Insert<Texture>(L"DiffuseLightTarget", diffuse);
//Resources::Insert<Texture>(L"SpecualrLightTarget", specular);
