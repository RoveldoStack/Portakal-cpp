#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/StencilOperation.h>
#include <Runtime/Graphics/ComparisionMethod.h>

namespace Portakal
{
	/// <summary>
	/// Required information to specify a stencil face behaviour
	/// </summary>
	struct PORTAKAL_API StencilFaceDesc
	{
		/// <summary>
		/// On fail operation
		/// </summary>
		StencilOperation Fail;

		/// <summary>
		/// On pass operation
		/// </summary>
		StencilOperation Pass;

		/// <summary>
		/// On depth fail operation
		/// </summary>
		StencilOperation DepthFail;

		/// <summary>
		/// The comparision method
		/// </summary>
		ComparisionMethod Comparision;
	};
}

