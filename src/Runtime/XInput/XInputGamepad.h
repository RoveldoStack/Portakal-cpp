#pragma once
#include <Runtime/Input/Gamepad.h>

namespace Portakal
{
	class PORTAKAL_API XInputGamepad : public Gamepad
	{
	public:
		XInputGamepad(const unsigned int index) : Gamepad(index)
		{

		}
		~XInputGamepad() = default;


	private:

		// Inherited via Gamepad
		virtual void SetVibrationCore(const short rightMotorPower, const short leftMotorPower) override;
	};
}