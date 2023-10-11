#pragma once
#include "yaScript.h"


namespace md
{
	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void Render() override;

		virtual void OnCollisionEnter(Collider3D* collider) override;
		virtual void OnCollisionStay(Collider3D* collider) override;
		virtual void OnCollisionExit(Collider3D* collider) override;

		virtual void Start() override;
		virtual void Action() override;
		virtual void End() override;

	private:
		float mMoveSpeed;
	};
}
