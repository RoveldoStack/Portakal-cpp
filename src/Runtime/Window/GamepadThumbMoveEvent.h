#pragma once
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Input/GamepadThumbs.h>

namespace Portakal
{
	class PORTAKAL_API GamepadThumbMoveEvent : public WindowEvent
	{
	public:
		GamepadThumbMoveEvent(const GamepadThumbs thumb, const float x, const float y, int index) : mThumb(thumb), mX(x), mY(y) {}
		~GamepadThumbMoveEvent() = default;

		FORCEINLINE GamepadThumbs GetThumb() const noexcept { return mThumb; }
		FORCEINLINE float GetX() const noexcept { return mX; }
		FORCEINLINE float GetY() const noexcept { return mY; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::GamepadThumbMove; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Gamepad thumb move: " + String::GetFromFloat(mX) + ":" + String::GetFromFloat(mY); }
	private:
		const GamepadThumbs mThumb;
		const float mX;
		const float mY;
	};
}