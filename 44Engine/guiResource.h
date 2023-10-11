#pragma once
#include "guiWidget.h"
#include "yaResource.h"


namespace gui
{
	class Resource : public Widget
	{
	public:
		Resource();
		~Resource();

		virtual void FixedUpdate() override;

		void SetTarget(md::Resource* target) { mTarget = target; }
		md::Resource* GetTarget() { return mTarget; }

	private:
		md::Resource* mTarget;
	};
}
