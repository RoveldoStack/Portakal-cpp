#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Available resource submit shader stages
	/// </summary>
	enum class PORTAKAL_API ResourceSubmitShaderStage : unsigned int
	{
		Vertex,
		Fragment,
		TesellationEval,
		TesellationControl,
		Compute
	};
}