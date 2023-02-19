#pragma once
#include <Runtime/Graphics/TextureFormat.h>
#include <dxgi.h>
#include <Runtime/Graphics/InputElementDataFormat.h>

namespace Portakal
{
	/// <summary>
	/// Utilities for the dxgi interface
	/// </summary>
	class PORTAKAL_API DXGIUtils
	{
	public:
		DXGIUtils() = delete;
		~DXGIUtils() = delete;

		/// <summary>
		/// Returns the dxgi texture format
		/// </summary>
		/// <param name="format"></param>
		/// <returns></returns>
		FORCEINLINE static DXGI_FORMAT GetTextureFormat(const TextureFormat format);

		/// <summary>
		/// Returns the dxgi format for the input element 
		/// </summary>
		/// <param name="type"></param>
		/// <returns></returns>
		FORCEINLINE static DXGI_FORMAT GetInputElementFormat(const InputElementDataFormat type);
	};
}