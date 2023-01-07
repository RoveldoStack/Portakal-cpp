#pragma once
#include <Runtime/Graphics/TextureFormat.h>
#include <dxgi.h>
#include <Runtime/Graphics/InputElementDataFormat.h>

namespace Portakal
{
	class PORTAKAL_API DXGIUtils
	{
	public:
		DXGIUtils() = delete;
		~DXGIUtils() = delete;

		FORCEINLINE static DXGI_FORMAT GetTextureFormat(const TextureFormat format);
		FORCEINLINE static DXGI_FORMAT GetInputElementFormat(const InputElementDataFormat type);
	};
}