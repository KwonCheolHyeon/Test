#pragma once
#include "guiWidget.h"
#include "yaGameObject.h"



namespace gui
{
	class Component : public Widget
	{
	public:
		Component(md::enums::eComponentType type);
		~Component();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		void SetTarget(md::GameObject* target) { mTarget = target; }
		md::GameObject* GetTarget() { return mTarget; }

	private:
		md::enums::eComponentType mType;
		md::GameObject* mTarget;
	};
}
