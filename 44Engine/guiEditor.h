#pragma once
#include "yaEngine.h"

namespace gui
{
	class Widget;
	class EditorObject;
	class DebugObject;
	class Editor
	{
	public:
		Editor();
		virtual ~Editor();

		void Initialize();
		void Run();

		void Release();
		void DestroySingle();
		

	private:
		bool mEnable = false;
	};
}
