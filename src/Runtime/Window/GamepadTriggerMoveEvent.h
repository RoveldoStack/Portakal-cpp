#pragma once
#include <Runtime/Window/WindowEvent.h>
#include <Runtime/Input/GamepadTriggers.h>

namespace Portakal
{
	class PORTAKAL_API GamepadTriggerMoveEvent : public WindowEvent
	{
	public:
		GamepadTriggerMoveEvent(const GamepadTriggers trigger,const float amount) : mTrigger(trigger),mAmount(amount) {}
		~GamepadTriggerMoveEvent() = default;

		FORCEINLINE GamepadTriggers GetTrigger() const noexcept { return mTrigger; }
		FORCEINLINE float GetTriggerAmount() const noexcept { return mAmount; }

		FORCEINLINE virtual WindowEventType GetEventType() const noexcept override final { return WindowEventType::GamepadTriggerMove; }
		FORCEINLINE virtual String GetEventMessage() const noexcept override final { return "Gamepad trigger move: " + String::GetFromFloat(mAmount); }
	private:
		const GamepadTriggers mTrigger;
		const float mAmount;
	};
}