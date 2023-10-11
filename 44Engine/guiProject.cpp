#include "guiProject.h"

#include "yaTexture.h"
#include "yaMaterial.h"
#include "yaMesh.h"
#include "yaShader.h"

#include "guiInspector.h"
#include "guiResource.h"
#include "yaResources.h"
#include "guiEditor.h"
#include "guiWidgetManager.h"

extern gui::Editor editor;

namespace gui
{

	Project::Project()
		: mTreeWidget(nullptr)
	{
		SetName("Project");
		float width = 1600.f;
		float height = 900.f;

		Vector2 size(width, height);

		SetSize(ImVec2((float)size.x / 2 + size.x / 5, size.y / 4));

		mTreeWidget = new TreeWidget();
		mTreeWidget->SetName("Resources");
		AddWidget(mTreeWidget);

		mTreeWidget->SetEvent(this
			, std::bind(&Project::toInspector, this, std::placeholders::_1));

		mTreeWidget->SetDummyRoot(true);
		ResetContent();
	}

	Project::~Project()
	{
		delete mTreeWidget;
		mTreeWidget = nullptr;
	}

	void Project::FixedUpdate()
	{
		Widget::FixedUpdate();

		//리소스가 바뀐다면 리소스목록 초기화
	}

	void Project::Update()
	{
		Widget::Update();
	}

	void Project::LateUpdate()
	{

	}

	void Project::ResetContent()
	{
		//mTreeWidget->Close();
		mTreeWidget->Clear();

		TreeWidget::Node* pRootNode = mTreeWidget->AddNode(nullptr, "Resources", 0, true);

		//enum class eResourceType
		//{
		//	Mesh,
		//	Texture,
		//	Material,
		//	Sound,
		//	Prefab,
		//	MeshData,
		//	GraphicsShader,
		//	ComputeShader,
		//	End,
		//};
		AddResources<md::Mesh>(pRootNode, "Mesh");
		AddResources<md::graphics::Texture>(pRootNode, "Texture");
		AddResources<md::graphics::Material>(pRootNode, "Materials");
		AddResources<md::Shader>(pRootNode, "Shaders");
	}

	void Project::toInspector(void* data)
	{
		md::Resource* resource = static_cast<md::Resource*>(data);

		Inspector* inspector = WidgetManager::GetWidget<Inspector>("Inspector");
		inspector->SetTargetResource(resource);
		inspector->InitializeTargetResource();
	}

}
