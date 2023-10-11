#include "mdStageColliderObject.h"

#include "yaCollider3D.h"
#include "yaRigidBody.h"

namespace md
{
	StageColliderObject::StageColliderObject()
		: mColl3D(nullptr)
		, mRigid(nullptr)
	{
	}
	StageColliderObject::~StageColliderObject()
	{
	}
	void StageColliderObject::Initalize()
	{
		Collider3D* mColl3D = AddComponent<Collider3D>();
		RigidBody* mRigid = AddComponent<RigidBody>();
	}
	void StageColliderObject::Update()
	{
	}
	void StageColliderObject::FixedUpdate()
	{
	}
	void StageColliderObject::PrevRender()
	{
	}
	void StageColliderObject::Render()
	{
	}
}
