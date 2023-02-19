#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available message box flags
	/// </summary>
	enum class PORTAKAL_API PlatformMessageBoxFlags : unsigned int
	{
		None = 1 << 0,
		Help = 1 << 1,
		OK = 1 << 2,
		IconExclamation = 1 << 3,
		IconWarning = 1 << 4,
		IconInformation = 1 << 5,
		IconAtRisk = 1 << 6,
		IconQuestion = 1 << 7,
		IconStop = 1 << 8
	};

	FORCEINLINE static PlatformMessageBoxFlags operator |(const PlatformMessageBoxFlags a, const PlatformMessageBoxFlags b)
	{
		return (PlatformMessageBoxFlags)((unsigned int)a | (unsigned int)b);
	}

	FORCEINLINE static bool operator &(const PlatformMessageBoxFlags a, const PlatformMessageBoxFlags b)
	{
		return ((unsigned int)a & (unsigned int)b);
	}
}