#pragma once
#include "guiWidget.h"
#include "ImGuizmo.h"

namespace md
{
	class Camera;
	class GameObject;
};
namespace gui
{

	class Gizmo :
		public Widget
	{
	public:
		Gizmo();
		virtual ~Gizmo();

		void Initialize();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override ;
		virtual void Close() override;


		void ClearTarget();
		void InitializeTargetGameObject();

		md::GameObject* GetTargetGameObject() { return mTargetGameObject; }
		void SetTargetGameObject(md::GameObject* target) { mTargetGameObject = target; }
		ImGuizmo::OPERATION GetGizmoOperation() { return mGizmoOperation; }
		void SetGizmoOperation(md::GameObject* target) { mGizmoOperation = ImGuizmo::TRANSLATE; }

	private:
		ImGuizmo::OPERATION mGizmoOperation;
		bool mbisOrthographic;
		float mOrthographicViewWidth;
		md::Camera* mCamera;
		static md::GameObject* mTargetGameObject;
	};
}
