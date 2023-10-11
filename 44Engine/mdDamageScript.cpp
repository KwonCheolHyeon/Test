#include "mdDamageScript.h"
#include "yaGameObject.h"
#include "yaBaseRenderer.h"
#include "yaTime.h"
namespace md
{
	DamageScript::DamageScript()
		:Script()
		, mIsFlash(0)
		, mElpasedTime(0.0f)
		, mFlashDuration(1.5f)
	{
	}
	DamageScript::~DamageScript()
	{
	}
	void DamageScript::Initalize()
	{
		
	}
	void DamageScript::Update()
	{
		mElpasedTime += Time::DeltaTime();
	}
	void DamageScript::FixedUpdate()
	{
	}
	void DamageScript::Render()
	{
	}
	void DamageScript::OnCollisionEnter(Collider3D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Player")
		{
			mIsFlash = 1;
			mElpasedTime = 0.0f;
		}
	}
	void DamageScript::OnCollisionStay(Collider3D* collider)
	{
	}
	void DamageScript::OnCollisionExit(Collider3D* collider)
	{
		if (collider->GetOwner()->GetName() == L"Player")
		{
			mIsFlash = 0;
			mElpasedTime = 0.0f;
		}
	}
	void DamageScript::HitFlash()
	{
		BaseRenderer* flashBaseRenderer = GetOwner()->GetComponent<BaseRenderer>();

		if (flashBaseRenderer != nullptr)
		{
			std::shared_ptr<Material> flashMaterial = flashBaseRenderer->GetMaterial(0);
			if (flashMaterial != nullptr)
			{
				flashMaterial->SetData(eGPUParam::Int_0, &mIsFlash);
				flashMaterial->SetData(eGPUParam::Float_0, &mFlashDuration);
				flashMaterial->SetData(eGPUParam::Float_1, &mElpasedTime);
			}
		}
	}
}
