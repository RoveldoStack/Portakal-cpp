#pragma once
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Input/GamepadButtons.h>

namespace Portakal
{
	class PORTAKAL_API GamepadButtonEvent : public WindowEvent
	{
	public:
		FORCEINLINE GamepadButtons GetButton() const noexcept { return mButton; }
		FORCEINLINE unsigned int GetIndex() const noexcept { return mIndex; }

	protected:
		GamepadButtonEvent(const GamepadButtons button,const unsigned int index) : mButton(button),mIndex(index) {}
		~GamepadButtonEvent() = default;
	private:
		const GamepadButtons mButton;
		const unsigned int mIndex;
	};
}