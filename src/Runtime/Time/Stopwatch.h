#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Stopwatch is used for measuring the times between marks, usefull for how much time passed between positions
	/// </summary>
	class PORTAKAL_API Stopwatch
	{
	public:
		Stopwatch() : mMarkedTime(0) {}
		~Stopwatch() = default;

		/// <summary>
		/// Returns the passed time as nanoseconds
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long long GetAsNanoseconds() const noexcept;

		/// <summary>
		/// Returns the passed time as milliseconds
		/// </summary>
		/// <returns></returns>
		FORCEINLINE float GetAsMilliseconds() const noexcept;

		/// <summary>
		/// Marks a position
		/// </summary>
		void Mark();

		/// <summary>
		/// Resets
		/// </summary>
		void Reset();
	private:
		unsigned long long mMarkedTime;
		unsigned long long mLastDifference;
	};
}