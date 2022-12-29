#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents the movement event of the window
	/// </summary>
	class PORTAKAL_API WindowMovedEvent : public WindowEvent
	{
	public:
		WindowMovedEvent(const unsigned int x, const unsigned int y) : mX(x), mY(y) {}
		~WindowMovedEvent() = default;

		FORCEINLINE unsigned int GetX() const noexcept { return mX; }
		FORCEINLINE unsigned int GetY() const noexcept { return mY; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::WindowMoved; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Window moved [" + String::GetFromInteger(mX) + " - " + String::GetFromInteger(mY) + "]"; }
	private:
		unsigned int mX;
		unsigned int mY;
	};
}