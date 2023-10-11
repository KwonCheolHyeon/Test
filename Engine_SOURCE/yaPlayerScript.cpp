#include "yaPlayerScript.h"
#include "yaTransform.h"
#include "yaGameObject.h"
#include "yaInput.h"
#include "yaTime.h"
#include "yaAnimator.h"
#include "yaRigidBody.h"
#include "yaCollisionManager.h"
#include "yaRenderer.h"

#include "yaMeshData.h"
#include "mdDamageScript.h"


namespace md
{
	PlayerScript::PlayerScript()
		: Script()
		, mMoveSpeed(10.0f)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initalize()
	{
		MeshData* meshData = MeshData::LoadFromFbx(L"fbx\\PlayerTestZombie.fbx");
		if (meshData)
		{
			GetOwner()->SettingFromMeshData(meshData);
		}

		// PhysX 초기 설정을 위한 구조체
		tPhysicsInfo info = {};
		info.eActorType = eActorType::Dynamic;
		info.eGeomType = eGeometryType::Capsule;
		info.size = math::Vector3(5.0f, 10.0f, 5.0f);

		RigidBody* rigid = GetOwner()->AddComponent<RigidBody>();
		// rigidBody를 추가후 SetPhysical을 해줘야 PhysX 적용
		rigid->SetPhysical(info);
		rigid->SetMassForDynamic(100.0f);
		rigid->SetFreezeRotation(FreezeRotationFlag::ROTATION_Y, true);
		rigid->SetFreezeRotation(FreezeRotationFlag::ROTATION_X, true);
		rigid->SetFreezeRotation(FreezeRotationFlag::ROTATION_Z, true);
		// SetPhysical() 이후 오브젝트의 위치를 설정해줘야한다(동기화때문)
		GetOwner()->SetPhysicalLocalPosition(Vector3(0.0f, 80.0f, 0.0f));
		GetOwner()->GetTransform()->SetPhysicalRotation(math::Vector3(0.0f, 0.0f, 90.0f));

		GetOwner()->AddComponent<Collider3D>();
		GetOwner()->AddComponent<DamageScript>();
	}

	void PlayerScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		RigidBody* rb = GetOwner()->GetComponent<RigidBody>();

		if (Input::GetKey(eKeyCode::H))
		{
			tr->SetPosition(math::Vector3(0.0f, 0.0f, 0.f));
		}

		if (Input::GetKey(eKeyCode::LBTN))
		{
			//CollisionManager::DrawRaycast(GetOwner()->GetPosition(), math::Vector3(0.0f, -1.0f, 0.0f), 200.0f);

			// Raycast 호출하여 다음 이동 방향을 구함		
			math::Vector3 mouseHitPos = CollisionManager::GetMouseRayHitPos(GetOwner()->GetLayerType(), tr->GetPosition());
			math::Vector3 localPos = tr->GetPhysicalLocalPosition();
			math::Vector3 moveDir = mouseHitPos - localPos;
			moveDir.Normalize();
			 
			math::Vector3 nextMoveTargetPos = moveDir * mMoveSpeed;
			rb->SetVelocity(nextMoveTargetPos);
		}

		if (Input::GetKey(eKeyCode::SPACE))
		{
			rb->SetVelocity(math::Vector3::Zero);
		}
	}

	void PlayerScript::Render()
	{

	}

	void PlayerScript::OnCollisionEnter(Collider3D* collider)
	{

	}

	void PlayerScript::OnCollisionStay(Collider3D* collider)
	{
	}

	void PlayerScript::OnCollisionExit(Collider3D* collider)
	{
	}

	void PlayerScript::Start()
	{
	}

	void PlayerScript::Action()
	{
	}

	void PlayerScript::End()
	{
	}

}
