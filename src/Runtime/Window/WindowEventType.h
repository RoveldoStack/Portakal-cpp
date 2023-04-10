#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Existing window event types
	/// </summary>
	enum class PORTAKAL_API WindowEventType
	{
		WindowClosed,
		WindowMoved,
		WindowResized,

		DragDrop,

		KeyboardDown,
		KeyboardUp,
		Char,

		MouseButtonDown,
		MouseButtonUp,
		MouseMoved,
		MouseScrolled,

		GamepadButtonDown,
		GamepadButtonUp,
		GamepadTriggerMove,
		GamepadThumbMove
	};
}