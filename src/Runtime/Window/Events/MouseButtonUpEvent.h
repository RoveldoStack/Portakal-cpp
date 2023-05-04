#pragma once
#include <Runtime/Window/Events/MouseButtonEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a mouse button down event for the window
	/// </summary>
	class PORTAKAL_API MouseButtonUpEvent : public MouseButtonEvent
	{
	public:
		MouseButtonUpEvent(const unsigned int button) : MouseButtonEvent(button) {}
		~MouseButtonUpEvent() = default;

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::MouseButtonUp; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Mouse button up [" + String::GetFromInteger(GetButton()) + "]"; }
	};
}