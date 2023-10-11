#pragma once
#include "yaScript.h"

namespace md
{
	class DamageScript : public Script
	{


	public:
		DamageScript();
		virtual ~DamageScript();

		virtual void Initalize();
		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(Collider3D* collider) ;
		virtual void OnCollisionStay(Collider3D* collider) ;
		virtual void OnCollisionExit(Collider3D* collider) ;

		virtual void OnTriggerEnter(Collider3D* collider) {};
		virtual void OnTriggerStay(Collider3D* collider) {};
		virtual void OnTriggerExit(Collider3D* collider) {};

		virtual void Start() {};
		virtual void Action() {};
		virtual void Complete() {};
		virtual void End() {};

		void HitFlash();

	private:
		int mIsFlash; // 0으로 초기화 후 1로 설정시 반짝임 작동
		float mFlashDuration;
		float mElpasedTime;


	};
}
