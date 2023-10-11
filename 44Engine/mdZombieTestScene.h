#pragma once
#include <yaScene.h>

namespace md
{
	class ZombieTestScene :
		public Scene
	{
	public:
		ZombieTestScene();
		virtual ~ZombieTestScene();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

	private:
	};
}
