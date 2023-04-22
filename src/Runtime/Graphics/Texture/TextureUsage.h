#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available texture usages
	/// </summary>
	enum class PORTAKAL_API TextureUsage : unsigned int
	{
        Sampled = 1 << 0,
        Storage = 1 << 1,
        RenderTarget = 1 << 2,
        DepthStencil = 1 << 3,
        Cubemap = 1 << 4,
        Staging = 1 << 5,
	};

	FORCEINLINE static TextureUsage operator |(const TextureUsage a, const TextureUsage b)
	{
		return (TextureUsage)((unsigned int)a | (unsigned int)b);
	}

	FORCEINLINE static bool operator &(const TextureUsage a, const TextureUsage b)
	{
		return ((unsigned int)a & (unsigned int)b);
	}
}