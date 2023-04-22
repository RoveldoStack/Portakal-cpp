#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available input element data types
	/// </summary>
	enum class InputElementDataFormat : unsigned char
	{
         //
        // Summary:
        //     One 32-bit floating point value.
        Float1,
        //
        // Summary:
        //     Two 32-bit floating point values.
        Float2,
        //
        // Summary:
        //     Three 32-bit floating point values.
        Float3,
        //
        // Summary:
        //     Four 32-bit floating point values.
        Float4,
        //
        // Summary:
        //     Two 8-bit unsigned normalized integers.
        Byte2_Norm,
        //
        // Summary:
        //     Two 8-bit unisgned integers.
        Byte2,
        //
        // Summary:
        //     Four 8-bit unsigned normalized integers.
        Byte4_Norm,
        //
        // Summary:
        //     Four 8-bit unsigned integers.
        Byte4,
        //
        // Summary:
        //     Two 8-bit signed normalized integers.
        SByte2_Norm,
        //
        // Summary:
        //     Two 8-bit signed integers.
        SByte2,
        //
        // Summary:
        //     Four 8-bit signed normalized integers.
        SByte4_Norm,
        //
        // Summary:
        //     Four 8-bit signed integers.
        SByte4,
        //
        // Summary:
        //     Two 16-bit unsigned normalized integers.
        UShort2_Norm,
        //
        // Summary:
        //     Two 16-bit unsigned integers.
        UShort2,
        //
        // Summary:
        //     Four 16-bit unsigned normalized integers.
        UShort4_Norm,
        //
        // Summary:
        //     Four 16-bit unsigned integers.
        UShort4,
        //
        // Summary:
        //     Two 16-bit signed normalized integers.
        Short2_Norm,
        //
        // Summary:
        //     Two 16-bit signed integers.
        Short2,
        //
        // Summary:
        //     Four 16-bit signed normalized integers.
        Short4_Norm,
        //
        // Summary:
        //     Four 16-bit signed integers.
        Short4,
        //
        // Summary:
        //     One 32-bit unsigned integer.
        UInt1,
        //
        // Summary:
        //     Two 32-bit unsigned integers.
        UInt2,
        //
        // Summary:
        //     Three 32-bit unsigned integers.
        UInt3,
        //
        // Summary:
        //     Four 32-bit unsigned integers.
        UInt4,
        //
        // Summary:
        //     One 32-bit signed integer.
        Int1,
        //
        // Summary:
        //     Two 32-bit signed integers.
        Int2,
        //
        // Summary:
        //     Three 32-bit signed integers.
        Int3,
        //
        // Summary:
        //     Four 32-bit signed integers.
        Int4,
        //
        // Summary:
        //     One 16-bit floating point value.
        Half1,
        //
        // Summary:
        //     Two 16-bit floating point values.
        Half2,
        //
        // Summary:
        //     Four 16-bit floating point values.
        Half4
	};
}