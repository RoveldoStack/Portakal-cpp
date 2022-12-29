#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API PlatformMessageBoxFlags : unsigned int
	{
		None,
		Help,
		OK,
		IconExclamation,
		IconWarning,
		IconInformation,
		IconAtRisk,
		IconQuestion,
		IconStop
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