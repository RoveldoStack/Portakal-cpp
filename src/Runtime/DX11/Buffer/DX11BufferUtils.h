#pragma once
#include <Runtime/Graphics/Buffer/GraphicsBufferType.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API DX11BufferUtils
	{
	public:
		DX11BufferUtils() = delete;
		~DX11BufferUtils() = delete;

		FORCEINLINE static D3D11_USAGE GetUsage(const GraphicsBufferType type);
		FORCEINLINE static D3D11_CPU_ACCESS_FLAG GetCpuFlags(const GraphicsBufferType type);
	};
}