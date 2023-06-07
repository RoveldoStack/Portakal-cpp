#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Math/Vector2F.h>
#include <Runtime/Object/TaggedObject.h>

namespace Portakal
{
	/// <summary>
	/// Represents a connected gamepad device instance
	/// </summary>
	class PORTAKAL_API Gamepad : public TaggedObject
	{
		friend class InputAPI;
	public:
		Gamepad(const unsigned int index) :mIndex(index),mTriggerLeft(0),mTriggerRight(0) {}
		~Gamepad() = default;

		/// <summary>
		/// Returns the connection port index for the device
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetIndex() const noexcept { return mIndex; }

		/// <summary>
		/// Returns how much left trigger is moved
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float GetLeftTrigger() const noexcept { return mTriggerLeft; }

		/// <summary>
		/// Returns how much right trigger is moved
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float GetRightTrigger() const noexcept { return mTriggerRight; }

		/// <summary>
		/// Returns how much left thumb is moved
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2F GetLeftThumb() const noexcept { return mThumbLeft; }

		/// <summary>
		/// Returns how much right thumb is moved
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Vector2F GetRightThumb() const noexcept { return mThumbRight; }

		/// <summary>
		/// Sends a vibration message
		/// </summary>
		/// <param name="rightMotorPower"></param>
		/// <param name="leftMotorPower"></param>
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