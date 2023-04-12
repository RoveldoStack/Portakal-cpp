#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Math/Vector2.h>
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	class PORTAKAL_API Gamepad : public TaggedObject
	{
		friend class InputAPI;
	public:
		Gamepad(const unsigned int index) :mIndex(index),mTriggerLeft(0),mTriggerRight(0) {}
		~Gamepad() = default;

		FORCEINLINE unsigned int GetIndex() const noexcept { return mIndex; }
		FORCEINLINE float GetLeftTrigger() const noexcept { return mTriggerLeft; }
		FORCEINLINE float GetRightTrigger() const noexcept { return mTriggerRight; }
		FORCEINLINE Vector2F GetLeftThumb() const noexcept { return mThumbLeft; }
		FORCEINLINE Vector2F GetRightThumb() const noexcept { return mThumbRight; }

		virtual void SetVibration(const short rightMotorPower, const short leftMotorPower) = 0;
	protected:
		void SetLeftTrigger(const float amount) { mTriggerLeft = amount; }
		void SetRightTrigger(const float amount) { mTriggerRight = amount; }
		void SetLeftThumb(const Vector2F amount) { mThumbLeft = amount; }
		void SetRightThumb(const Vector2F amount) { mThumbRight = amount; }
	private:
		const unsigned int mIndex;
		float mTriggerLeft;
		float mTriggerRight;
		Vector2F mThumbLeft;
		Vector2F mThumbRight;
	};
}