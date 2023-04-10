#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class PORTAKAL_API Gamepad
	{
	public:
		Gamepad(const unsigned int index) :mIndex(index) {}
		~Gamepad() = default;

		FORCEINLINE unsigned int GetIndex() const noexcept { return mIndex; }
		void SetVibration(const short rightMotorPower, const short leftMotorPower) { SetVibrationCore(rightMotorPower, leftMotorPower); }
	protected:
		virtual void SetVibrationCore(const short rightMotorPower,const short leftMotorPower) = 0;
	private:
		const unsigned int mIndex;
	};
}