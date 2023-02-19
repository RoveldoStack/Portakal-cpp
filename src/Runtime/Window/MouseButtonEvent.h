#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Base mouse button event
	/// </summary>
	class PORTAKAL_API MouseButtonEvent : public WindowEvent
	{
	public:

		/// <summary>
		/// Returns the related button
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetButton() const noexcept { return mButton; }
	protected:
		MouseButtonEvent(const unsigned int button) : mButton(button) {}
		~MouseButtonEvent() = default;
	private:
		unsigned int mButton;
	};
}