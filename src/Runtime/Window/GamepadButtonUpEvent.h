#pragma once
#include <Runtime/Window/GamepadButtonEvent.h>
#include <Runtime/Input/GamepadButtons.h>

namespace Portakal
{
	class PORTAKAL_API GamepadButtonUpEvent : public GamepadButtonEvent
	{
	public:
		GamepadButtonUpEvent(const GamepadButtons button,const unsigned int index) : GamepadButtonEvent(button,index)
		{

		}
		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::GamepadButtonUp; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Gamepadbutton up, index: " + String::GetFromInteger(GetIndex()) + ". Button: " + String::GetFromInteger((unsigned int)GetButton()); }
	};
}