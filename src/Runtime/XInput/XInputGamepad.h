#pragma once
#include <Runtime/Input/Gamepad.h>

namespace Portakal
{
	class PORTAKAL_API XInputGamepad : public Gamepad
	{
		friend class XInputManager;
	public:
		XInputGamepad(const unsigned int index) : Gamepad(index)
		{

		}
		~XInputGamepad() = default;


	private:

		// Inherited via Gamepad
		virtual void SetVibration(const short rightMotorPower, const short leftMotorPower) override;
		// Inherited via Gamepad
		virtual void DestroyCore() override;
	};
}