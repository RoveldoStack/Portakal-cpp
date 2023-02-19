#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/InputElementDesc.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a input layout for the vertex buffer
	/// </summary>
	struct PORTAKAL_API InputLayoutDesc
	{
		/// <summary>
		/// The input element items
		/// </summary>
		Array<InputElementDesc> Elements;

		/// <summary>
		/// Instance step rate if it's a instanced rendering
		/// </summary>
		unsigned int InstanceStepRate;
	};
}