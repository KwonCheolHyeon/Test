#include "mdCreeperFlashScript.h"
#include "yaInput.h"
#include "yaGameObject.h"
#include "yaBaseRenderer.h"
#include "yaTime.h"

namespace md
{
	CreeperFlashScript::CreeperFlashScript()
		: Script()
		, mIsFlash(0)
		, mElpasedTime(0.0f)
		, mFlashDuration(1.5f)
	{
	}
	CreeperFlashScript::~CreeperFlashScript()
	{
	}
	void CreeperFlashScript::Initalize()
	{
	}
	void CreeperFlashScript::Update()
	{

		mElpasedTime += Time::DeltaTime();

		// 추후에 Attack 상태로 진입했을 때 Flash값 1로 전환해서 반짝이도록 변경해야함
		if (Input::GetKey(eKeyCode::U) && mIsFlash == 0)
		{
			mIsFlash = 1;
			mElpasedTime = 0.0f;
		}

		if (mIsFlash == 1 && mElpasedTime > mFlashDuration)
		{
			mIsFlash = 0;
		}

	}
	void CreeperFlashScript::Render()
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
	void CreeperFlashScript::OnCollisionEnter(Collider3D* collider)
	{
	}
	void CreeperFlashScript::OnCollisionStay(Collider3D* collider)
	{
	}
	void CreeperFlashScript::OnCollisionExit(Collider3D* collider)
	{
	}
	void CreeperFlashScript::Start()
	{
	}
	void CreeperFlashScript::Action()
	{
	}
	void CreeperFlashScript::End()
	{
	}
}
