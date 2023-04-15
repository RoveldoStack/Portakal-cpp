#pragma once
#include <Runtime/Window/KeyboardKeyEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents the keyboard key down event for the window
	/// </summary>
	class PORTAKAL_API KeyboardKeyDownEvent : public KeyboardKeyEvent
	{
	public:
		KeyboardKeyDownEvent(const KeyboardKeys key) : KeyboardKeyEvent(key) {}
		~KeyboardKeyDownEvent() = default;

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::KeyboardDown; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Keyboard key down " + String::GetFromLongLong((long long)GetKey()); }
	};
}