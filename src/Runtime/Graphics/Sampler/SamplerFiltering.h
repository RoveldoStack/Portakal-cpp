#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available sampler filtering types
	/// </summary>
	enum class PORTAKAL_API SamplerFiltering
	{
        //
       // Summary:
       //     Point sampling is used for minification, magnification, and mip-level sampling.
        MinPoint_MagPoint_MipPoint,
        //
        // Summary:
        //     Point sampling is used for minification and magnification; linear interpolation
        //     is used for mip-level sampling.
        MinPoint_MagPoint_MipLinear,
        //
        // Summary:
        //     Point sampling is used for minification and mip-level sampling; linear interpolation
        //     is used for mip-level sampling.
        MinPoint_MagLinear_MipPoint,
        //
        // Summary:
        //     Point sampling is used for minification; linear interpolation is used for magnification
        //     and mip-level sampling.
        MinPoint_MagLinear_MipLinear,
        //
        // Summary:
        //     Linear interpolation is used for minifcation; point sampling is used for magnification
        //     and mip-level sampling.
        MinLinear_MagPoint_MipPoint,
        //
        // Summary:
        //     Linear interpolation is used for minification and mip-level sampling; point sampling
        //     is used for magnification.
        MinLinear_MagPoint_MipLinear,
        //
        // Summary:
        //     Linear interpolation is used for minification and magnification, and point sampling
        //     is used for mip-level sampling.
        MinLinear_MagLinear_MipPoint,
        //
        // Summary:
        //     Linear interpolation is used for minification, magnification, and mip-level sampling.
        MinLinear_MagLinear_MipLinear,
        //
        // Summary:
        //     Anisotropic filtering is used. The maximum anisotropy is controlled by Veldrid.SamplerDescription.MaximumAnisotropy.
        Anisotropic
	};
}