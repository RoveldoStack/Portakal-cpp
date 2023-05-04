#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents a char event
	/// </summary>
	class PORTAKAL_API KeyboardCharEvent : public WindowEvent
	{
	public:
		KeyboardCharEvent(const unsigned int character) : mChar(character) {}
		~KeyboardCharEvent() = default;

		/// <summary>
		/// Returns the typed char
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetChar() const noexcept { return mChar; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::Char; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Char event: " + mChar; }
	private:
		unsigned int mChar;
	};
}