#include "guiMeshRenderer.h"
#include "yaMeshRenderer.h"
#include "guiEditor.h"
#include "guiListWidget.h"
#include "yaResources.h"
#include "yaResource.h"
#include "guiInspector.h"
#include "yaSpriteRenderer.h"

#include "guiEditorObjectManager.h"
#include "guiWidgetManager.h"

extern gui::Editor editor;

namespace gui
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{
		SetName("MeshRenderer");
		SetSize(ImVec2(200.0f, 120.0f));
	}

	MeshRenderer::~MeshRenderer()
	{

	}

	void MeshRenderer::FixedUpdate()
	{
		Component::FixedUpdate();

		if (GetTarget())
		{
			md::MeshRenderer* meshRenderer
				= GetTarget()->GetComponent<md::MeshRenderer>();

			if (meshRenderer == nullptr)
				return;

			//ya::SpriteRenderer* spriteRenderer
			//	= GetTarget()->GetComponent<ya::SpriteRenderer>();

			//if (spriteRenderer == nullptr)
			//	return;


			mMaterial = meshRenderer->GetMaterial(0);
			mMesh = meshRenderer->GetMesh();
		}
	}

	void MeshRenderer::Update()
	{
		Component::Update();

		if (mMesh == nullptr
			|| mMaterial == nullptr)
			return;

		std::string meshName = WStringToString(mMesh->GetName());
		std::string materialName = WStringToString(mMaterial->GetName());

		ImGui::Text("Mesh"); 
		ImGui::InputText("##MeshName", (char*)meshName.data()
			, meshName.length(), ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine();
		if (ImGui::Button("##MeshBtn", ImVec2(15.0f, 15.0f)))
		{
			static ListWidget* listUI = WidgetManager::GetWidget<ListWidget>("ListWidget");
			listUI->SetState(eState::Active);
			

			//모든 메쉬의 리소스를 가져와야한다.
			std::vector<std::shared_ptr<md::Mesh>> meshes 
				= md::Resources::Finds<md::Mesh>();

			std::vector<std::wstring> wName;
			for (auto mesh : meshes)
			{
				wName.push_back(mesh->GetName());
			}

			listUI->SetItemList(wName);
			listUI->SetEvent(this, std::bind(&MeshRenderer::SetMesh
				, this, std::placeholders::_1));
		}


		ImGui::Text("Material"); //ImGui::SameLine();
		ImGui::InputText("##Material", (char*)materialName.data()
			, materialName.length() + 20, ImGuiInputTextFlags_ReadOnly);
		
		ImGui::SameLine();
		if (ImGui::Button("##MaterialBtn", ImVec2(15.0f, 15.0f)))
		{
			static ListWidget* listUI = WidgetManager::GetWidget<ListWidget>("ListWidget");
			listUI->SetState(eState::Active);
			//모든 메쉬의 리소스를 가져와야한다.
			std::vector<std::shared_ptr<md::Material>> materials
				= md::Resources::Finds<md::Material>();

			std::vector<std::wstring> wName;
			for (auto material : materials)
			{
				wName.push_back(material->GetName());
			}

			listUI->SetItemList(wName);
			listUI->SetEvent(this, std::bind(&MeshRenderer::SetMaterial
				, this, std::placeholders::_1));
		}
	}

	void MeshRenderer::LateUpdate()
	{
		Component::LateUpdate();
	}

	void MeshRenderer::SetMesh(std::string key)
	{
		std::wstring wKey(key.begin(), key.end());
		std::shared_ptr<md::Mesh> mesh = md::Resources::Find<md::Mesh>(wKey);

		static Inspector* inspector = WidgetManager::GetWidget<Inspector>("Inspector");
		inspector->GetTargetGameObject()->GetComponent<md::MeshRenderer>()->SetMesh(mesh);
	}

	void MeshRenderer::SetMaterial(std::string key)
	{
		std::wstring wKey(key.begin(), key.end());
		std::shared_ptr<md::Material> material = md::Resources::Find<md::Material>(wKey);

		static Inspector* inspector = WidgetManager::GetWidget<Inspector>("Inspector");
		inspector->GetTargetGameObject()->GetComponent<md::MeshRenderer>()->SetMaterial(material, 0);
	}
}
