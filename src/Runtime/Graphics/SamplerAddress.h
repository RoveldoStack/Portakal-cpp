#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API SamplerAddress : unsigned char
	{
        //
       // Summary:
       //     Texture coordinates are wrapped upon overflow.
        Wrap,
        //
        // Summary:
        //     Texture coordinates are mirrored upon overflow.
        Mirror,
        //
        // Summary:
        //     Texture coordinates are clamped to the maximum or minimum values upon overflow.
        Clamp,
        //
        // Summary:
        //     Texture coordinates that overflow return the predefined border color defined
        //     in Veldrid.SamplerDescription.BorderColor.
        Border
	};
}