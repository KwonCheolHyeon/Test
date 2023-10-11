#include "mdNavTestScene.h"
#include "yaCamera.h"
#include "yaObject.h"
#include "yaCameraScript.h"
#include "yaMeshData.h"
#include "yaResources.h"
#include "mdDetourManager.h"
#include "yaCollisionManager.h"
#include "yaRigidBody.h"

#include "yaPlayer.h"

namespace md
{
	NavTestScene::NavTestScene()
		: Scene(eSceneType::NavTestScene)
	{

	}

	NavTestScene::~NavTestScene()
	{
	}

	void NavTestScene::Initalize()
	{

		// 충돌처리를 할 LayerType 설정
		CollisionManager::SetCollisionGroup(eLayerType::Player, eLayerType::Stage);

		// Raycast 충돌처리를 할 LayerType 설정
		//CollisionManager::EnableRaycast((UINT)eLayerType::Camera, (UINT)eLayerType::Stage, true);

		//DetourManager::ChangeScene(eSceneType::NavTestScene);

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

		Player* playerObj = object::Instantiate<Player>(eLayerType::Player);

		MeshData* meshData = MeshData::LoadFromFbx(L"Nav\\NavTest.fbx");
		std::shared_ptr<Mesh> mesh = Resources::Load<Mesh>(L"NavTest.mesh", L"NavTest.mesh");
		GameObject* stage = meshData->Instantiate(eLayerType::Stage);
		//stage->SetRotation(Vector3(0.0f,-90.0f,0.0f));

		tPhysicsInfo info = {};
		info.eActorType = eActorType::Static;
		info.eGeomType = eGeometryType::None;

		std::vector<std::vector<physx::PxVec3>> vertex = DetourManager::GetVertexFromBinFile(L"Nav\\NavTest.bin");
		std::vector<std::vector<physx::PxU32>> index = DetourManager::GetIndexFromBinFile(L"Nav\\NavTest.bin");

		RigidBody* rigid = stage->AddComponent<RigidBody>();
		rigid->SetTriangleVertexVec(vertex);
		rigid->SetTriangleIndexVec(index);
		rigid->IsCreateTriangleActors(true);
		rigid->SetPhysical(info);

		stage->AddComponent<Collider3D>();

		//(L"Nav\\NavTest.bin");

		Scene::Initalize();
	}

	void NavTestScene::Update()
	{

		Scene::Update();
	}

	void NavTestScene::FixedUpdate()
	{
		Scene::FixedUpdate();
	}

	void NavTestScene::Render()
	{
		Scene::Render();
	}

	void NavTestScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void NavTestScene::OnExit()
	{
		Scene::OnExit();
	}

}
