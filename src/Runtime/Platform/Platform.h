#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Platform/PlatformType.h>

namespace Portakal
{
	class PORTAKAL_API Platform
	{
	public:
		FORCEINLINE static PlatformType GetCurrentPlatform();
	public:
		Platform() = delete;
		~Platform() = delete;
	};
}