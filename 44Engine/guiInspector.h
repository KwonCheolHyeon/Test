#pragma once
#include "guiWidget.h"
#include "yaGameObject.h"
#include "guiComponent.h"
#include "guiResource.h"
#include "ImGuizmo.h"

namespace gui
{
	class Inspector : public Widget
	{
	public:
		Inspector();
		~Inspector();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		md::GameObject* GetTargetGameObject() { return mTargetGameObject; }
		void SetTargetGameObject(md::GameObject* target) { mTargetGameObject = target; }
		md::Resource* GetTargetResource() { return mTargetResource; }
		void SetTargetResource(md::Resource* target) { mTargetResource = target; }

		void ClearTarget();
		void InitializeTargetGameObject();
		void InitializeTargetResource();

	private:
		md::GameObject* mTargetGameObject;
		md::Resource* mTargetResource;
		std::vector<gui::Component*> mComponents;
		std::vector<gui::Resource*> mResources;
	};
}
