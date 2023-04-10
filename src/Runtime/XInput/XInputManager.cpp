#include "XInputManager.h"
#include <Windows.h>
#include <Xinput.h>
#include <Runtime/Log/Log.h>
#include <Runtime/Input/GamepadButtons.h>
#include <Runtime/Win32/Win32Window.h>
#include <Runtime/Window/GamepadButtonDownEvent.h>
#include <Runtime/Window/GamepadButtonUpEvent.h>
#include <Runtime/Window/GamepadTriggerMoveEvent.h>
#include <Runtime/Window/GamepadThumbMoveEvent.h>
#include <Runtime/Memory/Memory.h>

namespace Portakal
{
	Array<GamepadButtons> currentButtons;
	Array<GamepadButtons> pressedButtons[XUSER_MAX_COUNT];

	void XInputManager::Initialize()
	{
		currentButtons = Array<GamepadButtons>(100);
	}

	void XInputManager::CollectGamepadInputStates(Window* pWindow)
	{
		Win32Window* pWin32Window = (Win32Window*)pWindow;

		/*
		* Iterate connections
		*/
		for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
		{
			/*
			* Get state
			*/
			XINPUT_STATE state = {};
			if (XInputGetState(i, &state) != ERROR_SUCCESS)
			{
				continue;
			}

			/*
			* Collect buttons
			*/
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
			{
				GamepadButtons button = GamepadButtons::A;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				GamepadButtons button = GamepadButtons::B;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				GamepadButtons button = GamepadButtons::X;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				GamepadButtons button = GamepadButtons::Y;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
			{
				GamepadButtons button = GamepadButtons::DPadLeft;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
			{
				GamepadButtons button = GamepadButtons::DPadRight;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
			{
				GamepadButtons button = GamepadButtons::DPadUp;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
			{
				GamepadButtons button = GamepadButtons::DPadDown;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
			{
				GamepadButtons button = GamepadButtons::ShouldLeft;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
			{
				GamepadButtons button = GamepadButtons::ShouldRight;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB)
			{
				GamepadButtons button = GamepadButtons::ThumbLeft;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)
			{
				GamepadButtons button = GamepadButtons::ThumRight;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				GamepadButtons button = GamepadButtons::Back;
				currentButtons.Add(button);
			}
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				GamepadButtons button = GamepadButtons::Start;
				currentButtons.Add(button);
			}

			/*
			* Check for newly pressed buttons
			*/
			for (unsigned int buttonIndex = 0; buttonIndex < currentButtons.GetCursor(); buttonIndex++)
			{
				const GamepadButtons button = currentButtons[buttonIndex];

				if (!pressedButtons[i].Has(button))
				{
					pressedButtons[i].Add(button);

					pWin32Window->DispatchWin32Event(new GamepadButtonDownEvent(button,i));
				}
			}
			
			/*
			* Check for released buttons
			*/
			for (unsigned int buttonIndex = 0; buttonIndex < pressedButtons[i].GetCursor(); buttonIndex++)
			{
				const GamepadButtons button = pressedButtons[i][buttonIndex];

				if (!currentButtons.Has(button))
				{
					pressedButtons[i].Remove(button);

					pWin32Window->DispatchWin32Event(new GamepadButtonUpEvent(button, i));

					buttonIndex--;
				}
			}

			/*
			* Reset buttons
			*/
			currentButtons.Reset();

			/*
			* Collect triggers
			*/
			const float leftTriggerAmount = (float)state.Gamepad.bLeftTrigger / UCHAR_MAX;
			const float rightTriggerAmount = (float)state.Gamepad.bRightTrigger / UCHAR_MAX;

			if (leftTriggerAmount != 0)
			{
				pWin32Window->DispatchWin32Event(new GamepadTriggerMoveEvent(GamepadTriggers::Left, leftTriggerAmount));
			}
			if (rightTriggerAmount != 0)
			{
				pWin32Window->DispatchWin32Event(new GamepadTriggerMoveEvent(GamepadTriggers::Right, rightTriggerAmount));
			}
			
			/*
			* Collect thumbs
			*/
			const float thumbLeftX = state.Gamepad.sThumbLX / (float)SHRT_MAX;
			const float thumbLeftY = state.Gamepad.sThumbLY / (float)SHRT_MAX;
			const float thumbRightX = state.Gamepad.sThumbRX / (float)SHRT_MAX;
			const float thumbRightY = state.Gamepad.sThumbRY / (float)SHRT_MAX;

			if (thumbLeftX != 0 || thumbLeftY != 0) // validate left thumb
			{
				pWin32Window->DispatchWin32Event(new GamepadThumbMoveEvent(GamepadThumbs::Left, thumbLeftX, thumbLeftY, i));
			}
			if (thumbRightX != 0 || thumbRightY != 0)
			{
				pWin32Window->DispatchWin32Event(new GamepadThumbMoveEvent(GamepadThumbs::Right, thumbRightX, thumbRightY, i));
			}
		}
	}
}