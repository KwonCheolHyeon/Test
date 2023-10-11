#pragma once
#include "yaGameObject.h"


namespace md
{
	class Collider3D;
	class RigidBody;
	class StageColliderObject : public GameObject
	{
	public:
		StageColliderObject();
		virtual ~StageColliderObject();

		virtual void Initalize() override;
		virtual void Update()override;
		virtual void FixedUpdate()override;
		virtual void PrevRender()override;
		virtual void Render()override;

	private:
		Collider3D* mColl3D;
		RigidBody* mRigid;
	};
}
