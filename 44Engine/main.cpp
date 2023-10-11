// 44Engine.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "44Engine.h"
#include "yaApplication.h"
#include "yaSceneManager.h"
#include "guiEditor.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "yaTitleScene.h"
#include "yaPlayScene.h"
#include "mdUITestScene.h"
#include "mdPhysXTestScene.h"
#include "mdAnimationFunctionTestScene.h"
#include "mdNavTestScene.h"
#include "mdZombieTestScene.h"

#ifdef _DEBUG
#include <dxgidebug.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "..\\External\\fbx\\lib\\Debug\\libfbxsdk-md.lib") 
#pragma comment(lib, "..\\External\\PhysX\\lib\\Debug\\PhysX_64.lib") 
#pragma comment(lib, "..\\x64\\Debug\\Lib\\Engine_SOURCE.lib") 

#else 

#pragma comment(lib, "..\\External\\fbx\\lib\\Release\\libfbxsdk-md.lib") 
#pragma comment(lib, "..\\External\\PhysX\\lib\\Release\\PhysX_64.lib") 
#pragma comment(lib, "..\\x64\\Release\\Lib\\Engine_SOURCE.lib") 

#endif


//#ifdef _DEBUG
//#pragma comment(lib, "..\\External\\fbx\\lib\\Debug\\libfbxsdk-md.lib") 
//#else 
//#pragma comment(lib, "..\\External\\fbx\\lib\\Release\\libfbxsdk-md.lib") 
//#endif


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

#ifdef _DEBUG
void D3DMemoryLeakCheck()
{
	HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));

	IDXGIDebug* debug;

	GetDebugInterface(IID_PPV_ARGS(&debug));

	OutputDebugStringW(L"===================================Starting Live Direct3D Object Dump:===========================================\r\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
	OutputDebugStringW(L"===================================Completed Live Direct3D Object Dump.==========================================\r\n");

	debug->Release();
}
#endif

md::Application application;
gui::Editor editor;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(83156);
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY44ENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    // 여기서 이니셜라이즈 함수들이 호출되고
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }




    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY44ENGINE));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 여기서 실제 무한 루프를 돌면서 모든 로직이 처리되고
            application.Run();

            editor.Run();
            application.Present();
        }
    }

    // 여기서 각종 해제되어야 것들이 할당 해제되고
    md::SceneManager::Release();
    application.Release();
    editor.Release();

#ifdef _DEBUG
	D3DMemoryLeakCheck();
#endif

    // 운영체제한테 잘 종료되었는지를 반환해
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY44ENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL/*MAKEINTRESOURCEW(IDC_MY44ENGINE)*/;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }


   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   // 1. 그래픽 디바이스 만들고 윈도우 만들어서 보여주고
   application.SetWindow(hWnd, 1600, 900);
   // 2. 각종 매니저 클래스를 초기화한다.
   application.Initalize();
   
   //md::SceneManager::CreateScene(md::eSceneType::TitleScene, new md::TitleScene());
   //md::SceneManager::CreateScene(md::eSceneType::PlayScene, new md::PlayScene());
   //md::SceneManager::CreateScene(md::eSceneType::UITestScene, new md::UITestScene());
   //md::SceneManager::CreateScene(md::eSceneType::PhysXTestScene, new md::PhysXTestScene());
   //md::SceneManager::CreateScene(md::eSceneType::AnimationFunctionTestScene, new md::AnimationFunctionTestScene());
   //md::SceneManager::CreateScene(md::eSceneType::NavTestScene, new md::NavTestScene());
   md::SceneManager::CreateScene(md::eSceneType::ZombieMonsterTestScene, new md::ZombieTestScene());

   
   md::SceneManager::LoadScene(md::eSceneType::ZombieMonsterTestScene);
   // 3. 에디터에서 관리하는 것들이 여기서 초기화되는데, 거기에는
   // 디버그 용 충돌체들과 imgui, imgui를 이용해서 만든 윈도우들이 있다.
   //editor.Initalize();

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            ::SetWindowPos(hWnd, nullptr, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
        }
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
