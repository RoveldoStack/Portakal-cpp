#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	#define WAIT_INFINITE 0xFFFFFFFF

	/// <summary>
	/// Platform agnostic mutex implementation
	/// </summary>
	class PORTAKAL_API PlatformMutex
	{
	public:
		/// <summary>
		/// Creates anew mutex
		/// </summary>
		/// <returns></returns>
		static PlatformMutex* Create();
	public:
		PlatformMutex() = default;
		virtual ~PlatformMutex() = default;

		/// <summary>
		/// Tries to lock
		/// If it fails returns false
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual bool TryLock() = 0;

		/// <summary>
		/// Locks the mutex
		/// </summary>
		/// <param name="waitTime"></param>
		/// <returns></returns>
		FORCEINLINE virtual bool Lock(const unsigned long long waitTime) = 0;

		/// <summary>
		/// Releases the mutex
		/// </summary>
		FORCEINLINE virtual bool Release() = 0;
	};
}