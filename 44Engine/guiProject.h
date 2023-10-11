#pragma once
#include "guiWidget.h"
#include "guiTreeWidget.h"
#include "yaResources.h"
#include "yaResource.h"
namespace gui
{
	class Project : public Widget
	{
	public:
		Project();
		~Project();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		void ResetContent();

	private:
		template <typename T>
		void AddResources(TreeWidget::Node* rootNode, const char* stemNodeName)
		{
			const std::vector<std::shared_ptr<T>> resources
				= md::Resources::Finds<T>();

			TreeWidget::Node* stemNode
				= mTreeWidget->AddNode(rootNode, stemNodeName, 0, true);

			for (std::shared_ptr<T> resource : resources)
			{
				std::string resourceName = WStringToString(resource->GetName());
				mTreeWidget->AddNode(stemNode, resourceName, resource.get());
			}
		}

		void toInspector(void* data);



	private:
		TreeWidget* mTreeWidget;
	};
}
