#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents the mouse moving event for the window
	/// </summary>
	class PORTAKAL_API MouseMovedEvent : public WindowEvent
	{
	public:
		MouseMovedEvent(const unsigned int x, const unsigned int y) : mX(x), mY(y) {}
		~MouseMovedEvent() = default;

		/// <summary>
		/// Returns pos-x
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetX() const noexcept { return mX; }

		/// <summary>
		/// Returns pos-y
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetY() const noexcept { return mY; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::MouseMoved; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Mouse moved: " + String::GetFromInteger(mX) + "," + String::GetFromInteger(mY); }
	private:
		unsigned int mX;
		unsigned int mY;
	};
}