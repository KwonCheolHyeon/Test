#pragma once
#include "yaGameObject.h"

namespace md
{
	class Zombie : public GameObject
	{
	public:
		Zombie();
		virtual ~Zombie();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void PrevRender() override;
		virtual void Render() override;

	private:

	};
}
