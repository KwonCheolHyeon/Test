#pragma once
#include "yaScript.h"

namespace md
{
	class CreeperFlashScript : public Script
	{
	public:
		CreeperFlashScript();
		~CreeperFlashScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider3D* collider) override;
		virtual void OnCollisionStay(Collider3D* collider) override;
		virtual void OnCollisionExit(Collider3D* collider) override;

		void Start();
		void Action();
		void End();

	private:
		int mIsFlash; // 0으로 초기화 후 1로 설정시 반짝임 작동
		float mFlashDuration;
		float mElpasedTime;
	};
}
