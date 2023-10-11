#include "guiHierarchy.h"
#include "yaApplication.h"
#include "yaScene.h"
#include "yaLayer.h"
#include "yaSceneManager.h"
#include "guiInspector.h"
#include "guiEditor.h"
#include "yaRenderer.h"
#include "guiInspector.h"
#include "yaGameObject.h"

#include "guiWidgetManager.h"

extern md::Application application;
extern gui::Editor editor;

namespace gui
{
	Hierarchy::Hierarchy()
		: mTreeWidget(nullptr)
	{
		SetName("Hierarchy");
		SetSize(ImVec2(1600 / 2, 900 / 2));

		mTreeWidget = new TreeWidget();
		mTreeWidget->SetName("Scenes");
		AddWidget(mTreeWidget);

		mTreeWidget->SetEvent(this
			, std::bind(&Hierarchy::InitializeInspector, this, std::placeholders::_1));

		mTreeWidget->SetDummyRoot(true);

		// Engine_SOURCE의 GameObject를 가져와서 mTreeWidget에 넣어준다.
		InitializeScene();
	}

	Hierarchy::~Hierarchy()
	{
		delete mTreeWidget;
		mTreeWidget = nullptr;
	}

	void Hierarchy::FixedUpdate()
	{
	}

	void Hierarchy::Update()
	{
	}

	void Hierarchy::LateUpdate()
	{
	}

	void Hierarchy::InitializeInspector(void* data)
	{
		md::renderer::inspectorGameObject = static_cast<md::GameObject*>(data);
		
		Inspector* inspector = WidgetManager::GetWidget<Inspector>("Inspector");
		inspector->SetTargetGameObject(md::renderer::inspectorGameObject);
		inspector->InitializeTargetGameObject();

	}

	void Hierarchy::InitializeScene()
	{
		mTreeWidget->Clear();

		md::Scene* scene = md::SceneManager::GetActiveScene();
		std::string sceneName = WStringToString(scene->GetName());

		TreeWidget::Node* root = mTreeWidget->AddNode(nullptr, sceneName, 0, true);

		for (size_t i = 0; i < (UINT)md::enums::eLayerType::End; i++)
		{
			md::Layer& layer = scene->GetLayer((md::enums::eLayerType)i);
			const std::vector<md::GameObject*>& gameObjs = layer.GetGameObjects();

			for (md::GameObject* obj : gameObjs)
			{
				AddGameObject(root, obj);
			}
		}
	}

	void Hierarchy::AddGameObject(TreeWidget::Node* parent, md::GameObject* gameObject)
	{
		std::string name = WStringToString(gameObject->GetName());
		
		TreeWidget::Node* node = mTreeWidget->AddNode(parent, name, gameObject);
	}

}
