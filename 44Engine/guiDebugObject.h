#pragma once
#include "yaGameObject.h"


namespace gui
{
	class DebugObject : public md::GameObject
	{
	public:
		DebugObject();
		virtual ~DebugObject();

		virtual void FixedUpdate() override;
	
	private:
	};
}
