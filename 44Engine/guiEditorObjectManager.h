#pragma once
#include "yaEngine.h"
#include "guiDebugObject.h"
#include "guiEditorObject.h"
#include "yaGraphics.h"
#include "yaMath.h"



namespace gui
{
	class EditorObjectManager
	{
	public:
		EditorObjectManager();
		~EditorObjectManager();

		static void Initialize();
		static void Release();

		static void Run();

		static void Update();
		static void FixedUpdate();
		static void Render();
		static void DebugRender(md::graphics::DebugMesh& mesh);

		void InsertEditorObject(EditorObject* obj) { mEditorObjects.push_back(obj); }



	private:

		static std::vector<EditorObject*> mEditorObjects;
		static std::vector<DebugObject*> mDebugObjects;

	};
}
