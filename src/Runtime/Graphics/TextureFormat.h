#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	enum class PORTAKAL_API TextureFormat : unsigned char
	{
        None,
        //
       // Summary:
       //     RGBA component order. Each component is an 8-bit unsigned normalized integer.
        R8_G8_B8_A8_UNorm,
        //
        // Summary:
        //     BGRA component order. Each component is an 8-bit unsigned normalized integer.
        B8_G8_R8_A8_UNorm,
        //
        // Summary:
        //     Single-channel, 8-bit unsigned normalized integer.
        R8_UNorm,
        //
        // Summary:
        //     Single-channel, 16-bit unsigned normalized integer. Can be used as a depth format.
        R16_UNorm,
        //
        // Summary:
        //     RGBA component order. Each component is a 32-bit signed floating-point value.
        R32_G32_B32_A32_Float,
        //
        // Summary:
        //     Single-channel, 32-bit signed floating-point value. Can be used as a depth format.
        R32_Float,
        //
        // Summary:
        //     BC3 block compressed format.
        BC3_UNorm,
        //
        // Summary:
        //     A depth-stencil format where the depth is stored in a 24-bit unsigned normalized
        //     integer, and the stencil is stored in an 8-bit unsigned integer.
        D24_UNorm_S8_UInt,
        //
        // Summary:
        //     A depth-stencil format where the depth is stored in a 32-bit signed floating-point
        //     value, and the stencil is stored in an 8-bit unsigned integer.
        D32_Float_S8_UInt,
        //
        // Summary:
        //     RGBA component order. Each component is a 32-bit unsigned integer.
        R32_G32_B32_A32_UInt,
        //
        // Summary:
        //     RG component order. Each component is an 8-bit signed normalized integer.
        R8_G8_SNorm,
        //
        // Summary:
        //     BC1 block compressed format with no alpha.
        BC1_Rgb_UNorm,
        //
        // Summary:
        //     BC1 block compressed format with a single-bit alpha channel.
        BC1_Rgba_UNorm,
        //
        // Summary:
        //     BC2 block compressed format.
        BC2_UNorm,
        //
        // Summary:
        //     A 32-bit packed format. The 10-bit R component occupies bits 0..9, the 10-bit
        //     G component occupies bits 10..19, the 10-bit A component occupies 20..29, and
        //     the 2-bit A component occupies bits 30..31. Each value is an unsigned, normalized
        //     integer.
        R10_G10_B10_A2_UNorm,
        //
        // Summary:
        //     A 32-bit packed format. The 10-bit R component occupies bits 0..9, the 10-bit
        //     G component occupies bits 10..19, the 10-bit A component occupies 20..29, and
        //     the 2-bit A component occupies bits 30..31. Each value is an unsigned integer.
        R10_G10_B10_A2_UInt,
        //
        // Summary:
        //     A 32-bit packed format. The 11-bit R componnent occupies bits 0..10, the 11-bit
        //     G component occupies bits 11..21, and the 10-bit B component occupies bits 22..31.
        //     Each value is an unsigned floating point value.
        R11_G11_B10_Float,
        //
        // Summary:
        //     Single-channel, 8-bit signed normalized integer.
        R8_SNorm,
        //
        // Summary:
        //     Single-channel, 8-bit unsigned integer.
        R8_UInt,
        //
        // Summary:
        //     Single-channel, 8-bit signed integer.
        R8_SInt,
        //
        // Summary:
        //     Single-channel, 16-bit signed normalized integer.
        R16_SNorm,
        //
        // Summary:
        //     Single-channel, 16-bit unsigned integer.
        R16_UInt,
        //
        // Summary:
        //     Single-channel, 16-bit signed integer.
        R16_SInt,
        //
        // Summary:
        //     Single-channel, 16-bit signed floating-point value.
        R16_Float,
        //
        // Summary:
        //     Single-channel, 32-bit unsigned integer
        R32_UInt,
        //
        // Summary:
        //     Single-channel, 32-bit signed integer
        R32_SInt,
        //
        // Summary:
        //     RG component order. Each component is an 8-bit unsigned normalized integer.
        R8_G8_UNorm,
        //
        // Summary:
        //     RG component order. Each component is an 8-bit unsigned integer.
        R8_G8_UInt,
        //
        // Summary:
        //     RG component order. Each component is an 8-bit signed integer.
        R8_G8_SInt,
        //
        // Summary:
        //     RG component order. Each component is a 16-bit unsigned normalized integer.
        R16_G16_UNorm,
        //
        // Summary:
        //     RG component order. Each component is a 16-bit signed normalized integer.
        R16_G16_SNorm,
        //
        // Summary:
        //     RG component order. Each component is a 16-bit unsigned integer.
        R16_G16_UInt,
        //
        // Summary:
        //     RG component order. Each component is a 16-bit signed integer.
        R16_G16_SInt,
        //
        // Summary:
        //     RG component order. Each component is a 16-bit signed floating-point value.
        R16_G16_Float,
        //
        // Summary:
        //     RG component order. Each component is a 32-bit unsigned integer.
        R32_G32_UInt,
        //
        // Summary:
        //     RG component order. Each component is a 32-bit signed integer.
        R32_G32_SInt,
        //
        // Summary:
        //     RG component order. Each component is a 32-bit signed floating-point value.
        R32_G32_Float,
        //
        // Summary:
        //     RGBA component order. Each component is an 8-bit signed normalized integer.
        R8_G8_B8_A8_SNorm,
        //
        // Summary:
        //     RGBA component order. Each component is an 8-bit unsigned integer.
        R8_G8_B8_A8_UInt,
        //
        // Summary:
        //     RGBA component order. Each component is an 8-bit signed integer.
        R8_G8_B8_A8_SInt,
        //
        // Summary:
        //     RGBA component order. Each component is a 16-bit unsigned normalized integer.
        R16_G16_B16_A16_UNorm,
        //
        // Summary:
        //     RGBA component order. Each component is a 16-bit signed normalized integer.
        R16_G16_B16_A16_SNorm,
        //
        // Summary:
        //     RGBA component order. Each component is a 16-bit unsigned integer.
        R16_G16_B16_A16_UInt,
        //
        // Summary:
        //     RGBA component order. Each component is a 16-bit signed integer.
        R16_G16_B16_A16_SInt,
        //
        // Summary:
        //     RGBA component order. Each component is a 16-bit floating-point value.
        R16_G16_B16_A16_Float,
        //
        // Summary:
        //     RGBA component order. Each component is a 32-bit signed integer.
        R32_G32_B32_A32_SInt,
        //
        // Summary:
        //     A 64-bit, 4x4 block-compressed format storing unsigned normalized RGB data.
        ETC2_R8_G8_B8_UNorm,
        //
        // Summary:
        //     A 64-bit, 4x4 block-compressed format storing unsigned normalized RGB data, as
        //     well as 1 bit of alpha data.
        ETC2_R8_G8_B8_A1_UNorm,
        //
        // Summary:
        //     A 128-bit, 4x4 block-compressed format storing 64 bits of unsigned normalized
        //     RGB data, as well as 64 bits of alpha data.
        ETC2_R8_G8_B8_A8_UNorm,
        //
        // Summary:
        //     BC4 block compressed format, unsigned normalized values.
        BC4_UNorm,
        //
        // Summary:
        //     BC4 block compressed format, signed normalized values.
        BC4_SNorm,
        //
        // Summary:
        //     BC5 block compressed format, unsigned normalized values.
        BC5_UNorm,
        //
        // Summary:
        //     BC5 block compressed format, signed normalized values.
        BC5_SNorm,
        //
        // Summary:
        //     BC7 block compressed format.
        BC7_UNorm,
        //
        // Summary:
        //     RGBA component order. Each component is an 8-bit unsigned normalized integer.
        //     This is an sRGB format.
        R8_G8_B8_A8_UNorm_SRgb,
        //
        // Summary:
        //     BGRA component order. Each component is an 8-bit unsigned normalized integer.
        //     This is an sRGB format.
        B8_G8_R8_A8_UNorm_SRgb,
        //
        // Summary:
        //     BC1 block compressed format with no alpha. This is an sRGB format.
        BC1_Rgb_UNorm_SRgb,
        //
        // Summary:
        //     BC1 block compressed format with a single-bit alpha channel. This is an sRGB
        //     format.
        BC1_Rgba_UNorm_SRgb,
        //
        // Summary:
        //     BC2 block compressed format. This is an sRGB format.
        BC2_UNorm_SRgb,
        //
        // Summary:
        //     BC3 block compressed format. This is an sRGB format.
        BC3_UNorm_SRgb,
        //
        // Summary:
        //     BC7 block compressed format. This is an sRGB format.
        BC7_UNorm_SRgb
	};
}