#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Supported cpu architectures
	/// </summary>
	enum class PORTAKAL_API CpuArchitecture
	{
		Amdx86,
		Amdx64,
		Armx86,
		Armx64,
		Ppcx86,
		Ppcx64
	};
}