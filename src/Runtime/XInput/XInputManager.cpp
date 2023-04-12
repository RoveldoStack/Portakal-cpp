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
#include <Runtime/Input/InputAPI.h>
#include "XInputGamepad.h"

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
		for (DWORD userIndex = 0; userIndex < XUSER_MAX_COUNT; userIndex++)
		{
			/*
			* Get state
			*/
			XINPUT_STATE state = {};
			if (XInputGetState(userIndex, &state) != ERROR_SUCCESS) // failed to get this user index's gamepad
			{
				/*
				* Check if there is a gamepad with this index
				*/
				{
					const Array<SharedSafeHeap<Gamepad>> gamepads = InputAPI::GetGamepads();
					SharedSafeHeap<XInputGamepad> pFoundGamepad = nullptr;
					for (unsigned int gamepadIndex = 0; gamepadIndex < gamepads.GetCursor(); gamepadIndex++)
					{
						const SharedSafeHeap<Gamepad> pGamepad = gamepads[gamepadIndex];
						if (pGamepad->GetIndex() == userIndex)
						{
							pFoundGamepad = pGamepad;
							break;
						}
					}

					if (pFoundGamepad != nullptr)
					{
						pressedButtons[userIndex].Clear();
						InputAPI::RemoveGamepad(pFoundGamepad);

						LOG("XInputManager", "Removed gamepad");
					}
				}
				continue;
			}

			/*
			* Register new device 
			*/
			SharedSafeHeap<XInputGamepad> pCurrentGamepad = nullptr;

			{
				const Array<SharedSafeHeap<Gamepad>> gamepads = InputAPI::GetGamepads();
				bool bHasIndex = false;
				for (unsigned int gamepadIndex = 0; gamepadIndex < gamepads.GetCursor(); gamepadIndex++)
				{
					SharedSafeHeap<Gamepad> pGamepad = gamepads[gamepadIndex];
					if (pGamepad->GetIndex() == userIndex)
					{
						bHasIndex = true;
						pCurrentGamepad = pGamepad;
						break;
					}
				}

				if (!bHasIndex)
				{

					/*
					* Get the device capabilities
					*/
					XINPUT_CAPABILITIES capabilities = {};
					XInputGetCapabilities(userIndex, XINPUT_FLAG_GAMEPAD, &capabilities);

					/*
					* Create device
					*/
					pCurrentGamepad = new XInputGamepad(userIndex);
					
					InputAPI::RegisterGamepad(pCurrentGamepad);
					LOG("XInputManager", "Registered gamepad");
				}
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

				if (!pressedButtons[userIndex].Has(button))
				{
					pressedButtons[userIndex].Add(button);

					pWin32Window->DispatchWin32Event(new GamepadButtonDownEvent(button, userIndex));
				}
			}
			
			/*
			* Check for released buttons
			*/
			for (unsigned int buttonIndex = 0; buttonIndex < pressedButtons[userIndex].GetCursor(); buttonIndex++)
			{
				const GamepadButtons button = pressedButtons[userIndex][buttonIndex];

				if (!currentButtons.Has(button))
				{
					pressedButtons[userIndex].Remove(button);

					pWin32Window->DispatchWin32Event(new GamepadButtonUpEvent(button, userIndex));

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
			
			pCurrentGamepad->SetLeftTrigger(leftTriggerAmount);
			pCurrentGamepad->SetRightTrigger(rightTriggerAmount);

			/*
			* Collect thumbs
			*/
			const float thumbLeftX = state.Gamepad.sThumbLX / (float)SHRT_MAX;
			const float thumbLeftY = state.Gamepad.sThumbLY / (float)SHRT_MAX;
			const float thumbRightX = state.Gamepad.sThumbRX / (float)SHRT_MAX;
			const float thumbRightY = state.Gamepad.sThumbRY / (float)SHRT_MAX;

			if (thumbLeftX != 0 || thumbLeftY != 0) // validate left thumb
			{
				pWin32Window->DispatchWin32Event(new GamepadThumbMoveEvent(GamepadThumbs::Left, thumbLeftX, thumbLeftY, userIndex));
			}
			if (thumbRightX != 0 || thumbRightY != 0)
			{
				pWin32Window->DispatchWin32Event(new GamepadThumbMoveEvent(GamepadThumbs::Right, thumbRightX, thumbRightY, userIndex));
			}

			pCurrentGamepad->SetLeftThumb({ thumbLeftX,thumbLeftY });
			pCurrentGamepad->SetRightThumb({ thumbRightX,thumbRightY });
		}
	}
}