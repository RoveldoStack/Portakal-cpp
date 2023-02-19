#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic time management class
	/// </summary>
	class PORTAKAL_API PlatformTime
	{
	public:
		PlatformTime() = delete;
		~PlatformTime() = delete;

		/// <summary>
		/// Returns the current runtime time as nanoseconds
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static unsigned long long GetCurrentTimeAsNanoseconds();
	};
}