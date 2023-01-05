#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Supported shader stages
	/// </summary>
	enum class PORTAKAL_API ShaderStage
	{
		None,
		Vertex,
		Fragment,
		TesellationEval,
		TesellationControl,
		Compute
	};
}