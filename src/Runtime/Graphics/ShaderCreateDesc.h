#pragma once
#include <Runtime/Graphics/ShaderStage.h>
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Required information to create a shader
	/// </summary>
	struct PORTAKAL_API ShaderCreateDesc
	{
		ShaderStage Stage;
		String EntryPoint;
		String Source;
	};
}