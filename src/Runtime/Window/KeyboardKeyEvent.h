#pragma once
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Input/KeyboardKeys.h>

namespace Portakal
{
	/// <summary>
	/// Represents the base event for the keyboard key events
	/// </summary>
	class PORTAKAL_API KeyboardKeyEvent : public WindowEvent
	{
	public:
		/// <summary>
		/// Returns the related key
		/// </summary>
		/// <returns></returns>
		FORCEINLINE KeyboardKeys GetKey() const noexcept { return mKey; }
	protected:
		KeyboardKeyEvent(const KeyboardKeys key) : mKey(key) {}
		~KeyboardKeyEvent() = default;
	private:
		const KeyboardKeys mKey;
	};
}