#include "guiTransform.h"
#include "yaTransform.h"

namespace gui
{
	Transform::Transform()
		: Component(eComponentType::Transform)
	{
		SetName("Transform");
		SetSize(ImVec2(200.0f, 120.0f));
	}

	Transform::~Transform()
	{

	}

	void Transform::FixedUpdate()
	{
		Component::FixedUpdate();

		if (GetTarget() == nullptr)
			return;

		md::Transform* tr = GetTarget()->GetComponent<md::Transform>();

	}

	void Transform::Update()
	{
		Component::Update();

		if (!GetTarget() || !GetTarget()->GetTransform())
		{
			return;
		}

		mPosisition = GetTarget()->GetPhysicalLocalPosition();
		mRotation = GetTarget()->GetRotation();
		mScale = GetTarget()->GetScale();

		ImGui::Text("Position"); ImGui::SameLine();
		ImGui::InputFloat3("##Position", (float*)&mPosisition);

		ImGui::Text("Rotation"); ImGui::SameLine();
		ImGui::InputFloat3("##Rotation", (float*)&mRotation);

		ImGui::Text("Scale"); ImGui::SameLine();
		ImGui::InputFloat3("##Scale", (float*)&mScale);

		md::Transform* tr = GetTarget()->GetComponent<md::Transform>();

		//GetTarget()->SetPosition(mPosisition);
		//GetTarget()->SetRotation(mRotation);
		//GetTarget()->SetScale(mScale);
	}

	void Transform::LateUpdate()
	{
		Component::LateUpdate();

	}
}
