#include "guiEditorObjectManager.h"
#include "yaMeshRenderer.h"
#include "yaRenderer.h"
#include "yaResources.h"
#include "yaInput.h"



namespace gui
{

	std::vector<EditorObject*> EditorObjectManager::mEditorObjects{};
	std::vector<DebugObject*> EditorObjectManager::mDebugObjects{};

	EditorObjectManager::EditorObjectManager()
	{
	}
	EditorObjectManager::~EditorObjectManager()
	{
	}
	void EditorObjectManager::Initialize()
	{
		// 충돌체의 종류 갯수만큼만 있으면 된다.
		mDebugObjects.resize((UINT)eColliderType::End);

		// 공용 Material
		std::shared_ptr<md::Material> material = md::Resources::Find<Material>(L"DebugMaterial");

		// 2D Debug Object
		// Rect
		std::shared_ptr<md::Mesh> rectMesh = md::Resources::Find<md::Mesh>(L"DebugRectMesh");
		mDebugObjects[(UINT)eColliderType::Plane] = new DebugObject();
		md::MeshRenderer* renderer = mDebugObjects[(UINT)eColliderType::Plane]->AddComponent<md::MeshRenderer>();
		renderer->SetMaterial(material, 0);
		renderer->SetMesh(rectMesh);

		// Triangle
		std::shared_ptr<md::Mesh> triangleMesh = md::Resources::Find<md::Mesh>(L"DebugTriangleMesh");
		mDebugObjects[(UINT)eColliderType::Triangle] = new DebugObject();
		renderer = mDebugObjects[(UINT)eColliderType::Triangle]->AddComponent<md::MeshRenderer>();
		renderer->SetMaterial(material, 0);
		renderer->SetMesh(triangleMesh);


		// Circle
		std::shared_ptr<md::Mesh> circleMesh = md::Resources::Find<md::Mesh>(L"CircleMesh");
		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		renderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<md::MeshRenderer>();
		renderer->SetMaterial(material, 0);
		renderer->SetMesh(circleMesh);

		// 3D Debug Object
		// Box
		std::shared_ptr<md::Mesh> boxMesh = md::Resources::Find<md::Mesh>(L"DebugCubeMesh");
		mDebugObjects[(UINT)eColliderType::Box] = new DebugObject();
		renderer = mDebugObjects[(UINT)eColliderType::Box]->AddComponent<md::MeshRenderer>();
		renderer->SetMaterial(material, 0);
		renderer->SetMesh(boxMesh);

		// Sphere
		std::shared_ptr<md::Mesh> sphereMesh = md::Resources::Find<md::Mesh>(L"SphereMesh");
		mDebugObjects[(UINT)eColliderType::Sphere] = new DebugObject();
		renderer = mDebugObjects[(UINT)eColliderType::Sphere]->AddComponent<md::MeshRenderer>();
		renderer->SetMaterial(material, 0);
		renderer->SetMesh(sphereMesh);
	}
	void EditorObjectManager::Release()
	{
		for (auto obj : mEditorObjects)
		{
			delete obj;
			obj = nullptr;
		}

		for (auto obj : mDebugObjects)
		{
			delete obj;
			obj = nullptr;
		}
	}
	void EditorObjectManager::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}
	void EditorObjectManager::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}
	void EditorObjectManager::FixedUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->FixedUpdate();
		}
	}
	void EditorObjectManager::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (DebugMesh& mesh : md::renderer::debugMeshes)
		{
			DebugRender(mesh);
		}
		md::renderer::debugMeshes.clear();
	}
	void EditorObjectManager::DebugRender(md::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		if (!debugObj)
			return;

		md::Transform* tr = debugObj->GetTransform();
		tr->SetPosition(mesh.position);
		tr->SetRotation(mesh.rotatation);

		switch (mesh.type)
		{
		case eColliderType::Plane:
			tr->SetScale(mesh.scale);
			break;
		case eColliderType::Triangle:
			tr->SetScale(mesh.scale);
			break;
		case eColliderType::Circle:
			tr->SetScale(Vector3(mesh.radius));
			break;
		//case eColliderType::Line:
		//	tr->SetScale(Vector3(mesh.scale.x, 1.f, 0.f));
		//	break;
		case eColliderType::Capsule:
		case eColliderType::Box:
			tr->SetScale(mesh.scale);
			break;
		case eColliderType::Sphere:
			tr->SetScale(Vector3(mesh.scale.x));
			break;
		case eColliderType::End:
			break;
		default:
			break;
		}
		md::BaseRenderer* renderer = debugObj->GetComponent<md::BaseRenderer>();
		md::Camera* camera = md::renderer::mainCamera;

		std::shared_ptr<Material> material = renderer->GetMaterial(0);
		//material->SetData(eGPUParam::Int, mesh.->state);
		tr->FixedUpdate();

		md::Camera::SetGpuViewMatrix(md::renderer::mainCamera->GetViewMatrix());
		md::Camera::SetGpuProjectionMatrix(md::renderer::mainCamera->GetProjectionMatrix());

		debugObj->Render();
	}
}
