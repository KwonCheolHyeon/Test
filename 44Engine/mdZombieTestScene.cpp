#include "mdZombieTestScene.h"
#include "yaRenderer.h"
#include "yaMeshRenderer.h"

#include "yaInput.h"
#include "yaObject.h"
#include "yaResources.h"
#include "yaMeshData.h"
#include "yaCollisionManager.h"

#include "yaTransform.h"
#include "yaAnimator.h"
#include "yaLight.h"
#include "yaParticleSystem.h"
#include "yaRigidBody.h"
#include "yaCollider3D.h"

#include "yaCamera.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "mdZombie.h"

#include "yaPlayerScript.h"

#include "mdZombieScript.h"
#include "mdZombieAniScript.h"

#include "yaCameraScript.h"


namespace md
{
	ZombieTestScene::ZombieTestScene()
		: Scene(eSceneType::ZombieMonsterTestScene)
	{
	}
	ZombieTestScene::~ZombieTestScene()
	{
	}
	void ZombieTestScene::Initalize()
	{		// Main Camera Game Object
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

		// 충돌처리를 할 LayerType 설정
		CollisionManager::SetCollisionGroup(eLayerType::Monster, eLayerType::Stage);
		CollisionManager::SetCollisionGroup(eLayerType::Monster, eLayerType::Wall);
		CollisionManager::SetCollisionGroup(eLayerType::Monster, eLayerType::Player);

		CollisionManager::SetCollisionGroup(eLayerType::Player, eLayerType::Stage);
		CollisionManager::SetCollisionGroup(eLayerType::Player, eLayerType::Wall);
		// Raycast 충돌처리를 할 LayerType 설정
		CollisionManager::EnableRaycast((UINT)eLayerType::Camera, (UINT)eLayerType::Stage, true);

		{
			Zombie* monster = object::Instantiate<Zombie>(eLayerType::Monster);
			monster->SetName(L"Zombie");
			ZombieScript* zombieScr = monster->AddComponent<ZombieScript>();
			monster->AddComponent<ZombieAniScript>();
			monster->SetScale(math::Vector3(5.0f, 5.0f, 5.0f)); 
			monster->SetPosition(math::Vector3(-20.f, -10.f, -20.f));
		}

		// Monster
		Zombie* monster = object::Instantiate<Zombie>(eLayerType::Monster);
		monster->SetName(L"Zombie");
		ZombieScript* zombieScr = monster->AddComponent<ZombieScript>();
		monster->AddComponent<ZombieAniScript>();
		monster->SetScale(math::Vector3(5.0f, 5.0f, 5.0f));
		monster->SetPosition(math::Vector3(20.f, -10.f, 20.f));


		// Player
		Player* player = nullptr;
		player = object::Instantiate<Player>(eLayerType::Player);
		player->SetName(L"Player");
		player->AddComponent<PlayerScript>();
		player->SetScale(Vector3(5.0f, 5.0f, 5.0f));
			
		


		{
			tPhysicsInfo info = {};
			info.eActorType = eActorType::Static;
			info.eGeomType = eGeometryType::Box;
			info.size = math::Vector3(50.0f, 1.0f, 50.0f);

			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Stage);
			obj->SetScale(Vector3(50.0f, 1.0f, 50.0f));
			obj->SetName(L"Floor");

			RigidBody* rigid = obj->AddComponent<RigidBody>();
			rigid->SetPhysical(info);
			obj->SetPosition(math::Vector3(0.0f, -20.0f, 0.0f));
			obj->AddComponent<Collider3D>();

			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DefferdMaterial"), 0);
		}

		Scene::Initalize();
	}
	void ZombieTestScene::Update()
	{
		Scene::Update();
	}
	void ZombieTestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void ZombieTestScene::Render()
	{
		Scene::Render();
	}
	void ZombieTestScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void ZombieTestScene::OnExit()
	{
		Scene::OnExit();
	}
}
