#pragma once
#include "yaEngine.h"
#include "yaGraphics.h"
#include "guiWidget.h"

namespace md
{
	class GameObject;
}

namespace gui
{
	class WidgetManager
	{
	public:

		static void Initialize();
		static void Release();
		static void Run();

		static void ImGui_Initialize();
		static void ImGui_Run();
		static void ImGui_Release();

		static class Hierarchy* GetHierachy() { return mHierarchy; }
		static class YamYamEditor* GetVisualEditor() { return mVisualEditor; }

		template<typename T>
		static void Insert(std::string name, T* widget)
		{
			auto iter = mWidgets.find(name);
			if (iter == mWidgets.end())
				mWidgets.insert(std::make_pair(name, widget));
		}

		template<typename T>
		static T* GetWidget(const std::string& name)
		{
			auto iter = mWidgets.find(name);
			if (iter == mWidgets.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

	private:
		static std::map<std::string, Widget*> mWidgets;

		static class Hierarchy* mHierarchy;
		static class YamYamEditor* mVisualEditor;
	};
}
