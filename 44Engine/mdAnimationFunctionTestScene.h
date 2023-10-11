#pragma once
#include "yaScene.h"

namespace md
{
	class AnimationFunctionTestScene : public Scene
	{
	public:
		// construtor destructor
		AnimationFunctionTestScene();
		virtual ~AnimationFunctionTestScene();

		// delete Function
		AnimationFunctionTestScene(const AnimationFunctionTestScene& _Other) = delete;
		AnimationFunctionTestScene(AnimationFunctionTestScene&& _Other) noexcept = delete;
		AnimationFunctionTestScene& operator=(const AnimationFunctionTestScene& _Other) = delete;
		AnimationFunctionTestScene& operator=(AnimationFunctionTestScene&& _Other) noexcept = delete;


		void Initalize() override;
		void Update() override;
		void FixedUpdate() override;
		void Render() override;
		void Destroy() override;

	public:
		void ChangeAnimTo1();
		void ChangeAnimTo4();

	protected:


	private:
		GameObject* m_Player;
	};
}
