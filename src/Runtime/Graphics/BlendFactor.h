#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Represents the possible blending values(coefs)
	/// </summary>
	enum class PORTAKAL_API BlendFactor
	{
        Zero,
        One,
        SourceAlpha,
        InverseSourceAlpha,
        DestinationAlpha,
        InverseDestinationAlpha,
        SourceColor,
        InverseSourceColor,
        DestinationColor,
        InverseDestinationColor,
        BlendFactor,
        InverseBlendFactor
	};
}