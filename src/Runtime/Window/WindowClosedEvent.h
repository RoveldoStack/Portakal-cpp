#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a window closing event
	/// </summary>
	class PORTAKAL_API WindowClosedEvent : public WindowEvent
	{
	public:
		WindowClosedEvent() = default;
		~WindowClosedEvent() = default;

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override { return WindowEventType::WindowClosed; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override { return "Window closed"; }
	};
}