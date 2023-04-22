#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a mouse wheel scroll event for the window
	/// </summary>
	class PORTAKAL_API MouseWheelEvent : public WindowEvent
	{
	public:
		MouseWheelEvent(const int horizontal, const int vertical) : mHorizontal(horizontal), mVertical(vertical) {}
		~MouseWheelEvent() = default;

		/// <summary>
		/// Returns the horizontal wheel amount
		/// </summary>
		/// <returns></returns>
		FORCEINLINE int GetHorizontal() const noexcept { return mHorizontal; }

		/// <summary>
		/// Returns the vertical wheel amount
		/// </summary>
		/// <returns></returns>
		FORCEINLINE int GetVertical() const noexcept { return mVertical; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::MouseScrolled; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Mouse wheel scrolled: [" + String::GetFromInteger(mHorizontal) + "," + String::GetFromInteger(mVertical) + "]"; }

	private:
		int mHorizontal;
		int mVertical;
	};
}