#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Available shader stages
	/// </summary>
	PENUM();
	enum class PORTAKAL_API ShaderStage : long long
	{
		None,
		Vertex,
		Fragment,
		TesellationEval,
		TesellationControl,
		Compute
	};

#include "ShaderStage.reflect.h"
}