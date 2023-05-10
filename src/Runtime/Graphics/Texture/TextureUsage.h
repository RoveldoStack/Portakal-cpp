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
        RenderTarget = 1 << 2,
        DepthStencil = 1 << 3,
		CpuWrite = 1 << 4,
		CpuRead = 1 << 5
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