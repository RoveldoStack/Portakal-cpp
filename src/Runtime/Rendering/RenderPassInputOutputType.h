#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Supported render pass inputout types
	/// </summary>
	enum class PORTAKAL_API RenderPassInputOutputType
	{
		RenderTarget,
		Texture,
		Color,
		Float,
		Integer,
		Bool,
		Finish,
		Other
	};
}