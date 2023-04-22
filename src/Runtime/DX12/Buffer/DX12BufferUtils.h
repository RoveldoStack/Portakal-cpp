#pragma once
#include <Runtime/Core/Core.h>
#include <dxgi.h>

namespace Portakal
{
	class PORTAKAL_API DX12BufferUtils
	{
	public:
		DX12BufferUtils() = delete;
		~DX12BufferUtils() = delete;

		FORCEINLINE static DXGI_FORMAT GetIndexFormat(const unsigned elementSizeInBytes);
	};
}