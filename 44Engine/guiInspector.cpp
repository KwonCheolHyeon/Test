#include "guiInspector.h"


#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "yaRenderer.h"

#include "guiTransform.h"
#include "guiMeshRenderer.h"
#include "guiTexture.h"

namespace gui
{
	using namespace md::enums;
	Inspector::Inspector()
	{
		SetName("Inspector");
		SetSize(ImVec2(300.0f, 100.0f));
		
		mComponents.resize((UINT)eComponentType::End);
		mTargetGameObject = md::renderer::inspectorGameObject;

		mComponents[(UINT)eComponentType::Transform] = new gui::Transform();
		mComponents[(UINT)eComponentType::Transform]->SetName("InspectorTransform");
		mComponents[(UINT)eComponentType::Transform]->SetTarget(mTargetGameObject);
		AddWidget(mComponents[(UINT)eComponentType::Transform]);
		
		mComponents[(UINT)eComponentType::MeshRenderer] = new gui::MeshRenderer();
		mComponents[(UINT)eComponentType::MeshRenderer]->SetName("InspectorMeshRenderer");
		mComponents[(UINT)eComponentType::MeshRenderer]->SetTarget(mTargetGameObject);
		AddWidget(mComponents[(UINT)eComponentType::MeshRenderer]);

		mResources.resize((UINT)eResourceType::End);
		mResources[(UINT)eResourceType::Texture] = new gui::Texture();
		mResources[(UINT)eResourceType::Texture]->SetName("InspectorTexture");
		AddWidget(mResources[(UINT)eResourceType::Texture]);
	}

	Inspector::~Inspector()
	{
		for (gui::Component* comp : mComponents)
		{
			delete comp;
			comp = nullptr;
		}

		for (gui::Resource* res : mResources)
		{
			delete res;
			res = nullptr;
		}
	}

	void Inspector::FixedUpdate()
	{
		//mComponents[(UINT)eComponentType::Transform]->SetTarget(mTargetGameObject);
		//mComponents[(UINT)eComponentType::MeshRenderer]->SetTarget(mTargetGameObject);
	}

	void Inspector::Update()
	{

	}

	void Inspector::LateUpdate()
	{
	}

	void Inspector::Render()
	{
		bool open = (bool)GetState();

		FixedUpdate();

		// ImGui::Begin()이 함수가 false를 반환 시 창이 접혀있음을 뜻함
		if (!ImGui::Begin(GetName().c_str(), &open, mWindow_flags))
			mState = eState::Paused;

		Update();

		for (Widget* child : mChilds)
		{
			child->Render();

			ImGui::Separator();
		}

		LateUpdate();

		ImGui::End();
	}

	void Inspector::ClearTarget()
	{
		for (gui::Component* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			comp->SetState(eState::Paused);
			comp->SetTarget(nullptr);
		}

		for (gui::Resource* res : mResources)
		{
			if (res == nullptr)
				continue;

			res->SetState(eState::Paused);
			res->SetTarget(nullptr);
		}
	}

	void Inspector::InitializeTargetGameObject()
	{
		ClearTarget();

		mComponents[(UINT)eComponentType::Transform]->SetState(eState::Active);
		mComponents[(UINT)eComponentType::Transform]->SetTarget(mTargetGameObject);
		mComponents[(UINT)eComponentType::MeshRenderer]->SetState(eState::Active);
		mComponents[(UINT)eComponentType::MeshRenderer]->SetTarget(mTargetGameObject);
	}

	void Inspector::InitializeTargetResource()
	{
		ClearTarget();

		mResources[(UINT)eResourceType::Texture]->SetState(eState::Active);
		mResources[(UINT)eResourceType::Texture]->SetTarget(mTargetResource);
	}
}
