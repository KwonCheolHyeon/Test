#include "mdZombie.h"

#include "mdDamageScript.h"
namespace md
{
	Zombie::Zombie()
	{
		
	}
	Zombie::~Zombie()
	{
	}
	void Zombie::Initalize()
	{
		GameObject::Initalize();
	}
	void Zombie::Update()
	{
		GameObject::Update();
	}
	void Zombie::FixedUpdate()
	{
		GameObject::FixedUpdate();
	}
	void Zombie::PrevRender()
	{
		GameObject::PrevRender();
	}
	void Zombie::Render()
	{
		DamageScript* scr = GetScript<DamageScript>();
		scr->HitFlash();
		GameObject::Render();
	}
}
