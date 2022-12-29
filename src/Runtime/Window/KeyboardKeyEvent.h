#pragma once
#include <Runtime/Window/WindowEvent.h>

namespace Portakal
{
	/// <summary>
	/// Represents the base event for the keyboard key events
	/// </summary>
	class PORTAKAL_API KeyboardKeyEvent : public WindowEvent
	{
	public:
		FORCEINLINE unsigned int GetKey() const noexcept { return mKey; }
	protected:
		KeyboardKeyEvent(const unsigned int key) : mKey(key) {}
		~KeyboardKeyEvent() = default;
	private:
		unsigned int mKey;
	};
}