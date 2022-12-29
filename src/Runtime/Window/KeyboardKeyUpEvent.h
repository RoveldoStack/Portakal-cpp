#pragma once
#include <Runtime/Window/KeyboardKeyEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a keyboard key up event for the window
	/// </summary>
	class PORTAKAL_API KeyboardKeyUpEvent : public KeyboardKeyEvent
	{
	public:
		KeyboardKeyUpEvent(const unsigned int key) : KeyboardKeyEvent(key) {}
		~KeyboardKeyUpEvent() = default;

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::KeyboardUp; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Keyboard key up: " + String::GetFromInteger(GetKey()); }
	};
}