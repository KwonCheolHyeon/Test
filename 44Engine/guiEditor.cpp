#include "guiEditor.h"
#include "yaApplication.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "guiYamYamEditor.h" 
#include "guiInspector.h"
#include "guiGame.h"
#include "guiHierarchy.h"
#include "guiProject.h"
#include "guiEditor.h"
#include "guiConsole.h"
#include "guiListWidget.h"

#include "guiDebugObject.h"
#include "guiEditorObject.h"
#include "guiWidget.h"
#include "yaGraphics.h"

#include "yaResources.h"
#include "yaInput.h"

#include "guiWidgetManager.h"
#include "guiEditorObjectManager.h"


extern md::Application application;
namespace gui
{
	Editor::Editor()
	{
	}
	Editor::~Editor()
	{
	}
	void Editor::Initialize()
	{
		EditorObjectManager::Initialize();
		WidgetManager::Initialize();
	}
	void Editor::Run()
	{
		if (md::Input::GetKey(md::eKeyCode::N_8))
		{
			if (mEnable == false)
			{
				Initialize();
				mEnable = true;
			}
			else
			{
				Release();
				mEnable = false;
			}
		}

		if (mEnable == false)
			return;

		EditorObjectManager::Run();
		WidgetManager::Run();
	}
	void Editor::Release()
	{
		if (mEnable == false)
			return;

		EditorObjectManager::Release();
		WidgetManager::Release();
	}
	void Editor::DestroySingle()
	{

	}
}
