#pragma once
#include "guiComponent.h"

namespace gui
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

	private:
		md::math::Vector3 mPosisition;
		md::math::Vector3 mRotation;
		md::math::Vector3 mScale;
	};

}
