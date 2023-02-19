#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Window/WindowEventType.h>

namespace Portakal
{
	/// <summary>
	/// An event emitted from a window
	/// </summary>
	class PORTAKAL_API WindowEvent
	{
	public:
		~WindowEvent() = default;

		/// <summary>
		/// Returns the event type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual WindowEventType GetEventType() const noexcept = 0;

		/// <summary>
		/// Returns the event message
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual String GetEventMessage() const noexcept = 0;

		/// <summary>
		/// Returns whether this event is handled and should not be consumed!
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsHandled() const noexcept { return mHandled; }

		/// <summary>
		/// Marks the event handled
		/// </summary>
		void MarkHandled() { mHandled = true; }

	protected:
		WindowEvent() : mHandled(false) {}
	private:
		bool mHandled;
	};
}