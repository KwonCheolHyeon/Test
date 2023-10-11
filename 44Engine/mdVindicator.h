#pragma once
#include "yaGameObject.h"

namespace md 
{
	class Vindicator : public GameObject
	{
	public:
		Vindicator();
		virtual ~Vindicator();

		virtual void Initalize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void PrevRender() override;
		virtual void Render() override;

	private:

	};

}


