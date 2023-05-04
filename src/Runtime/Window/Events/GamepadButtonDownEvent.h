#pragma once
#include <Runtime/Window/Events/GamepadButtonEvent.h>
#include <Runtime/Input/GamepadButtons.h>

namespace Portakal
{
	class PORTAKAL_API GamepadButtonDownEvent : public GamepadButtonEvent
	{
	public:
		GamepadButtonDownEvent(const GamepadButtons button,const unsigned int index) : GamepadButtonEvent(button,index)
		{

		}
		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::GamepadButtonDown; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Gamepadbutton down, index: " + String::GetFromInteger(GetIndex()) + ". Button: " + String::GetFromInteger((unsigned int)GetButton()); }
	};
}