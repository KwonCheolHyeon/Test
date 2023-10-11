#include "mdPhysXTestScene.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaPlayerScript.h"
#include "yaCamera.h"
#include "yaCameraScript.h"
#include "yaObject.h"
#include "yaInput.h"
#include "yaPlayer.h"
#include "yaMonster.h"
#include "yaCollisionManager.h"
#include "yaAnimator.h"
#include "yaLight.h"
#include "yaParticleSystem.h"
#include "yaMeshData.h"
#include "yaRigidBody.h"
#include "yaCollider3D.h"


namespace md
{
	PhysXTestScene::PhysXTestScene()
		: Scene(eSceneType::PhysXTestScene)
	{
	}
	PhysXTestScene::~PhysXTestScene()
	{
	}
	void PhysXTestScene::Initalize()
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

		// 충돌처리를 할 LayerType 설정
		CollisionManager::SetCollisionGroup(eLayerType::Player, eLayerType::Stage);
		CollisionManager::SetCollisionGroup(eLayerType::Player, eLayerType::Wall);
		// Raycast 충돌처리를 할 LayerType 설정
		CollisionManager::EnableRaycast((UINT)eLayerType::Camera, (UINT)eLayerType::Stage, true);
		
		{
			// PhysX 초기 설정을 위한 구조체
			tPhysicsInfo info = {};
			info.eActorType = eActorType::Dynamic;
			info.eGeomType = eGeometryType::Capsule;
			info.size = math::Vector3(5.0f, 10.0f, 5.0f);
		
			MeshData* meshData = MeshData::LoadFromFbx(L"fbx\\Zombie.fbx");
		
			GameObject* player = meshData->Instantiate(eLayerType::Player);
			player->SetScale(Vector3(5.0f, 5.0f, 5.0f));
			player->SetName(L"Player");
			// rigidBody를 추가후 SetPhysical을 해줘야 PhysX 적용
			RigidBody* rigid = player->AddComponent<RigidBody>();
			rigid->SetPhysical(info);
			rigid->SetMassForDynamic(100.0f);
			rigid->SetFreezeRotation(FreezeRotationFlag::ROTATION_Y, true);
			rigid->SetFreezeRotation(FreezeRotationFlag::ROTATION_X, true);
			rigid->SetFreezeRotation(FreezeRotationFlag::ROTATION_Z, true);
			// SetPhysical() 이후 오브젝트의 위치를 설정해줘야한다(동기화때문)
			player->SetPhysicalLocalPosition(Vector3(0.0f, 80.0f, 0.0f));
			player->GetTransform()->SetPhysicalRotation(math::Vector3(0.0f, 0.0f, 90.0f));
		
			player->AddComponent<Collider3D>();
			player->AddComponent<PlayerScript>();
		}
		
		{
			tPhysicsInfo info = {};
			info.eActorType = eActorType::Static;
			info.eGeomType = eGeometryType::Box;
			info.size = math::Vector3(50.0f, 1.0f, 50.0f);
		
			//MeshData* meshData = MeshData::LoadFromFbx(L"fbx\\cube.fbx");
			//std::shared_ptr<Mesh> mesh = Resources::Load<Mesh>(L"cube.mesh", L"cube.mesh");
			//GameObject* obj = meshData->Instantiate();
		
			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Stage);
			obj->SetScale(Vector3(50.0f, 1.0f, 50.0f));
			obj->SetName(L"Floor");
		
			RigidBody* rigid = obj->AddComponent<RigidBody>();
			//NavMesh Test Code
			//rigid->SetTriangleIndexVec();
			//rigid->SetTriangleVertexVec();
			//rigid->IsCreateTriangleActors(true);
			rigid->SetPhysical(info);
			obj->SetPosition(Vector3(0.0f, -20.0f, 0.0f));
			obj->AddComponent<Collider3D>();
		
			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DefferdMaterial"), 0);
		}

		{
			tPhysicsInfo info = {};
			info.eActorType = eActorType::Static;
			info.eGeomType = eGeometryType::Box;
			info.size = math::Vector3(5.0f, 5.0f, 5.0f);

			GameObject* obj = object::Instantiate<GameObject>(eLayerType::Wall);
			obj->SetScale(Vector3(5.0f, 5.0f, 5.0f));
			obj->SetName(L"Cube");

			RigidBody* rigid = obj->AddComponent<RigidBody>();
			rigid->SetPhysical(info);
			obj->SetPosition(Vector3(10.0f, -10.f, 3.0f));
			obj->AddComponent<Collider3D>();

			MeshRenderer* mr = obj->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"CubeMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DefferdMaterial"), 0);
		}
		Scene::Initalize();
	}
	void PhysXTestScene::Update()
	{
		Scene::Update();
	}
	void PhysXTestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}
	void PhysXTestScene::Render()
	{
		Scene::Render();
	}
	void PhysXTestScene::OnEnter()
	{
		Scene::OnEnter();
	}
	void PhysXTestScene::OnExit()
	{
		Scene::OnExit();
	}
}
