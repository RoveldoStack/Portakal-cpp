#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents the resized event of the window
	/// </summary>
	class PORTAKAL_API WindowResizedEvent : public WindowEvent
	{
	public:
		WindowResizedEvent(const unsigned int width, const unsigned int height) : mWidth(width), mHeight(height) {}
		~WindowResizedEvent() = default;

		/// <summary>
		/// Returns the width
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }

		/// <summary>
		/// Returns the height
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::WindowResized; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Window resized"; }
	private:
		unsigned int mWidth;
		unsigned int mHeight;
	};
}