#pragma once
#include <Runtime/Window/MouseButtonEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a mouse button down event for the window
	/// </summary>
	class PORTAKAL_API MouseButtonDownEvent : public MouseButtonEvent
	{
	public:
		MouseButtonDownEvent(const unsigned int button) : MouseButtonEvent(button) {}
		~MouseButtonDownEvent() = default;

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::MouseButtonDown; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Mouse button down [" + String::GetFromInteger(GetButton()) + "]"; }
	};
}