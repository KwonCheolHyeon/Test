﻿#include "yaInput.h"
#include "yaApplication.h"


extern md::Application application;
namespace md
{
	std::vector<Input::Key> Input::mKeys;
	math::Vector2 Input::mMouseWinPos;
	math::Vector2 Input::mMouseWinPosPrev;
	math::Vector2 Input::mMouseIngameLocalPos;
	math::Vector2 Input::mMouseDir;

	int ASCII[(UINT)eKeyCode::END] =
	{
		//Alphabet
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',
		
		//Special Key
		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		//Num Pad
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,

		//Num Line
		'0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9',
	};
	

	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key key;
			key.eType = (eKeyCode)i;
			key.eState = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		if (GetFocus())
		{
			//KEY 정보 갱신
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				// 해당키가 현재 눌려있다.
				if (GetAsyncKeyState(ASCII[i]) & 0x8000)
				{
					// 이전 프레임에도 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::PRESSED;
					else
						mKeys[i].eState = eKeyState::DOWN;

					mKeys[i].bPressed = true;
				}
				else // 해당키가 현재 안눌려있다.
				{
					// 이전 프레임에는 눌려 있었다.
					if (mKeys[i].bPressed)
						mKeys[i].eState = eKeyState::UP;
					else // 이전 프레임에도 안눌려 있었다.
						mKeys[i].eState = eKeyState::NONE;

					mKeys[i].bPressed = false;
				}
			}

			//Mouse 위치 갱신
			mMouseWinPosPrev = mMouseWinPos;
			
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(application.GetHwnd(), &mousePos);
			mMouseWinPos.x = static_cast<float>(mousePos.x);
			mMouseWinPos.y = static_cast<float>(mousePos.y);

			const static Vector2 screenSize = application.GetSize();

			mMouseIngameLocalPos.x = mMouseWinPos.x - screenSize.x * 0.5f;
			mMouseIngameLocalPos.y = screenSize.y * 0.5f - mMouseWinPos.y;

			mMouseDir = mMouseWinPos - mMouseWinPosPrev;
			mMouseDir.y *= -1.f;
		}
		else
		{
			for (UINT i = 0; i < (UINT)eKeyCode::END; ++i)
			{
				if (eKeyState::DOWN == mKeys[i].eState || eKeyState::PRESSED == mKeys[i].eState)
					mKeys[i].eState = eKeyState::UP;
				else if (eKeyState::UP == mKeys[i].eState)
					mKeys[i].eState = eKeyState::NONE;

				mKeys[i].bPressed = false;
			}
		}

	}
}
