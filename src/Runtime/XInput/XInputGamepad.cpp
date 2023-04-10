#include "XInputGamepad.h"
#include <Windows.h>
#include <Xinput.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	void XInputGamepad::SetVibrationCore(const short rightMotorPower, const short leftMotorPower)
	{
		XINPUT_VIBRATION vibration = {};
		vibration.wLeftMotorSpeed = leftMotorPower;
		vibration.wRightMotorSpeed = rightMotorPower;

		XInputSetState(GetIndex(), &vibration);
	}
}